#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ipc/libipc.h>
#include "../benchmark.h"
/*
int main(){

	char data[100];
	int dataLength = 1;
	printf("Enter the message: ");
	gets(data);
	if(strcmp(data, "#") ==0){
		printf("Reached escape sequence\n");
		return 1;
	}
	dataLength = strlen(data);
	if(dataLength == 0){
		printf("Can not send blank data\n");
		return -1;
	}
	Hyb_Broadcast(data,dataLength);
	return 0;
}
*/

int main(){
	
	struct 	timespec starttime;
	struct timespec endtime;

	char *data = hundred_char_msg;
	int dataLength = -1;
	if(strcmp(data, "#") ==0){
		printf("Reached escape sequence\n");
		return 1;
	}
	dataLength = strlen(data);
	if(dataLength == 0){
		printf("Can not send blank data\n");
		return -1;
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&starttime);
	Hyb_Broadcast(data,dataLength);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&endtime);
	printf("Time taken in nano secs %lu for message length %d\n",(endtime.tv_nsec-starttime.tv_nsec),dataLength);

	return 0;
}
