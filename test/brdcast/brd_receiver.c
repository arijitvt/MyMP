#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include <ipc/libipc.h>

#define NO_OF_THREADS 4

void receive(void *dev){
	int *dev_id = (int *) dev;
	char data_buffer[100];
//	while(1){		 
		Hyb_Recv(*dev_id,data_buffer,100);
		if(strcmp(data_buffer,"#") == 0){
			printf("Escape symbol is received");
			return ;
			//break;
		}
		if(strlen(data_buffer) != 0){	
			printf("FROM THE DEVICE : %d\t%s\n",*dev_id,data_buffer);
			memset(data_buffer,'0',100);
		}
//	}
}

int main(){
	pthread_t threads[NO_OF_THREADS];
	int i ;
	void *status;
	for(i =0 ; i < NO_OF_THREADS; ++i){
		pthread_create(&threads[i],NULL,receive,(void*)&i);
		pthread_join(threads[i],&status);
	}
	return 0;
}
