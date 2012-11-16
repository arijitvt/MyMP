#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/tty_driver.h>
#include<linux/tty.h>
#include<linux/tty_flip.h>
#include<linux/device.h>
#include<linux/major.h>
#include<linux/slab.h>
#include<linux/timer.h>
#include<linux/string.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
#include<linux/devpts_fs.h>
#include<linux/tty.h>
#include "ipty.h"

MODULE_LICENSE("GPL");

#define SUCCESS 0
#define FAILURE -1

/**************************************************/
/*System Variables*/
#define NO_OF_DEV 4
#define MINOR_START_NUMBER 121
const char *tty_driver_name = "IPC_tty";
const char *tty_dev_name = "ipty";
const char tokenizer = '%';

/***************************************************/

struct tty_driver *master_tty_driver;

int totalDevices = NO_OF_DEV;

static int tty_dev_open(struct tty_struct *tty, struct file *flip) {
	return SUCCESS;
}

static void tty_dev_close(struct tty_struct *tty, struct file *flip) {
}


static int tty_dev_write(struct tty_struct * tty, char *buf,
		int count) {
	if(count > 0 ){
	//	tty_lock();
		strcat(buf,"\n");
		int total = tty_insert_flip_string(tty,buf,count+1);
		if(total){
			tty_flip_buffer_push(tty);
			tty_wakeup(tty);
		}
	//	tty_unlock();
	}
	return count;
}

static int sync_tty_dev_write(struct tty_struct *tty){
	printk(KERN_ALERT "TTY index is %d\n",tty->index);
	return 0; 
}

static int tty_dev_ioctl(struct tty_struct *tty, struct file *flip,
		unsigned int cmd, unsigned long param) {

	int retval = -1;

	switch (cmd) {

		case IOCTL_READ_MSG:
			printk(KERN_ALERT "Read message command is read\n");
			break;

		case IOCTL_SEND_MSG:
			printk(KERN_ALERT "Sending the message\n");
			retval = sync_tty_dev_write(tty);
			break;

		default:			
			printk(KERN_ALERT "Default case with tty index %d\n",tty->index);
			//sync_sent = 1;
			//open_device[tty->index] = 1;
	}
	return 0;
}

int tty_write_room(struct tty_struct *tty){
	int n = 8192 - tty->buf.memory_used;
	if(n < 0 )
		return 0;
	return n;
}



static struct tty_operations tty_dev_operations = {

	.open = tty_dev_open, 
	.close = tty_dev_close, 
	.write = tty_dev_write, 
	.ioctl = tty_dev_ioctl,
	.write_room = tty_write_room,	
};


static int initModule(void) {

printk(KERN_ALERT "My TTY driver Module is loading\n");
master_tty_driver = alloc_tty_driver(NO_OF_DEV);
if (!master_tty_driver) {
	printk(KERN_ALERT "Allocation of master is failed");
	return FAILURE;
}

//memset(open_device,0,NO_OF_DEV*sizeof(int));

master_tty_driver->owner = THIS_MODULE;
master_tty_driver->driver_name = tty_driver_name;
master_tty_driver->name = tty_dev_name;
master_tty_driver->major = TTY_MAJOR;
master_tty_driver->minor_start = MINOR_START_NUMBER;
master_tty_driver->num = NO_OF_DEV;
master_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
master_tty_driver->subtype = SERIAL_TYPE_NORMAL;
master_tty_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_RESET_TERMIOS;
master_tty_driver->init_termios = tty_std_termios;
master_tty_driver->init_termios.c_iflag = 0;
master_tty_driver->init_termios.c_oflag = 0;
master_tty_driver->init_termios.c_cflag = B38400 | CS8 | CREAD;
master_tty_driver->init_termios.c_lflag = 0;
master_tty_driver->init_termios.c_ispeed = 38400;
master_tty_driver->init_termios.c_ospeed = 38400;
tty_set_operations(master_tty_driver, &tty_dev_operations);

int retval = tty_register_driver(master_tty_driver);
if (retval != 0) {
	printk(KERN_ALERT "Unable to register the device\n");
	return FAILURE;
}

return SUCCESS;
}

static void exitModule(void) {
int i;
for (i = 0; i < totalDevices; ++i) {
	tty_unregister_device(master_tty_driver, i);
}

tty_unregister_driver(master_tty_driver);
printk(KERN_ALERT "My TTY Driver Module is unloading\n");
}

module_init( initModule);
module_exit( exitModule);
