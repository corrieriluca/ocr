#ifndef IMAGE_OPERATIONS_H_
#define IMAGE_OPERATIONS_H_

#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void init_sdl();
SDL_Surface *load_image(char *path);

// from David Bouchet's pixel_operations.c
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void update_surface(SDL_Surface *screen, SDL_Surface *image);

void save_image(SDL_Surface *image, char *path);

void draw_horizontal_line(SDL_Surface *image, size_t line);
void draw_vertical_line(SDL_Surface *image, size_t column,
                        size_t start, size_t end);

#endif
