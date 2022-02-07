OBJECTS = hellothread.o

CC=gcc

CFLAGS= -c -Wall

hellothread: hellothread.c
	$(CC) -o hellothread -pthread -lpthread hellothread.c
	
clean: 
	rm -rf *o hellothread
