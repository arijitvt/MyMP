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
	FILE *fp = fopen(dest_string,"w");
	if(fp == NULL){
		printf("Unable to send the message\n");
		return -1;
	}
	char *data_buf = (char *) malloc(strlen(data)+3);
	strcpy(data_buf,data);
	strcat(data_buf,"\n");
	fprintf(fp,"%s",data_buf);
	fclose(fp);
	return 0;
		
}

/*
int main(){

	Hyb_Send(0,"Arijit",10 );
	return 0;
}
*/
