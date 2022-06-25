obj-m := hello.o

KDIR := /lib/modules/$(shell uname -r)/build

# KDIR := /root/test/linux

PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -f *.o *.ko
	rm -f *.mod.*
	rm -f Module*
	rm -f module*