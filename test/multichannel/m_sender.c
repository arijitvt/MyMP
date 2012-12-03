#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ipc/libipc.h>
#include<pthread.h>
#include "mchannel.h"



pthread_mutex_t thread_mutex;
int id = 0 ;

void send(){
	int dev_id = -1;
	pthread_mutex_lock(&thread_mutex);
	dev_id = id;
	++id;
	pthread_mutex_unlock(&thread_mutex);
	
	struct 	timespec starttime;
	struct timespec endtime;

	char *data_buffer = fifty_char_msg;
	int dataLength= strlen(data_buffer);
	printf("Data in the buffer %s with length %d\n",data_buffer,dataLength);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&starttime);
	Hyb_Send(dev_id,data_buffer,dataLength);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&endtime);
	printf("Time taken in nano secs %lu for message length %d\n",(endtime.tv_nsec-starttime.tv_nsec),dataLength);
}


int main(){
	
	pthread_t threads[NO_OF_THREADS];
	int i ;
	void *status;
	pthread_mutex_init(&thread_mutex,NULL);
	for(i =0 ; i < NO_OF_THREADS; ++i){
		pthread_create(&threads[i],NULL,(void*)send,NULL);
	}
	for(i =0 ; i < NO_OF_THREADS; ++i){
		pthread_join(threads[i],&status);
	}
	pthread_mutex_destroy(&thread_mutex);
	

	return 0;
}
