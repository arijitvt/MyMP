LIB=/usr/include/ipc
CC=gcc
CFLAG=-c
LADD=-lrt

all: transfer

transfer: $(LIB)/Hyb_ASend.o transfer.o
	$(CC) $(LIB)/Hyb_ASend.o transfer.o -o transfer $(LADD)

transfer.o: transfer.c
	$(CC) $(CFLAG) $(LIB)/Hyb_ASend.o transfer.c

clean:
	rm -rf *.o 
