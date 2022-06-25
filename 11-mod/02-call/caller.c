#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

extern int myadd(int, int);
extern int mysub(int, int);

int __init init_caller(void)
{
     printk( KERN_ALERT "insmod caller.ko ...\n");
     printk( KERN_ALERT "[caller Module] myadd: %d\n", myadd(3, 2));
     printk( KERN_ALERT "[caller Module] mysub: %d\n", mysub(3, 2));
     return 0;
}   
void __exit exit_caller(void)
{
	printk(KERN_ALERT "rmmod caller ...\n");
}

module_init (init_caller);
module_exit (exit_caller);

MODULE_LICENSE("GPL");
