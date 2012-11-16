#include<stdio.h>
#include<ipc/libipc.h>
#include<time.h>


int main(){
	char data[100];
	Hyb_Recv(0,data,100);
	printf("Data Received %s\n",data);
	return 0;
}
