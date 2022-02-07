OBJECTS = dining.o

CC=gcc

CFLAGS= -c -Wall

dining: dining.c
	$(CC) -o dining -pthread -lpthread dining.c
	
clean: 
	rm -rf *o dining
