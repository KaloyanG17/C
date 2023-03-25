CC = gcc
CFLAGS = -Wall -Wextra -g

all: single byn

single: beggar.o single.o
	$(CC) $(CFLAGS) beggar.o single.o -o single

byn: beggar.o byn.o
	$(CC) $(CFLAGS) beggar.o byn.o -o byn

beggar.o: beggar.c beggar.h
	$(CC) $(CFLAGS) -c beggar.c

single.o: single.c beggar.h
	$(CC) $(CFLAGS) -c single.c

byn.o: byn.c beggar.h
	$(CC) $(CFLAGS) -c byn.c

clean:
	rm -f beggar.o single.o demo