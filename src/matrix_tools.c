#include <stdio.h>
#include <stdlib.h>
#include "matrix_tools.h"
#include "segmentation.h"

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

// Print a matrix only filled with 0.0 and 1.0 in the console (doubles)
void print_matrix_double(double matrix[], size_t height, size_t width)
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
            if (matrix[j * width + k] == 1.0)
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

/* This functions puts the source matrix into a larger squared one
 * which has already been declared previously with calloc.
 */
void matrix_in_square(size_t matrix[], size_t square[], size_t height,
        size_t width, size_t squareSize)
{
    size_t startingRow = squareSize / 2 - height / 2;
    size_t startingCol = squareSize / 2 - width / 2;

    for (size_t row = 0; row < height; row++)
    {
        for (size_t col = 0; col < width; col++)
        {
            square[(startingRow + row) * squareSize + (startingCol + col)] =
                matrix[row * width + col];
        }
    }
}

/* This function resizes a square matrix of size squareSize into a smaller one
 * of size resizedSize (with resizedSize being a divisor of squareSize)
 */
void resize_square_matrix(size_t square[], double resized[],
        size_t squareSize, size_t resizedSize)
{
    // ratio is size_t because resizedSize divides squareSize
    size_t ratio = squareSize / resizedSize;

    // double for loop inside the resized matrix !
    for (size_t row = 0; row < resizedSize; row++)
    {
        for (size_t col = 0; col < resizedSize; col++)
        {
            // Counting for the number of ones in the square matrix
            // double for loop inside the square matrix !
            size_t nbOne = 0;
            for (size_t i = row * ratio; i < (row + 1) * ratio; i++)
            {
                for (size_t j = col * ratio; j < (col + 1) * ratio; j++)
                    if (square[i * squareSize + j]) // == 1
                        nbOne++;
            }
            double value = (nbOne / ratio >= 0.4) ? 1.0 : 0.0;
            resized[row * resizedSize + col] = value;
        }
    }
}

/* This functions returns the transformed matrix 'matrix' into a squared one
 * of size MATRIX_SIZE * MATRIX_SIZE (defined in "segmentation.h").
 * Return type is double for Character matrix
 */
double *resize_matrix(size_t matrix[], size_t height, size_t width)
{
    double *result = calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(double));

    // Determine the size of the larger square for the 'matrix_in_square'
    // function. Using MATRIX_SIZE is necessary to obtain a divisor of it.
    size_t squareSize = (height > width) ?
        height + (MATRIX_SIZE - height % MATRIX_SIZE) :
        width + (MATRIX_SIZE - width % MATRIX_SIZE);

    size_t *square = calloc(squareSize * squareSize, sizeof(size_t));

    matrix_in_square(matrix, square, height, width, squareSize);

    resize_square_matrix(square, result, squareSize, MATRIX_SIZE);

    free(square); // needed
    return result;
}