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

/* This function creates a matrix by extracting it from a source matrix at
 * a specified row and column, for specified width and column.
 * Used for extracting characters in the image binarized matrix.
*/
size_t *extract_matrix(size_t sourceMatrix[], size_t width,
                       size_t startingRow, size_t startingColumn,
                       size_t resultHeight, size_t resultWidth)
{
    size_t *result = calloc(resultHeight * resultWidth, sizeof(size_t));

    for (size_t row = 0; row < resultHeight; row++)
    {
        for (size_t col = 0; col < resultWidth; col++)
        {
            result[row * resultWidth + col] =
                sourceMatrix[(startingRow + row) * width + (startingColumn + col)];
        }
    }

    return result;
}