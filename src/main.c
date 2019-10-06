/*
   ___            _ _        
  / __\___   __ _(_) |_ ___  
 / /  / _ \ / _` | | __/ _ \ 
/ /__| (_) | (_| | | || (_) |
\____/\___/ \__, |_|\__\___/ 
            |___/            

SIMPLE OPTICAL CHARACTER RECOGNITION
*/

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "preprocessing.h"
#include "image_operations.h"
#include "matrix_tools.h";

int main(int argc, char** argv)
{
    if (argc != 2)
        errx(1, "Error");
    
    SDL_Surface *image_surface;
    init_sdl();
    image_surface = load_image(argv[1]);
    size_t *matrix = image_to_bin_matrix(image_surface);
    printf("image_to_bin_matrix called\nThe matrix is:\n");
    print_matrix(&matrix, image_surface->h, image_surface->w);

    return 0;
}
