#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ipc/libipc.h>


int main(){

	char data[100];
	int dataLength = 1;
	while(dataLength != 0){
		printf("Enter the message: ");
		scanf("%s",data);
		int dataLength = strlen(data);
		if(dataLength == 0){
			printf("Can not send blank data\n");
			return;
		}
	 	Hyb_Broadcast(data,dataLength);
	}	
	return 0;
}
