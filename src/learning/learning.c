#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "../image_operations.h"
#include "../preprocessing.h"
#include "../segmentation.h"
#include "../matrix_tools.h"

#define CHARACTER_NUMBER 67

int main(int argc, char** argv)
{
    if (argc != 2)
        errx(1, "Error: you must specify the folder of the samples");

    // Check if the argument is a folder
    if (argv[1][strlen(argv[1]) - 1] != '/')
        errx(2, "Error: you must add a '/' after the folder name");

    SDL_Surface *character_surface;
    init_sdl();
    char letters[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?'0123456789";

    Character characters[CHARACTER_NUMBER];

    printf("-------------- LEARNING PROCESS -----------------\n\n");
    printf("--- LOADING CHARACTERS ---\n");

    for (size_t i = 0; i < CHARACTER_NUMBER; i++)
    {
        printf("Loading %s%zu.png => It's a '%c'\n", argv[1], i, letters[i]);
        char path[15];
        snprintf(path, 15, "%s%zu.png", argv[1], i);

        character_surface = load_image(path);

        binarize(character_surface);
        size_t *bin_matrix = calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(size_t));
        image_to_bin_matrix(character_surface, bin_matrix);

        double *char_mat = calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(double));
        for (size_t j = 0; j < MATRIX_SIZE * MATRIX_SIZE; j++)
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

    printf("\nDEBUGGING Characters array = [");
    for (size_t i = 0; i < CHARACTER_NUMBER; i++)
        printf("%c", characters[i].character);
    printf("]\n");

    // ----- HERE ARE CALLED TO FUNCTIONS FROM THE NN FOR TRAINING IT -------

    printf("\n--- SENDING CHARACTERS TO THE NEURAL NETWORK ---\n");

    return 0;
}