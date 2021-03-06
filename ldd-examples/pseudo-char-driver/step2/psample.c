#include <linux/init.h>	
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/cdev.h>

dev_t pseudo_dev_id;

struct cdev c1; //per device

int pseudo_open(struct inode* inode,struct file* file)
{
	printk("pseudo open...\n");
	return 0;
}
int pseudo_close(struct inode* inode,struct file* file)
{
	printk("pseudo close...\n");
	return 0;
}
int pseudo_read(struct file* file,char __user* ubuf,size_t ucount,loff_t *off)
{
	printk("pseudo read..\n");
	return 0;
}
int pseudo_write(struct file* file,const char __user* ubuf,size_t ucount,loff_t *off)
{
	printk("pseudo write..\n");
	return 0;
}
struct file_operations pseudo_fops =
{
	.open 		= pseudo_open,
	.release 	= pseudo_close,
	.read		= pseudo_read,
	.write		= pseudo_write
};

static int __init psample_init(void)	
{
	int ret,i=0;
	ret=alloc_chrdev_region(&pseudo_dev_id,0,ndevices,"pseudo_char_driver");
	if(ret)
	{
		printk("error in alloc....\n");
		return -EINVAL; //suitable err value
	}
	cdev_init(&cdev, &pseudo_fops);
	kobject_set_name(&cdev.kobj,"pdevice%d",i);
	ret=cdev_add(&cdev,pseudo_dev_id+i,1);
	if(ret)
	{
		//TODO
	}
	printk("pseudo char drivered registered,major=%d\n",MAJOR(pseudo_dev_id));
        return 0;
}
static void __exit psample_exit(void)
{
	cdev_del(&cdev);
 	unregister_chrdev_region(pseudo_dev_id,ndevices);
	printk("device unregistered\n");
}
module_init(psample_init); 
module_exit(psample_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rajesh Sola");
MODULE_DESCRIPTION("A Pseudo Char Driver Module");


