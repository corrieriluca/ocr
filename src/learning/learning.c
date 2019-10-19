#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "../image_operations.h"
#include "../preprocessing.h"
#include "../segmentation.h"

int main()
{   
    SDL_Surface *character_surface;
    init_sdl();
    char letters[] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?'";
    
    Character characters[57];

    printf("-------------- LEARNING PROCESS -----------------\n\n");
    printf("--- LOADING CHARACTERS ---\n");
    
    for (size_t i = 0; i < 57; i++)
    {
        printf("Loading letters/%zu.png => It's a '%c'\n", i, letters[i]);
        char path[15];
        snprintf(path, 15, "letters/%zu.png", i);

        character_surface = load_image(path);
        size_t width = character_surface->w; // 16
        size_t height = character_surface->h; // 16

        binarize(character_surface);
        size_t *bin_matrix = calloc(width * height, sizeof(size_t));
        image_to_bin_matrix(character_surface, bin_matrix);
        
        double *char_mat = calloc(width * height, sizeof(double));
        for (size_t j = 0; j < width * height; j++)
            char_mat[j] = (double)bin_matrix[j];

        free(bin_matrix);

        // creating the character object;
        Character character;
        character.startingPoint = 0;
        character.endPoint = 0;
        character.matrix = char_mat;
        character.character = letters[i];
        // adding the character to the array of characters
        characters[i] = character;
    }

    SDL_FreeSurface(character_surface);

    printf("\nDEBUGGIN Characters array = [");
    for (size_t i = 0; i < 57; i++)
        printf("%c", characters[i].character);
    printf("]\n");

    // ----- HERE ARE THE CALLS TO FUNCTIONS FROM THE NN FOR TRAINING IT -------

    printf("\n--- SENDING CHARACTERS TO THE NEURAL NETWORK ---\n");

    return 0;
}