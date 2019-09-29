# Makefile
CC = gcc

CFLAGS = -W -Wall -Wextra -std=c99 -Werror -O3
CPPFLAGS =
LDFLAGS =
LDLIBS =

SRC = main.c
OBJ = ${SRC:.c=.o}

main: ${OBJ}

clean:
	${RM} ${OBJ} # remove object files
	${RM} main # remove main program

# END
