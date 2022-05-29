OBJS = test.o 1.o 2.o
all : test
test : $(OBJS)
	$(CC)  -o  $@  $(OBJS)
test.o : test.c test.h
1.o : 1.c
2.o : 2.c
.c.o :
	$(CC)  -c  $<
clean :
	rm  -f  test  *.o
