CC = gcc
CFLAGS = -Wall -Wextra

all: main

main: main.o airTrip.o
	$(CC) $(CFLAGS) -o main main.o airTrip.o

main.o: main.c airTrip.h
	$(CC) $(CFLAGS) -c main.c

airTrip.o: airTrip.c airTrip.h
	$(CC) $(CFLAGS) -c airTrip.c

clean:
	rm -f main main.o airTrip.o
