# Makefile OCR

CC = gcc
CFLAGS = -W -Wall -Wextra -std=c99 -Werror -O3
CPPFLAGS = `pkg-config --cflags sdl` -MMD
LDFLAGS =
LDLIBS = `pkg-config --libs sdl` -lSDL_image -lm

SRC = src/segmentation.c src/preprocessing.c src/matrix_tools.c src/main.c src/image_operations.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: ocr tmp

ocr: ${OBJ}

tmp:
	mkdir -p tmp

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} ocr
	rm -r tmp

# END
