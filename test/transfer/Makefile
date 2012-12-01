LIB=/usr/include/ipc
CC=gcc
CFLAG=-c
LADD=-lrt

all: transfer

transfer: $(LIB)/Hyb_Send.o transfer.o
	$(CC) $(LIB)/Hyb_Send.o transfer.o -o transfer $(LADD)

transfer.o: transfer.c
	$(CC) $(CFLAG) $(LIB)/Hyb_Send.o transfer.c

clean:
	rm -rf *.o 
