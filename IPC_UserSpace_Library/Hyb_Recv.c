#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "libipc.h"

int Hyb_Recv(int dest,char *data, int count)
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
	char data_buffer[300];
	int len = 10 ;

	while(1){
		FILE *fp = fopen(dest_string,"r");
		if(fp == NULL){
			printf("Unable to send the message\n");
			return -1;
		}
		fgets(data, 100 , fp);
		printf("%s",data);
/*		do{
			fscanf(fp,"%s",data);
			strcat(data_buffer,data);
			printf("%s\n",data);
		}while(data != NULL);
		len = strlen(data_buffer);	
		printf("data lenght : %d\n",len);
		fclose(fp);
		return 0;
		if(len > 1)*/
		break;
	}
	//return 0;
		
}

/*
int main(){
	
	char recv_buffer[256];
	Hyb_Recv(0,recv_buffer,256 );
	printf("From the main the recv buffer is %s\n",recv_buffer);
	return 0;
}

*/
