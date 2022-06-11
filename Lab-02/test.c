#include <stdio.h>
#include "test.h"
int main()
{
	(void) fn1 ("First call");
#if defined(CONFIG_FN2)
	(void) fn2 ("Second call");
#endif

#if defined(CONFIG_SUBFN)
	sub();
#endif
}
