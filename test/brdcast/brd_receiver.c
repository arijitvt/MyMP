#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include <ipc/libipc.h>

#define NO_OF_THREADS 4


pthread_mutex_t thread_mutex;
int id = 0 ;

void receive(){
	int dev_id = -1;
	pthread_mutex_lock(&thread_mutex);
	dev_id = id;
	++id;
	pthread_mutex_unlock(&thread_mutex);
	printf("ID is %d\n",dev_id);
	char data_buffer[100];
//	while(1){		
	printf("Before the call \n"); 
	Hyb_Recv(dev_id,data_buffer,100);
	printf("After the call \n"); 
	if(strcmp(data_buffer,"#") == 0){
		printf("Escape symbol is received");
		return ;
			//break;
	}
	if(strlen(data_buffer) != 0){	
		printf("FROM THE DEVICE : %d\t%s\n",dev_id,data_buffer);
		memset(data_buffer,'0',100);
	}
//	}
}

int main(){
	pthread_t threads[NO_OF_THREADS];
	int i ;
	void *status;
	pthread_mutex_init(&thread_mutex,NULL);
	for(i =0 ; i < NO_OF_THREADS; ++i){
		pthread_create(&threads[i],NULL,(void*)receive,NULL);
	}
	for(i =0 ; i < NO_OF_THREADS; ++i){
		pthread_join(threads[i],&status);
	}
	pthread_mutex_destroy(&thread_mutex);
	return 0;
}
