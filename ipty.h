#ifndef IPTY_H
#define IPTY_H


#include<linux/major.h>
#include<linux/ioctl.h>



#define IOCTL_BROADCAST_MSG _IOWR(TTY_MAJOR,0, char *)

#endif
