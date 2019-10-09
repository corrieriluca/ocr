#ifndef IMAGE_OPERATIONS_H_
#define IMAGE_OPERATIONS_H_

#include <stdlib.h>
#include <SDL.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void init_sdl();
SDL_Surface *load_image(char *path);
SDL_Surface *display_image(SDL_Surface *img);
void wait_for_keypressed();

// from David Bouchet's pixel_operations.c
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void update_surface(SDL_Surface *screen, SDL_Surface *image);

void save_image(SDL_Surface *image, char *name);

#endif
