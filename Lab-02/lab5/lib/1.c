// 1.c

#include <stdio.h>

int  a;
int  b = 100;
int  fn1 (char  *str)
{
	a = 1001;
	b = 1002;
	printf("Fn1 : [%s], %d, %d\n", str, a, b);

	return (0);
}
