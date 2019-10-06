#include <stdio.h>
#include <stdlib.h>
#include "matrix_tools.h"

// Print a matrix only filled with 0 and 1 in the console
void print_matrix(size_t matrix[], size_t height, size_t width)
{
    printf("*");
    for (size_t i = 0; i < width; i++)
        printf("-");
    printf("*\n");

    for (size_t j = 0; j < height; j++)
    {
        printf("|");
        for (size_t k = 0; k < width; k++)
        {
            if (matrix[j * width + k]) // == 1
                printf("o");
            else
                printf(" ");
        }
        printf("|\n");
    }

    printf("*");
    for (size_t l = 0; l < width; l++)
        printf("-");
    printf("*\n");
}

// Fill randomly a matrix of size width * height with 0 and 1
void matrix_random_fill(size_t matrix[], size_t height, size_t width)
{
    for (size_t i = 0; i < width * height; i++)
        matrix[i] = (size_t)rand() % 2; // random values : 0 or 1
}

// Debugging
int main()
{
    size_t width = 16, height = 16;
    size_t *matrix = calloc(height*width, sizeof(size_t));
    matrix_random_fill(matrix, height, width);
    print_matrix(matrix, height, width);

    return 0;
}
