CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
all:
	$(CC) $(CFLAGS) -o http_server main.c
clean:
	rm -f http_server
