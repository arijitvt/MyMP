#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "libipc.h"
#include "limit.h"

int Hyb_ASend(int dest, const char *data, int count )
{
	char string_buffer[10];
	sprintf(string_buffer,"%d",dest);
	const char *dev_name =  "/dev/ipty";
	char *dest_string = (char *)malloc(strlen(dev_name)+strlen(string_buffer));
 	strcat(dest_string,dev_name);
	strcat(dest_string,string_buffer);
#ifdef DEBUG
	printf("%s\n",dest_string);
#endif	
	while(1){
		FILE *fp = fopen(dest_string,"w");
		if(fp == NULL){
			printf("Unable to send the message\n");
			return -1;
		}
		fprintf(fp,"%s",data);
		fclose(fp);
		usleep(limit);
	}
	return 0;
		
}

/*
int main(){

	Hyb_ASend(0,"Arijit0",10 );
	return 0;
}
*/
