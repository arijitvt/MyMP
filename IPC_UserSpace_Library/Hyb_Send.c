#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>

#include "libipc.h"
#include "../ipty.h"

int Hyb_Send(int dest, const char *data, int count )
{
	char string_buffer[10];
	sprintf(string_buffer,"%d",dest);
	const char *dev_name =  "/dev/ipty";
	char *dest_string = (char *)malloc(strlen(dev_name)+strlen(string_buffer));
 	strcat(dest_string,dev_name);
	strcat(dest_string,string_buffer);
	printf("%s\n",dest_string);
	int fd = open(dest_string,O_RDONLY);
	if(fd < 0){
		printf("Unable to send the message\n");
		return -1;
	}
	/*
	fprintf(fp,data);
	fclose(fp);*/
	char *ch = "0";
	ioctl(fd,IOCTL_SEND_MSG,ch);
	close(fd);
	return 0;
		
}
/*

int main(){

	Hyb_Send(0,"Arijit",10 );
	return 0;
}
*/
