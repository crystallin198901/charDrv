#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <cdev.h>
#define REG_MAJ 100
#define REG_MIN 0

struct cdev* pcdev;
struct file_operations* pfo;
dev_t dev_num;

static int chrdrv_open(struct inode *p,struct file *f)
{
  printk(KERN_INFO "chrDrv open function\n);
  return 0;
}

static ssize_t chrdrv_write(struct file *f,const char __user *b,size_t c,loff_t *l)
{
  printk(KERN_INFO "chrDrv write function\n");
  return 0;
}

static ssize_t chrdrv_read(struct file *f,const char __user *b,size_t c,loff_t *l)
{
  printk(KERN_INFO "chrDrv read function\n");
  return 0;
}

static int __init chrdrv_init(void)
{
  dev_num = MKDEV(REG_MAJ,REG_MIN);
  printk(KERN_INFO "charDrv init\n");
  if(OK == register_chrdev_region(dev_num,10,"char device"))
  {
    printk(KERN_INFO "device's number is %d\n",dev_num);
  }
  else
  {
    printk(KERN_INFO "failed to register devNum.\n");
    return -1; 
  } 
  pcdev = kzalloc(sizeof(struct cdev),GFP_KERNEL);
  pfo = kzalloc(sizeof(struct file_operations),GFP_KERNEL);
  pfo->open = chrdrv_open;
  pfo->write = chrdrv_write;
  pfo->read = chrdrv_read;
  cdev_init(pcdev,pfo);
  if(OK == cdev_add(pcdev,dev_num,10)
  {
    printk(KERN_INFO "charDrv added\n");
  }
  else
  {
    printk(KERN_INFO "failed to add charDrv\n");
    return -1;
  }
  return 0;
}

static void __exit chrdrv_exit(void)
{
  printk(KERN_INFO "charDrv exit\n");
  cdev_del(pcdev);
  kfree(pcdev);
  kfree(pfo);
  unregister_chrdev_region(dev_num);
}

module_init(chrdrv_init);
module_exit(chrdrv_exit);
MODULE_LICENSE("GPL");
