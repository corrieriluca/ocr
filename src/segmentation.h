#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#define MAX_LINE_NUMBER 100 // for the memory allocation
#define MAX_CHARACTER_NUMBER 100 // for the memory allocation
#define MATRIX_SIZE 16 // size of square matrix for input in the NN

#include "image_operations.h"

// Represents a character
typedef struct Character
{
    size_t startingPoint;
    size_t endPoint;
    size_t *matrix; // the matrix of 0 and 1 representing the character
    char character; // to be determined by the neural network
} Character;

// Represents a text line
typedef struct Line
{
    size_t startingPoint; // the starting point of the line in the matrix
    size_t endPoint;      // the end point of the line in the matrix
    size_t nbCharacters;
    Character *characters; // characters array of this line
} Line;

size_t Find_Lines(Line lines[],
                  size_t binarized_matrix[],
                  size_t height, size_t width);

void Debug_Lines(Line lines[], size_t nbLines);

void Find_Characters(Line *line, size_t binarized_matrix[], size_t width);

void Get_Characters(Line *line, size_t binarized_matrix[], size_t width);

void Save_Segmentation(SDL_Surface *image, Line lines[], size_t nbLines);

#endif