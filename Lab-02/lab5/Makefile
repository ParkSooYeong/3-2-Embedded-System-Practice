ifeq  (.config, $(wildcard .config))
include  .config
endif

CROSS_COMPILE =
CC = $(CROSS_COMPILE)gcc

ifeq  ($(CONFIG_FN2), y)
ifeq  ($(CONFIG_SUBFN), y)
CFLAGS = -Iinclude  -DCONFIG_FN2 -DCONFIG_SUBFN
else
CFLAGS = -Iinclude  -DCONFIG_FN2
endif
else
CFLAGS = -Iinclude
endif

export CC
export CONFIG_FN2
export CONFIG_SUBFN
all : test
test : test.o
	$(MAKE)  -C  lib
	$(CC)  -o  $@  test.o  -Llib  -labc
.c.o :
	$(CC)  -c  $(CFLAGS)  $<
clean:
	$(MAKE)  -C  lib clean
	rm  -f  test  *.o
