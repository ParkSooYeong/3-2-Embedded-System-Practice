#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DEBUG 1
#define MAX_BUFFER_SIZE 65535

static struct proc_dir_entry* proc_dir_entry_p;
static struct file_operations file_operations_s;
static char* proc_buffer_p;
static unsigned int proc_buffer_length_v;
static unsigned short int read_flag;

int read_proc(struct file* file, char* buffer, size_t count, loff_t* offset)
{
	if(DEBUG) printk(KERN_INFO "read_proc() called.\n");
	if(read_flag) read_flag = 0;
	else {
		read_flag = 1;
		return 0;
	}
	copy_to_user(buffer, proc_buffer_p, proc_buffer_length_v);
	if(DEBUG) printk(KERN_INFO "Ok. (count = %zu)\n", count);
	return proc_buffer_length_v;
}

int write_proc(struct file* file, char* buffer, size_t count, loff_t* offset)
{
	size_t n;
	if(DEBUG) printk(KERN_INFO "write_proc() called.\n");
	if(count >= MAX_BUFFER_SIZE) {
		if(DEBUG) printk(KERN_INFO "write_proc(): Buffer exceeded!\n");
		n = MAX_BUFFER_SIZE;
	}
	else n = count;
	kfree(proc_buffer_p);
	if(DEBUG) printk(KERN_INFO "kfree() called.\n");
	if(!(proc_buffer_p = (char*)kmalloc(MAX_BUFFER_SIZE*sizeof(char), GFP_KERNEL))) {
		if(DEBUG) printk(KERN_INFO "kmalloc() ko.\n");
		return count;
	}
	if(DEBUG) printk(KERN_INFO "kmalloc() ok.\n");
	copy_from_user(proc_buffer_p, buffer, n);
	proc_buffer_length_v = n;
	if(DEBUG) printk(KERN_INFO "Ok. (count = %zu)\n", count);
	return count;
}

static int __init init_f(void)
{
	if(DEBUG) printk(KERN_INFO "Module inserted.\n");
	remove_proc_entry("device-tree", NULL);
	if(!(proc_dir_entry_p = proc_create("device-tree", 0666, NULL, &file_operations_s))) {
		if(DEBUG) printk(KERN_INFO "Proc entry not created.\n");
		return -1;
	}
	if(DEBUG) printk(KERN_INFO "Proc entry created.\n");
	file_operations_s.read = read_proc;
	file_operations_s.write = write_proc;
	if(!(proc_buffer_p = (char*)kmalloc(1*sizeof(char), GFP_KERNEL))) {
		if(DEBUG) printk(KERN_INFO "kmalloc() ko.\n");
		return -1;
	}
	if(DEBUG) printk(KERN_INFO "kmalloc() ok.\n");
	proc_buffer_p[0] = '\0';
	proc_buffer_length_v = 0;
	read_flag = 1;
	if(DEBUG) printk(KERN_INFO "Ok.\n");
	return 0;
}

static void __exit exit_f(void)
{
	kfree(proc_buffer_p);
	if(DEBUG) printk(KERN_INFO "kfree() called.\n");
	remove_proc_entry("device-tree", NULL);
	if(DEBUG) printk(KERN_INFO "Proc entry removal requested.\n");
	if(DEBUG) printk(KERN_INFO "Module removed.\n");
}

module_init(init_f);
module_exit(exit_f);
