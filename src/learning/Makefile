# Makefile Learning process

CC = gcc
CFLAGS = -W -Wall -Wextra -std=c99 -Werror -O3
CPPFLAGS = `pkg-config --cflags sdl` -MMD
LDFLAGS =
LDLIBS = `pkg-config --libs sdl` -lSDL_image -lm

SRC = learning.c ../image_operations.c ../segmentation.c ../preprocessing.c ../matrix_tools.c

all: learn

learn: $(SRC)
	$(CC) -o $@.out $(SRC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS)

.PHONY: clean

clean:
	${RM} learn.out
	${RM} learn.d

# END
