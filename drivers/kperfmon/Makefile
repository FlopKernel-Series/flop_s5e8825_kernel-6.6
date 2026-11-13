#
# Makefile for the Linux kernel device drivers.
#
# Sep 2018, Binse Park <h22yap@gmail.com>
# Rewritten to use lists instead of if-statements.
#

ifeq ($(CONFIG_KPERFMON), y)
$(shell mkdir -p $(objtree)/include/linux && \
	cp -f $(srctree)/$(src)/olog.pb.h $(objtree)/include/linux/ && \
	cp -f $(srctree)/$(src)/ologk.h $(objtree)/include/linux/)

ifeq ($(CONFIG_KPERFMON_BUILD), y)
	obj-y		+= kperfmon.o
else
	obj-m		+= kperfmon.o
endif
endif
