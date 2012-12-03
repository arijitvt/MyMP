LIB=/usr/include/ipc
CC=gcc
CFLAG=-c
TFLAG=-pthread
LADD=-lrt

all: rcv send 

send: $(LIB)/Hyb_Broadcast.o m_sender.o
	$(CC) $(LIB)/Hyb_Send.o m_sender.o -o send $(TFLAG) $(LADD)

m_sender.o: m_sender.c
	$(CC) $(CFLAG) $(LIB)/Hyb_Send.o m_sender.c 

rcv: $(LIB)/Hyb_Recv.o m_receiver.o
	$(CC) $(LIB)/Hyb_Recv.o m_receiver.o -o receive $(TFLAG)

m_receiver.o: m_receiver.c
	$(CC) $(CFLAG) $(LIB)/Hyb_Recv.o m_receiver.c

clean:
	rm -rf *.o 
