#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ipc/libipc.h>


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
