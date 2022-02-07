OBJECTS = parse-1.o parse-2.o

CC=gcc

CFLAGS= -c -Wall

run: parse-1.o parse-2.o
	$(CC) parse-1.o -o parse-1 parse-2.o -o parse-2

parse-1.o: parse-1.c
	$(CC) $(CFLAGS) parse-1.c

parse-2.o: parse-2.c
	$(CC) $(CFLAGS) parse-2.c
	
clean:
	rm -rf *o parse-1 parse-2
