#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>	  // kmalloc.h
#include<linux/uaccess.h>	   // copy to/from user
#include<linux/ioctl.h>

#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "ioctl.h"

int32_t value1 = 0;
int32_t value2 = 0;
int32_t value = 0;

dev_t dev = 0;

static struct class *dev_class;
static struct cdev calc_cdev;

static int __init calc_driver_init(void);
static void __exit calc_driver_exit(void);

static long calc_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

int len, temp, op=4;
char *msg, *buf;

static int
calc_show(struct seq_file *m, void *v)
{
	printk(KERN_INFO "3. Calc_Proc_show !\n");
	// seq_printf(m, "Hello proc !\n");
	// seq_printf(m, "HZ = %d\n", HZ);

	if(op == 1) seq_printf(m, "%d + %d = %d\n", value1, value2, value);
	else if(op == 2) seq_printf(m, "%d - %d = %d\n", value1, value2, value);
	else if(op == 3) seq_printf(m, "%d * %d = %d\n", value1, value2, value);
	else seq_printf(m, "Calc in Kernel ...\n");

	return 0;
}

int calc_read(struct file *filp, char *buf, size_t count, loff_t *offp)
{
	if(count>temp) count = temp;
	temp = temp - count;
	copy_to_user(buf, msg, count);
	if(count == 0) temp = len;

	return count;
}

static int
calc_open(struct inode *inode, struct	file *file)
{
	printk(KERN_INFO "2. Calc_Proc_open !\n");
	return single_open(file, calc_show, NULL);
}

static struct file_operations fops = 
{
	.owner	  = THIS_MODULE,
	.unlocked_ioctl = calc_ioctl,
	.open = calc_open,
	// .read = calc_read,
	.read = seq_read,
};

static long calc_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd) {
		case CALC_IOCTL_ADD:
			op = 1;
			value = value1 + value2;
			printk(KERN_INFO "Add Operation\n");
			break;
		case CALC_IOCTL_SUB:
			op = 2;
			value = value1 - value2;
			printk(KERN_INFO "Subtraction Operation\n");
			break;
		case CALC_IOCTL_MUL:
			op = 3;
			value = value1 * value2;
			printk(KERN_INFO "Multiplication Operation\n");
			break;

		case CALC_IOCTL_DATA01:
			copy_from_user(&value1, (int32_t*)arg, sizeof(value1));
			printk(KERN_INFO "Received Data01 = %d\n", value1);
			break;
		case CALC_IOCTL_DATA02:
			copy_from_user(&value2, (int32_t*)arg, sizeof(value2));
			printk(KERN_INFO "Received Data02 = %d\n", value2);
			break;

		case CALC_IOCTL_RESULT:
			printk(KERN_INFO "Return Data to Application (%d)\n", value);
			copy_to_user((int32_t*) arg,  &value, sizeof(value));
			break;

		case CALC_IOCTL_CLS:
		default:
			value1 = 0;
			value2 = 0;
			value = 0;
			printk(KERN_INFO "Reset Kernel Data !!\n");
			break;
	}

	return 0;
}

static int __init calc_driver_init(void)
{
	if((alloc_chrdev_region(&dev, 0, 1, "calc_dev")) <0) {
		printk(KERN_INFO "cannot allocate major number\n");
		return -1;
	}
	printk(KERN_INFO "MAJOR = %d, Minor = %d\n", MAJOR(dev), MINOR(dev));

	cdev_init(&calc_cdev, &fops);

	if((cdev_add(&calc_cdev, dev, 1)) < 0) {
		printk(KERN_INFO "Cannot add device to the system\n");
		goto r_class;
	}

	/* Creating struct class */
	if((dev_class = class_create(THIS_MODULE, "calc_class")) == NULL) {
		printk(KERN_INFO "Cannot create the struct class\n");
		goto r_class;
	}

	/* Creating device */
	if((device_create(dev_class, NULL, dev, NULL, "calc_device")) == NULL) {
		printk(KERN_INFO "Cannot create the Device 1\n");
		goto r_device;
	}
	printk(KERN_INFO "Device Driver Insert ... Done!!!\n");

	printk(KERN_INFO "1. Calc_Proc_init !\n");
	proc_create("calc", 0, NULL, &fops);

	return 0;

r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev, 1);
	return -1;
}

void __exit calc_driver_exit(void)
{
	remove_proc_entry("calc", NULL);

	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&calc_cdev);
	unregister_chrdev_region(dev,  1);
	printk(KERN_INFO "Device Driver Remove ... Done!!!\n");
}

module_init(calc_driver_init);
module_exit(calc_driver_exit);

MODULE_LICENSE("GPL");
