CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99
LDFLAGS = 

OBJ = main.o queue.o

prog: $(OBJ)
	$(CC) $(LDFLAGS) -o prog $(OBJ)

main.o: main.c queue.h
	$(CC) $(CFLAGS) -c main.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f *.o prog