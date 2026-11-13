/****************************************************************************
 *
 * Copyright (c) 2014 - 2025 Samsung Electronics Co., Ltd. All rights reserved
 *
 * BT driver using hci_dev
 *
 ****************************************************************************/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/gpio/consumer.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>

#include <linux/mod_devicetable.h>
#include <linux/pm_runtime.h>
#include <linux/acpi.h>

#include <net/bluetooth/bluetooth.h>
#include <net/bluetooth/hci.h>
#include <net/bluetooth/hci_core.h>

#include "scsc_mx_module.h"
#include IN_SCSC_INC(scsc_logring.h)
#include "scsc_bt_priv.h"

static struct hci_dev			*hdev;
static const struct file_operations	*bt_fs;
static atomic_t				*error_count_ref;
static wait_queue_head_t		*read_wait_ref;
static struct device			*dev_ref;
static bool				terminate_recv;

struct scsc_data {
	struct sk_buff *rx_skb;
} scsc_data;

#define GET_HCI_DEV_PKT_TYPE(buf, type) ((const type *)(buf))[0]

struct h4_recv_pkt {
	u8  type;	/* Packet type */
	u8  hlen;	/* Header length */
	u8  loff;	/* Data length offset in header */
	u8  lsize;	/* Data length field size */
	u16 maxlen;	/* Max overall packet length */
	int (*recv)(struct hci_dev *hdev, struct sk_buff *skb);
};

#define H4_RECV_ACL \
	.type = HCI_ACLDATA_PKT, \
	.hlen = HCI_ACL_HDR_SIZE, \
	.loff = 2, \
	.lsize = 2, \
	.maxlen = HCI_MAX_FRAME_SIZE \

#define H4_RECV_SCO \
	.type = HCI_SCODATA_PKT, \
	.hlen = HCI_SCO_HDR_SIZE, \
	.loff = 2, \
	.lsize = 1, \
	.maxlen = HCI_MAX_SCO_SIZE

#define H4_RECV_EVENT \
	.type = HCI_EVENT_PKT, \
	.hlen = HCI_EVENT_HDR_SIZE, \
	.loff = 1, \
	.lsize = 1, \
	.maxlen = HCI_MAX_EVENT_SIZE

#define H4_RECV_ISO \
	.type = HCI_ISODATA_PKT, \
	.hlen = HCI_ISO_HDR_SIZE, \
	.loff = 2, \
	.lsize = 2, \
	.maxlen = HCI_MAX_FRAME_SIZE \

static const struct h4_recv_pkt scsc_bt_recv_pkts[] = {
	{ H4_RECV_ACL,    .recv = hci_recv_frame   },
	{ H4_RECV_SCO,    .recv = hci_recv_frame   },
	{ H4_RECV_EVENT,  .recv = hci_recv_frame   },
	{ H4_RECV_ISO,    .recv = hci_recv_frame   },
};

static struct sk_buff *_h4_recv_buf(struct hci_dev *hdev, struct sk_buff *skb,
				    const unsigned char *buffer, int count)
{
	const struct h4_recv_pkt *pkts = scsc_bt_recv_pkts;
	int pkts_count = ARRAY_SIZE(scsc_bt_recv_pkts);

	/* Check for error from previous call */
	if (IS_ERR(skb))
		skb = NULL;

	while (count) {
		int i, len;

		if (!skb) {
			for (i = 0; i < pkts_count; i++) {
				if (buffer[0] != (&pkts[i])->type)
					continue;

				skb = bt_skb_alloc((&pkts[i])->maxlen,
						   GFP_ATOMIC);
				if (!skb)
					return ERR_PTR(-ENOMEM);

				hci_skb_pkt_type(skb) = (&pkts[i])->type;
				hci_skb_expect(skb) = (&pkts[i])->hlen;
				break;
			}

			/* Check for invalid packet type */
			if (!skb)
				return ERR_PTR(-EILSEQ);

			count -= 1;
			buffer += 1;
		}

		len = min_t(uint, hci_skb_expect(skb) - skb->len, count);
		skb_put_data(skb, buffer, len);

		count -= len;
		buffer += len;

		/* Check for partial packet */
		if (skb->len < hci_skb_expect(skb))
			continue;

		for (i = 0; i < pkts_count; i++) {
			if (hci_skb_pkt_type(skb) == (&pkts[i])->type)
				break;
		}

		if (i >= pkts_count) {
			kfree_skb(skb);
			return ERR_PTR(-EILSEQ);
		}

		if (skb->len == (&pkts[i])->hlen) {
			u16 dlen;

			switch ((&pkts[i])->lsize) {
			case 0:
				/* No variable data length */
				dlen = 0;
				break;
			case 1:
				/* Single octet variable length */
				dlen = skb->data[(&pkts[i])->loff];
				hci_skb_expect(skb) += dlen;

				if (skb_tailroom(skb) < dlen) {
					kfree_skb(skb);
					return ERR_PTR(-EMSGSIZE);
				}
				break;
			case 2:
				/* Double octet variable length */
				dlen = skb->data[(&pkts[i])->loff] |
				       skb->data[(&pkts[i])->loff+1] << 8;
				hci_skb_expect(skb) += dlen;

				if (skb_tailroom(skb) < dlen) {
					kfree_skb(skb);
					return ERR_PTR(-EMSGSIZE);
				}
				break;
			default:
				/* Unsupported variable length */
				kfree_skb(skb);
				return ERR_PTR(-EILSEQ);
			}

			if (!dlen) {
				/* No more data, complete frame */
				(&pkts[i])->recv(hdev, skb);
				skb = NULL;
			}
		} else {
			/* Complete frame */
			(&pkts[i])->recv(hdev, skb);
			skb = NULL;
		}
	}

	return skb;
}

/*
 * scsc_hci_recv_frame receives the final data frame through scsc_shm transports.
 * read(scsc_bt_shm_h4_read) received read frame via bsmhcp_protocol.
 */
int scsc_hci_recv_frame(const void *buf, size_t len)
{
	SCSC_TAG_DEBUG(BT_H4,
			"hci_recv_frame (pkt_type: %u, len: %zu)\n",
			GET_HCI_DEV_PKT_TYPE(buf, unsigned char), len - 1);

	if (terminate_recv)
		return 0;

	scsc_data.rx_skb = _h4_recv_buf(hdev, scsc_data.rx_skb, buf, len);

	if (IS_ERR(scsc_data.rx_skb)) {
		int err = PTR_ERR(scsc_data.rx_skb);
		SCSC_TAG_ERR(BT_RX, "Frame reassembly failed (%d)", err);
		scsc_data.rx_skb = NULL;
		return err;
	}

	SCSC_TAG_DEBUG(BT_H4, "Done\n");
	return len;
}

/* scsc_hci_send_frame - write frame to scsc_shm.
 * write(scsc_bt_shm_h4_write) transmits write frame via bsmhcp_protocol.
 */
static int scsc_hci_send_frame(struct hci_dev *hdev, struct sk_buff *skb)
{
	int ret;
	SCSC_TAG_DEBUG(BT_H4,
			"scsc_hci_send_frame (pkt_type: %u, len=%u)\n",
			hci_skb_pkt_type(skb), skb->len);

	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	ret = bt_fs->write(NULL, skb->data, skb->len, NULL);
	if (ret >= 0) {
		/* Update HCI stat counters */
		hdev->stat.byte_tx += skb->len;

		switch (hci_skb_pkt_type(skb)) {
			case HCI_COMMAND_PKT:
				hdev->stat.cmd_tx++;
				break;

			case HCI_ACLDATA_PKT:
				hdev->stat.acl_tx++;
				break;

			case HCI_SCODATA_PKT:
				hdev->stat.sco_tx++;
				break;
		}
		kfree_skb(skb);
	}

	SCSC_TAG_DEBUG(BT_H4, "Sent Done (len: %d)\n", ret);
	return ret;
}

static int scsc_hci_flush(struct hci_dev *hdev)
{
	return 0;
}

static int scsc_hci_open(struct hci_dev *hdev)
{
	SCSC_TAG_INFO(BT_COMMON, "%s %p\n", hdev->name, hdev);
	terminate_recv = false;

	hdev->flush = scsc_hci_flush;

  	return 0;
}

static int scsc_hci_close(struct hci_dev *hdev)
{
	SCSC_TAG_INFO(BT_COMMON, "%s %p\n", hdev->name, hdev);
	terminate_recv = true;

	hdev->flush = NULL;

	return 0;
}

static int scsc_hci_shutdown(struct hci_dev *hdev)
{
	int ret;
	SCSC_TAG_INFO(BT_COMMON, "%s %p\n", hdev->name, hdev);
	terminate_recv = true;

	if (error_count_ref != NULL)
		atomic_inc(error_count_ref);

	if (read_wait_ref != NULL)
		wake_up(read_wait_ref);

	ret = bt_fs->release(NULL, NULL);

	hdev->hw_error = NULL;
	hdev->reset = NULL;

	return ret;
}

static int scsc_hci_setup_diag(struct hci_dev *hdev, bool enable)
{
	SCSC_TAG_INFO(BT_COMMON, "Handle first open\n");

	set_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks);
	return 0;
}

static int scsc_hci_setup(struct hci_dev *hdev)
{
	int ret = 0;

	SCSC_TAG_INFO(BT_COMMON, "Skip first setup");
	/*
	 * This file is for using the Linux Bluetooth subsystem for AIDL. The
	 * net/bluetooth performs some operations after registering a hci
	 * device.  However, we don't want these operations that are out of our
	 * control and the first driver open after booting to be performed at
	 * this stage because it cannot to download converted HCF file at the
	 * openning time. Therefore, we add this flag to ignore the first open
	 * (during Bluetooth device registeration) after device botting.
	 */
	if (!test_bit(HCI_QUIRK_NON_PERSISTENT_DIAG, &hdev->quirks)) {
		SCSC_TAG_INFO(BT_COMMON, "Set the diagnostic function.\n");

		set_bit(HCI_QUIRK_NON_PERSISTENT_DIAG, &hdev->quirks);
		hci_dev_set_flag(hdev, HCI_VENDOR_DIAG);
		hdev->set_diag = scsc_hci_setup_diag;

		return -EAGAIN;
	}

	ret = bt_fs->open(NULL, NULL);
	if (ret < 0)
		SCSC_TAG_ERR(BT_COMMON, "Open scsc_bt_h4 failed.\n");
	else
		hdev->shutdown = scsc_hci_shutdown;

	return ret;
}

void slsi_bt_notify_probe(struct device *dev,
			  const struct file_operations *fs,
			  atomic_t *error_count,
			  wait_queue_head_t *read_wait)
{
	bt_fs		= fs;
	error_count_ref = error_count;
	read_wait_ref   = read_wait;
	dev_ref		= dev;

	SCSC_TAG_INFO(BT_COMMON, "SCSC HCI probe\n");
}

void slsi_bt_notify_remove(void)
{
	bt_fs		= NULL;
	error_count_ref = NULL;
	read_wait_ref   = NULL;
	dev_ref		= NULL;

	SCSC_TAG_INFO(BT_COMMON, "SCSC HCI remove\n");
}

int scsc_hci_init(void)
{
	int ret = 0;

	if (!hdev) {
		hdev = hci_alloc_dev_priv(0);
		if (!hdev) {
			SCSC_TAG_ERR(BT_COMMON, "Can't allocate HCI device\n");
			return -ENOMEM;
		}

		hdev->bus = HCI_VIRTUAL;

		SET_HCIDEV_DEV(hdev, dev_ref);

		hdev->open  = scsc_hci_open;
		hdev->close = scsc_hci_close;
		hdev->send  = scsc_hci_send_frame;
		hdev->setup = scsc_hci_setup;

		ret = hci_register_dev(hdev);
		if (ret < 0) {
			SCSC_TAG_ERR(BT_COMMON, "failed to register hci device (err: %d)\n", ret);
			hci_free_dev(hdev);
			hdev = NULL;
		}
	}

	scsc_data.rx_skb = NULL;

	return ret;
}

int scsc_hci_deinit(void)
{
	if (hdev) {
		hci_unregister_dev(hdev);
		hci_free_dev(hdev);
		hdev = NULL;
	}

	memset(&scsc_data, 0, sizeof(struct scsc_data));
	return 0;
}
