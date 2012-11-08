#ifndef IPTY_H
#define IPTY_H

/*
#include<linux/tty_driver.h>
#include<linux/tty.h>
*/
#include<linux/ioctl.h>

#define TTY_DEVICE_MAJOR 4

#define IOCTL_READ_MSG _IOR(TTY_DEVICE_MAJOR,0,char *)

#define IOCTL_SEND_MSG _IOR(TTY_DEVICE_MAJOR,1,int)
/*
#define IOCTL_SYNC_OPEN_DEV _IOR(TTY_DEVICE_MAJOR, 2, int)

#define IOCTL_SYNC_CLOSE_DEV _IOR(TTY_DEVICE_MAJOR, 3, int)
*/
#endif
