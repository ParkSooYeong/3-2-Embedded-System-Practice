#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int __init init_callee(void)
{
	printk(KERN_ALERT "insmod callee.ko ...\n");
	return 0;
}

void __exit exit_callee(void)
{
	printk(KERN_ALERT "rmmod callee ...\n");
}

int myadd( int a, int b)
{
	printk(KERN_ALERT "[callee Module] myadd called \n");
	return a+b;
}

int mysub( int a, int b)
{
	printk(KERN_ALERT "[callee Module] mysub called \n");
	return a-b;
}

EXPORT_SYMBOL(myadd);
EXPORT_SYMBOL(mysub);

module_init(init_callee);
module_exit(exit_callee);

MODULE_LICENSE("GPL");