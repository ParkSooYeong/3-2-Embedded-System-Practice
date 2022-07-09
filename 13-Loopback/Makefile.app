OBJS = app.o

CONFIG_ARM = y

ifeq ($(CONFIG_ARM), y)
CROSS_COMPILE = arm-linux-
endif
CC = $(CROSS_COMPILE)gcc

all: app

app: $(OBJS)
ifeq ($(CONFIG_ARM), y)
	$(CC) -static -o $@ $(OBJS)
else
	$(CC) -o $@ $(OBJS)
endif

app.o: app.c

.c.o:
	$(CC)  -c  $<

clean:
	rm -rf app *.o *.a *.so
