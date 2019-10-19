#ifndef PREPROCESSING_H
#define PREPROCESSING_H

void binarize(SDL_Surface *image_surface);
void image_to_bin_matrix(SDL_Surface *img_surface, size_t *bin_matrix);
size_t *image_to_matrix(SDL_Surface *image_surface);

#endif