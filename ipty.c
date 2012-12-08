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
#define NO_OF_DEV 6
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

/**
* This function gets call when Hyb_Send function get called from the user-space.
* Thus it delivers the data to destination tty device.
*/
static int tty_dev_write(struct tty_struct * tty, char *buf,
		int count) {
	if(count > 0 ){
		int total = tty_insert_flip_string(tty,buf,count);
		if(total){
			tty_flip_buffer_push(tty);
			tty_wakeup(tty);
		}
	}
	return count;
}

static int sync_tty_dev_write(struct tty_struct *tty){
	printk(KERN_ALERT "TTY index is %d\n",tty->index);
	return 0; 
}

/**
* This function gets called when the Hyb_Broadcast function is getting called. This is responsible to send the data to all the other
* tty device nodes.
*/

static int tty_dev_broadcast(struct tty_struct *tty, char *buf, int count){
	int i ;
	for(i = 0 ; i <NO_OF_DEV;++i){
		struct tty_struct *my_tty = master_tty_driver->ttys[i];		
		if(count > 0 && my_tty != NULL){
			int total = tty_insert_flip_string(my_tty,buf,count);
			if(total){
				tty_flip_buffer_push(my_tty);
				tty_wakeup(my_tty);
			}
		}
	}
	return i;
}

static int tty_dev_ioctl(struct tty_struct *tty,
		unsigned int cmd, unsigned long param) {

	int retval = -1;
	switch (cmd) {
	
		case IOCTL_BROADCAST_MSG :
			printk("Broadcasting is called\n");
/*
* Get the data from user space
*/
			char *temp = (char *) param;
			char input ;
			get_user(input,temp);
			int length ;
			for(length = 0 ;  input !=NULL; ++length, ++temp){
				get_user(input,temp);
			}
				
			char *arg = (char *) kmalloc((sizeof(char) *length)+4,GFP_KERNEL);
			temp = (char *) param;
			copy_from_user(arg,temp,length);
			printk(KERN_ALERT "Data from user space %s\n", arg);
			tty_dev_broadcast(tty,arg,length);
			kfree(arg);
			break;


		default:			
			printk(KERN_ALERT "Default case with tty index %d\n",tty->index);
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
