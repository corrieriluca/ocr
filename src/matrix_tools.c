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
            //printf("%f ", matrix[j * width + k]);
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

// FUNCTIONS FOR BILINEAR INTERPOLATION ----------------------------------------

size_t getpixel(size_t matrix[], size_t width, size_t x, size_t y)
{
    return matrix[(y * width) + x];
}

float lerp(float s, float e, float t)
{
    return s + (e - s) * t;
}

float blerp(float c00, float c10, float c01, float c11, float tx, float ty)
{
    return lerp(lerp(c00, c10, tx), lerp(c01, c11, tx), ty);
}

void putpixel(double matrix[], size_t width, size_t x, size_t y, double value)
{
    matrix[(y * width) + x] = value;
}

void scale_matrix(size_t src[], size_t src_width, size_t src_height,
                    double dst[])
{
    int newWidth = MATRIX_SIZE;
    int newHeight = MATRIX_SIZE;
    int x, y;

    for(x = 0, y = 0; y < newHeight; x++)
    {
        if(x > newWidth)
        {
            x = 0; y++;
        }

        float gx = x / (float)(newWidth) * (src_width - 1);
        float gy = y / (float)(newHeight) * (src_height - 1);
        int gxi = (int)gx;
        int gyi = (int)gy;
        double result = 0;
        float c00 = (float)getpixel(src, src_width, gxi, gyi);
        float c10 = (float)getpixel(src, src_width, gxi+1, gyi);
        float c01 = (float)getpixel(src, src_width, gxi, gyi+1);
        float c11 = (float)getpixel(src, src_width, gxi+1, gyi+1);

        result = (double)blerp(c00, c10, c01, c11, gx - gxi, gy - gyi);

        putpixel(dst, newWidth, x, y, result);
    }
}

// -----------------------------------------------------------------------------

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
            result[row * resultWidth + col] = sourceMatrix[
                (startingRow + row) * width + (startingColumn + col)
            ];
        }
    }

    return result;
}

/* Returns the result height after having cropped the matrix from its blank
 * space
 */
void remove_blank(size_t sourceMatrix[], size_t height, size_t width,
                    size_t res[])
{
    // Finding the first row with ones
    size_t startingRow = 0;
    for (size_t row = 0; row < height; row++)
    {
        size_t nbOne = 0;
        for (size_t col = 0; col < width; col++)
        {
            nbOne += sourceMatrix[row * width + col];
        }
        if (nbOne) // > 0
        {
            startingRow = row - 1;
            break;
        }
    }

    // Finding the first row with only zeros until the end
    size_t endingRow = 0;
    for (size_t row = 0; row < height; row++)
    {
        size_t nbOne = 0;
        for (size_t col = 0; col < width; col++)
        {
            nbOne += sourceMatrix[row * width + col];
        }
        if (nbOne) // > 0
            endingRow = row + 1;
    }

    size_t resultHeight = height - startingRow;

    if (endingRow >= height)
        endingRow = 0;

    if (endingRow) // != 0
        resultHeight -= (height - endingRow);

    res[0] = resultHeight;
    res[1] = startingRow;
}

/* Takes an extracted matrix and tries to remove white parts up and down */
size_t *crop_matrix(size_t sourceMatrix[], size_t blankRes[], size_t width)
{
    size_t *result = calloc(blankRes[0] * width, sizeof(size_t));
    // Filling result
    for (size_t row = 0; row < blankRes[0]; row++)
    {
        for (size_t col = 0; col < width; col++)
        {
            result[row * width + col] = sourceMatrix[
                (blankRes[1] + row) * width + col
            ];
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
    /*printf("%d / %zu\n", MATRIX_SIZE, width);
    float scalex = (float)MATRIX_SIZE / width;
    float scaley = (float)MATRIX_SIZE / height;
    printf("ScaleX = %f\n", scalex);
    printf("ScaleY = %f\n", scaley);*/

    double *result = calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(double));

    // Determine the size of the larger square for the 'matrix_in_square'
    // function. Using MATRIX_SIZE is necessary to obtain a divisor of it.
    size_t squareSize = (height > width) ? height : width;

    size_t *square = calloc(squareSize * squareSize, sizeof(size_t));

    matrix_in_square(matrix, square, height, width, squareSize);

    //resize_square_matrix(square, result, squareSize, MATRIX_SIZE);

    scale_matrix(square, squareSize, squareSize, result);

    free(square); // needed
    return result;
}