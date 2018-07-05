#include <linux/module.h> /* Specifically, a module */
#include <linux/kernel.h> /* We're doing kernel work */
#include <linux/proc_fs.h> /* Necessary because we use the proc fs */
#include <linux/slab.h> 
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>


#define procfs_name "helloworld"
/**
* This structure hold information about the /proc file
*
*/
struct proc_dir_entry *Our_Proc_File;

static char *str = NULL;

static int my_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "current kernel time is %ld\n", jiffies);
	seq_printf(m, "str is %s\n", str);
	return 0;
}

static int mytest_proc_open(struct inode *inode, struct file *file)
{
 	return single_open(file, my_proc_show, inode->i_private);
}

static ssize_t  my_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos)
{
	char *tmp = kzalloc((count+1), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;
 
	if (copy_from_user(tmp,buffer,count)) {
		kfree(tmp);
		return -EFAULT;
	}
 
	kfree(str);
	str = tmp;
 
	return count;

}

static const struct file_operations mytest_proc_fops = {
 	.open  = mytest_proc_open,
 	.read  = seq_read,
 	.write  = my_proc_write,
 	.llseek  = seq_lseek,
 	.release = single_release,
};

int init_module()
{
 	Our_Proc_File = proc_create(procfs_name,0666, NULL,&mytest_proc_fops);
	if (Our_Proc_File == NULL) {
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
			procfs_name);
		return -ENOMEM;
	}
	printk(KERN_INFO "/proc/%s created\n", procfs_name);
	return 0; /* everything is ok */
}

void cleanup_module()
{
	remove_proc_entry(procfs_name, NULL);
	printk(KERN_INFO "/proc/%s removed\n", procfs_name);
}

