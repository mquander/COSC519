OBJECTS = reca.o usereca.o

CC=gcc

CFLAGS= -c -Wall

run: reca.o usereca.o
	$(CC) reca.o -o reca
	$(CC) usereca.o -o usereca
	
reca.o: reca.c
	$(CC) $(CFLAGS) reca.c -c

usereca.o: usereca.c
	$(CC) $(CFLAGS) usereca.c
	
clean:
	rm -rf *o reca usereca
