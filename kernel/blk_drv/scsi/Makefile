#
# Makefile for kernel/blk_drv/scsi
#
# Note! Dependencies are done automagically by 'make dep', which also
# removes any old dependencies. DONT put your own dependencies here
# unless its something special (ie not a .c file).
#

SCSI_OBJS :=

ifdef CONFIG_SCSI

SCSI_OBJS := hosts.o scsi.o scsi_ioctl.o constants.o

ifdef CONFIG_BLK_DEV_ST
SCSI_OBJS := $(SCSI_OBJS) st.o
endif

ifdef CONFIG_BLK_DEV_SD
SCSI_OBJS := $(SCSI_OBJS) sd.o sd_ioctl.o
endif

ifdef CONFIG_BLK_DEV_SR
SCSI_OBJS := $(SCSI_OBJS) sr.o sr_ioctl.o
endif

ifdef CONFIG_SCSI_AHA1542
SCSI_OBJS := $(SCSI_OBJS) aha1542.o
endif

ifdef CONFIG_SCSI_AHA1740
SCSI_OBJS := $(SCSI_OBJS) aha1740.o
endif

ifdef CONFIG_SCSI_FUTURE_DOMAIN
SCSI_OBJS := $(SCSI_OBJS) fdomain.o
endif

ifdef CONFIG_SCSI_ULTRASTOR
SCSI_OBJS := $(SCSI_OBJS) ultrastor.o
endif

ifdef CONFIG_SCSI_7000FASST
SCSI_OBJS := $(SCSI_OBJS) wd7000.o
endif

ifdef CONFIG_SCSI_SEAGATE
SCSI_OBJS := $(SCSI_OBJS) seagate.o
else
ifdef CONFIG_SCSI_FD_88x
SCSI_OBJS := $(SCSI_OBJS) seagate.o
endif
endif

ifdef CONFIG_SCSI_DEBUG
SCSI_OBJS := $(SCSI_OBJS) scsi_debug.o
endif

scsi.a: $(SCSI_OBJS)
	rm -f scsi.a
	$(AR) rcs scsi.a $(SCSI_OBJS)

else

scsi.a:
	rm -f scsi.a
	@echo No SCSI drivers configured
	$(AR) rcs scsi.a

endif

seagate.o: seagate.c
	$(CC) $(CFLAGS) -DARBITRATE -DSLOW_HANDSHAKE -DFAST32 -c seagate.c 

constants.o: constants.c
	$(CC) $(CFLAGS) -c constants.c

clean:
	rm -f core *.o *.a *.s

dep:
	$(CPP) -M *.c > .depend

#
# include a dependency file if one exists
#
ifeq (.depend,$(wildcard .depend))
include .depend
endif
