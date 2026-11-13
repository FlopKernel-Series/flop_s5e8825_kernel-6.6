#ifndef _CHUB_SHUB_H_
#define _CHUB_SHUB_H_

#include <linux/version.h>
#if (KERNEL_VERSION(6, 6, 0) <= LINUX_VERSION_CODE)
#include <soc/samsung/exynos/nanohub.h>
#else
#include <linux/platform_data/nanohub.h>
#endif

void set_contexthub_info(struct contexthub_ipc_info *chub);
void contexthub_dump_notifier_call(int val, struct contexthub_dump *dump);
void contexthub_ipc_notifier_call(int val, struct contexthub_ipc_data *data);

#endif
