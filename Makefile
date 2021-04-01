CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

all: exec

exec: list.o main.o huffman.o
	$(CC) $(CFLAGS) $^ -o $@

list.o: list.c list.h
	$(CC) -c $(CFLAGS) list.c

huffman.o: huffman.c list.h
	$(CC) -c $(CFLAGS) huffman.c

main.o: main.c list.h
	$(CC) -c $(CFLAGS) main.c 

clean:
	rm -f *.o *~