#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ipc/libipc.h>


int main(){

	char *data = "This is the broadcasting message";	
	int dataLength = strlen(data);
 	Hyb_Broadcast(data,dataLength);
	return 0;
}
