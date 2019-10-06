# Makefile OCR
TARGET = ocr

CC = gcc
CFLAGS = -W -Wall -Wextra -std=c99 -Werror -O3
CPPFLAGS =
LDFLAGS =

SDL = `pkg-config --cflags --libs sdl` -lSDL_image
LM = -lm

SRC = src/segmentation.c src/preprocessing.c src/matrix_tools.c src/main.c src/image_operations.c

all: $(TARGET) tmp

ocr: $(SRC)
	$(CC) -o $@ $(SRC) $(CFLAGS) $(SDL) $(LM)

tmp:
	mkdir -p tmp

.PHONY: clean
clean:
	# remove program file
	${RM} $(TARGET)
	# remove temp folder
	rm -r tmp
# END
