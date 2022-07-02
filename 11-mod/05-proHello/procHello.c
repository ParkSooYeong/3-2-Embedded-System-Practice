#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static int hello_proc_show(struct seq_file *m, void *v) {
	seq_printf(m, "Hello proc!\n");
	return 0;
}

static int hello_proc_open(struct inode *inode, struct  file *file) {
	return single_open(file, hello_proc_show, NULL);
}

static const struct file_operations hello_proc_fops = {
	.owner = THIS_MODULE,
	.open = hello_proc_open,
	.read = seq_read,
	.write = seq_write,
	.llseek = seq_lseek,
	.release = single_release,
};

static int hello_proc_init(void) {
	proc_create("hello_proc", 0, NULL, &hello_proc_fops);
	printk("Process hello proc created");
	return 0;
}

static void hello_proc_exit(void) {
	remove_proc_entry("hello_proc", NULL);
}

module_init(hello_proc_init);
module_exit(hello_proc_exit);

MODULE_LICENSE("GPL");
