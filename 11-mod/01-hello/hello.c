#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

int hello_init()
{
	printk("hello module loaded\n");
	return 0;
}

void hello_exit()
{
	printk("hello module unloaded\n");
	return;
}

module_init(hello_init );
module_exit(hello_exit );
MODULE_LICENSE("GPL");
