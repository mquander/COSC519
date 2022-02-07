OBJECTS = votecounter.o mutex-count.o

CC=gcc

CFLAGS= -c -Wall


votecounter: votecounter.c
	$(CC) -o votecounter -pthread -lpthread votecounter.c
	
mutex-count: mutex-count.c
	$(CC) -o mutex-count -pthread -lpthread mutex-count.c
	
clean: 
	rm -rf *o votecounter mutex-count
