LIB=/usr/include/ipc
CC=gcc
CFLAG=-c
TFLAG=-pthread
LADD=-lrt
all: rcv send 

send: $(LIB)/Hyb_Broadcast.o brd_sender.o
	$(CC) $(LIB)/Hyb_Broadcast.o brd_sender.o -o send $(LADD)

brd_sender.o: brd_sender.c
	$(CC) $(CFLAG) $(LIB)/Hyb_Broadcast.o brd_sender.c 

rcv: $(LIB)/Hyb_Recv.o brd_receiver.o
	$(CC) $(LIB)/Hyb_Recv.o brd_receiver.o -o receive $(TFLAG)

brd_receiver.o: brd_receiver.c
	$(CC) $(CFLAG) $(LIB)/Hyb_Recv.o brd_receiver.c

clean:
	rm -rf *.o 
