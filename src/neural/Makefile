# Makefile NEURAL NET

CC = gcc
CFLAGS = -W -Wall -Wextra -std=c99 -Werror -O3
CPPFLAGS =
LDFLAGS =
LDLIBS = -lm

SRC = *.c

all: neural

neural: $(SRC)
	$(CC) -o $@.out $(SRC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS)

.PHONY: clean

clean:
	${RM} neural.out
	${RM} neural.d

-include ${DEP}

# END
