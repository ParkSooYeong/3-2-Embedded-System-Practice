KERNELDIR = /lib/modules/$(shell uname -r)/build

obj-m := dd.o

KDIR := /lib/modules/$(shell uname -r)/build
# KDIR := /root/test/linux

PWD := $(shell pwd)

default:
#	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	$(MAKE) -C $(KDIR) M=${PWD} modules

load:
	insmod ./dd.ko

unload:
	rmmod dd

clean:
#	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	$(MAKE) -C $(KDIR) M=${PWD} clean

ifeq (0,1)
clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf modules.*
	rm -rf Module.*
	rm -rf .*.cmd
	rm -rf *.o
	rm -rf .tmp_versions
endif