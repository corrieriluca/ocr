#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "../image_operations.h"
#include "../preprocessing.h"
#include "../segmentation.h"
#include "../matrix_tools.h"

#define CHARACTER_NUMBER 67

int main()
{
    SDL_Surface *character_surface;
    init_sdl();
    char letters[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?'0123456789";

    printf("-------------- LEARNING PROCESS -----------------\n\n");
    printf("--- LOADING CHARACTERS ---\n");

    for (size_t i = 0; i < CHARACTER_NUMBER; i++)
    {
        FILE *matrix_file;
        char dbPath[20];
        snprintf(dbPath, 20, "database/%zu.txt", i);
        matrix_file = fopen(dbPath, "w+");

        printf("Loading arial/%zu.png => It's a '%c'\n", i, letters[i]);
        char path[15];
        snprintf(path, 15, "arial/%zu.png", i);

        character_surface = load_image(path);

        binarize(character_surface);
        size_t *bin_matrix = calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(size_t));
        image_to_bin_matrix(character_surface, bin_matrix);

        double *char_mat = calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(double));
        for (size_t j = 0; j < MATRIX_SIZE * MATRIX_SIZE; j++)
            char_mat[j] = (double)bin_matrix[j];

        //Writing the matrix in the matrix_file
        for (size_t m = 0; m < MATRIX_SIZE * MATRIX_SIZE; m++)
        {
            char val;
            val = char_mat[m] == 1.0 ? '1' : '0';
            fputc(val, matrix_file);
        }
        fputc('\n', matrix_file); // newline char

        free(bin_matrix);
        free(char_mat);
        fclose(matrix_file);
    }

    SDL_FreeSurface(character_surface);

    return 0;
}