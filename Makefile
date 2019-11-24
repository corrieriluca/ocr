# Makefile OCR

CC = gcc
CFLAGS = -W -Wall -Wextra -std=c99 -Werror -O3
CPPFLAGS = `pkg-config --cflags sdl` -MMD
LDFLAGS =
LDLIBS = `pkg-config --libs sdl` -lSDL_image -lm `pkg-config --cflags --libs gtk+-3.0`

SRC = src/ocr.c src/gui.c src/segmentation.c src/preprocessing.c src/matrix_tools.c src/image_operations.c

all: ocr tmp

ocr: $(SRC) src/main.c
	$(CC) -o $@.out src/main.c $(SRC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS) -export-dynamic

# to use the OCR without the GUI
cli: $(SRC) src/main-cli.c
	$(CC) -o ocr-$@.out src/main-cli.c $(SRC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS)
	mkdir -p tmp

tmp:
	mkdir -p tmp

.PHONY: clean

clean:
	${RM} ocr.out
	${RM} ocr.d
	${RM} ocr-cli.out
	${RM} ocr-cli.d
	if [ -d tmp ]; then rm -r tmp; fi

-include ${DEP}

# END
