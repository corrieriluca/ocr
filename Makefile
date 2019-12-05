# Makefile OCR

CC = gcc
CFLAGS = -W -Wall -Wextra -std=c99 -Werror -O3
CPPFLAGS = -MMD
LDFLAGS = -export-dynamic

# libraries
SDL = `pkg-config --cflags --libs sdl` -lSDL_image
GTK = `pkg-config --cflags --libs gtk+-3.0`
GSPELL = `pkg-config --cflags --libs gspell-1`
LM = -lm

SRC = src/ocr.c src/segmentation.c src/preprocessing.c src/matrix_tools.c src/image_operations.c

all: ocr tmp

ocr: $(SRC) src/main.c
	$(CC) -o $@.out src/main.c src/gui.c $(SRC) $(CFLAGS) $(CPPFLAGS) $(SDL) $(GTK) $(LM) $(GSPELL) $(LDFLAGS)

# to use the OCR without the GUI
cli: $(SRC) src/main-cli.c
	$(CC) -o ocr-$@.out src/main-cli.c $(SRC) $(CFLAGS) $(CPPFLAGS) $(SDL) $(GTK) $(LM)
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
