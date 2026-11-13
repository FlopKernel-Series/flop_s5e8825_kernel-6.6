
/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *  snd_debug_proc.h - header for SAMSUNG Audio debugging.
 */

#include <linux/mutex.h>

#define AUD_LOG_BUF_SIZE	SZ_64K
#define SDP_INFO_MAGIC 0x315044534153584Dull /*MXSASDP1*/
#define SDP_BOOT_MAGIC 0x325044534153584Dull /*MXSASDP2*/

struct sdp_log_buf {
	unsigned long long magic;
	char buf[AUD_LOG_BUF_SIZE];
} __packed;

struct snd_debug_proc {
	struct sdp_log_buf log_buf;
	bool is_enabled;
	unsigned int buf_pos;
	unsigned int buf_full;
	struct mutex lock;
	void (*save_log)(char *buf, int len);
};

#if IS_ENABLED(CONFIG_SND_SOC_SAMSUNG_AUDIO)
void sdp_info_print(const char *fmt, ...);

void sdp_boot_print(const char *fmt, ...);
#else
inline void sdp_info_print(const char *fmt, ...)
{
}

inline void sdp_boot_print(const char *fmt, ...)
{
}
#endif

