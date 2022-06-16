obj-y = 1.o
obj-$(CONFIG_FN2) += 2.o

all : libabc.a
libabc.a : $(obj-y)
ifeq  ($(CONFIG_SUBFN), y)
	$(MAKE)  -C  sub
	ar  ruv  $@  $(obj-y) sub/subfn.o
else
	ar  ruv  $@  $(obj-y)
endif
1.o : 1.c
2.o : 2.c
.c.o :
	$(CC) -c $<
clean :
	$(MAKE)  -C  sub clean
	rm  -f  *.o  *.a  *.so
