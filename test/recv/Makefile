LIB=/usr/include/ipc
CC=gcc
CFLAG=-c

all: rcv

rcv: $(LIB)/Hyb_Recv.o receive.o
	$(CC) $(LIB)/Hyb_Recv.o receive.o -o receive

receive.o: receive.c
	$(CC) $(CFLAG) $(LIB)/Hyb_Recv.o receive.c

clean:
	rm -rf *.o 
