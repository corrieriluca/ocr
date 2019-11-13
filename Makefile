# Makefile OCR

CC = gcc
CFLAGS = -W -Wall -Wextra -std=c99 -Werror -O3
CPPFLAGS = `pkg-config --cflags sdl` -MMD
LDFLAGS =
LDLIBS = `pkg-config --libs sdl` -lSDL_image -lm

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

SRC = src/segmentation.c src/preprocessing.c src/matrix_tools.c src/main.c src/image_operations.c

all: ocr tmp

ocr: $(SRC)
	$(CC) -o $@.out $(SRC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS)

# temporary, to test the gui without the rest
gui: src/gui.c src/main-gui.c
	$(CC) -o gui.out src/gui.c src/main-gui.c $(CFLAGS) $(GTKLIB) -export-dynamic

tmp:
	mkdir -p tmp

.PHONY: clean

clean:
	${RM} ocr.out
	${RM} ocr.d
	${RM} gui.out # temp
	rm -r tmp

-include ${DEP}

# END
