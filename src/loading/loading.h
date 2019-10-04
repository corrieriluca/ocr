#ifndef LOADING_H
#define LOADING_H

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);

#endif
