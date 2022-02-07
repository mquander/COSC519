OBJECTS = bank.o

CC=gcc

CFLAGS= -c -Wall

bank: bank.c
	$(CC) -o bank -pthread -lpthread bank.c
	
clean: 
	rm -rf *o bank
