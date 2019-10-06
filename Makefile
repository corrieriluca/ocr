# Makefile OCR

CC = gcc
CFLAGS = -W -Wall -Wextra -std=c99 -Werror -O3
CPPFLAGS = `pkg-config --cflags sdl` -MMD
LDFLAGS =
LDLIBS = `pkg-config --libs sdl` -lSDL_image -lm

SRC = src/segmentation.c src/preprocessing.c src/matrix_tools.c src/main.c src/image_operations.c

all: ocr tmp

ocr: $(SRC)
	$(CC) -o $@.out $(SRC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS)

tmp:
	mkdir -p tmp

.PHONY: clean

clean:
	${RM} ocr.out
	${RM} ocr.d
	rm -r tmp

-include ${DEP}

# END
