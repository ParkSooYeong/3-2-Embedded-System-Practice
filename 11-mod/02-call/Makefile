#KDIR := /lib/modules/$(shell uname -r)/build
#KDIR := /root/test/linux

SRCS := callee.c caller.c
OBJS := $(SRCS:.c=.o)

obj-m += $(OBJS)

# obj-m := callee.o caller.o

EXTRA_CFLAGS = -O2

KVERSION = $(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
	$(RM) Module.markers modules.order