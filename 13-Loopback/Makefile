CONFIG_ARM = y

ifeq ($(CONFIG_ARM), y)
KDIR := /root/test/linux-2.6.35-s4210
CROSS_COMPILE = arm-linux-
else
KDIR := /lib/modules/$(shell uname -r)/build
endif

CC = $(CROSS_COMPILE)gcc

obj-m := loopback.o

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

load:
	insmod ./loopback.ko

unload:
	rmmod ./loopback

clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf modules.*
	rm -rf Module.*
	rm -rf .*.cmd
	rm -rf *.o
	rm -rf .tmp_versions
