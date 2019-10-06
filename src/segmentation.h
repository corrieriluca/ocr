#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#define MATRIX_SIZE 16 // size of square matrix for input in the NN

// Represent a character
typedef struct Character
{
    size_t startingPoint;
    size_t endPoint;
    size_t *matrix; // the matrix of 0 and 1 representing the character
    char character; // to be determined by the neural network
} Character;

// Represent a text line
typedef struct Line
{
    size_t startingPoint;
    size_t endPoint;
    size_t nbCharacters;
    Character *characters;
} Line;

#endif