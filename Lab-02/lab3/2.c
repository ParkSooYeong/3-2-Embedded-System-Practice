// 2.c

#include <stdio.h>
static  int  sa;
static  int  sb = 100;

static  void  fn (char  *str)
{
	printf("Fn2 : [%s], %d, %d\n", str, sa, sb);
}

int  fn2 (char  *str)
{
	sa = 3001;
	sb = 3002;
	fn (str);
	return (0);
}
