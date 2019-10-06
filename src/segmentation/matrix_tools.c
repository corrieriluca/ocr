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

// Debugging
int main()
{
    size_t matrix[] = {0, 1, 1, 0, 1, 0};
    print_matrix(matrix, 2, 3);

    return 0;
}