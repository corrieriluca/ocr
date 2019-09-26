# Override C compiler
CC=gcc
CFLAGS=-W -Wall -Wextra -std=c99 -Werror -O3
LDFLAGS=
CFILES=src/main.c

all: ocr

clean:
	rm -rf bin/ocr
	rm -rf src/*.o

ocr:
	$(CC) $(CFILES) -o bin/ocr $(LDFLAGS)