#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/uinput.h>

#define MIN(a,b) (((a) <= (b)) ? (a) : (b))
#define BULK_EP_OUT 0x01
//  81 - kb, 82 - mouse
#define BULK_EP_IN 0x81  //0x81 SEE CORRECT NUMBER IN lsusb -v
#define MAX_PKT_SIZE 8

/* table of devices that work with this driver */
#define VENDOR_ID	0x1532
#define PRODUCT_ID	0x0042


static int data;
static struct task_struct *task;
static struct usb_device *device;
static struct usb_class_driver class; //<HID
static unsigned char bulk_buf[MAX_PKT_SIZE];

static struct usb_device_id id_table[] = {
	{ USB_DEVICE(VENDOR_ID, PRODUCT_ID) },
	{ },
};

MODULE_DEVICE_TABLE(usb, id_table);

static void gotemp_disconnect(struct usb_interface *interface)
{
	dev_info(&interface->dev, "USB goTemp now disconnected\n");
}

static ssize_t gotemp_read(struct file *f, char __user *buf, size_t cnt, loff_t *off)
{
    int retval;
    int read_cnt;

    char* mybuf = kmalloc(MAX_PKT_SIZE, GFP_ATOMIC);

    /* Read the data from the int endpoint */
    retval = usb_interrupt_msg(device, usb_rcvintpipe(device, BULK_EP_IN),
            mybuf, MAX_PKT_SIZE, &read_cnt, 2000);

    if (retval)
    {
        printk(KERN_ERR "GoTemp: Interrupt message returned %d\n", retval);
        return retval;
    }

    if (copy_to_user(buf,mybuf,read_cnt)) return -EFAULT;

    /*if (mybuf[0] != 0) 
	printk(KERN_ERR "GoTemp: pressed button: %x", mybuf[0]);*/
 
    kfree(mybuf);
    return read_cnt;
}
static struct file_operations fops =
{
    .read = gotemp_read,
};

static int gotemp_probe(struct usb_interface *interface,
			const struct usb_device_id *id) // podkluchaetsya pri podkluchenii delaem 
{
	int retval;
	
	device = interface_to_usbdev(interface);
	class.name = "usb/gotemp%d";
	class.fops = &fops;
	if ((retval = usb_register_dev(interface, &class)) < 0)
		printk(KERN_ERR "GoTemp: Not able to get a minor for this device.");
	else
		printk(KERN_INFO "GoTemp: Minor obtained: %d\n", interface->minor);		
	data++;
	if (data < 2)
		printk(KERN_INFO "Kernel Thread: %s\n", task->comm);

	return retval;
}


static struct usb_driver gotemp_driver = {
	.name =		"goTemp",
	.probe =	gotemp_probe,
	.disconnect =	gotemp_disconnect,
	.id_table =	id_table,
};

static int __init gotemp_init(void)
{
	int result;
	data = 0;
	if ((result = usb_register(&gotemp_driver)))
		printk(KERN_ERR "GoTemp: usb_register failed. Error number %d", result);
	return result;
}

static void __exit gotemp_exit(void)
{
	usb_deregister(&gotemp_driver);
}

module_init(gotemp_init);
module_exit(gotemp_exit);
MODULE_AUTHOR("My name here");
MODULE_DESCRIPTION("Simple driver");
MODULE_LICENSE("GPL");


