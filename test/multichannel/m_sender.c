#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ipc/libipc.h>
#include "../benchmark.h"


#define NO_OF_THREADS 4


pthread_mutex_t thread_mutex;
int id = 0 ;

void receive(){
	int dev_id = -1;
	pthread_mutex_lock(&thread_mutex);
	dev_id = id;
	++id;
	pthread_mutex_unlock(&thread_mutex);
	char data_buffer = fifty_char_msg;
	Hyb_Recv(dev_id,data_buffer,100);
	if(strcmp(data_buffer,"#") == 0){
		printf("Escape symbol is received");
		return ;
	}
	if(strlen(data_buffer) != 0){	
		printf("FROM THE DEVICE : %d\t%s\n",dev_id,data_buffer);
		memset(data_buffer,'0',100);
	}
}


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
