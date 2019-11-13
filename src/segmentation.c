#include <stdio.h>
#include <stdlib.h>
#include "segmentation.h"
#include "image_operations.h"
#include "matrix_tools.h"

/* ****************** LINE SEGMENTATION *********************** */

/* This function finds the text lines on the image (binarized matrix) with
 * the XY-Cut algorithm. It returns the number of lines, and fills the array
 * lines[] with Line struct elements. (see "segmentation.h")
 */
size_t Find_Lines(Line lines[],
        size_t binarized_matrix[],
        size_t height, size_t width)
{
    size_t nbLines = 0;

    // boolean indicating the state of the last iteration
    int isInLine = 0;

    // indicating the index of the starting point of the current line
    size_t startingPoint = 0;

    for (size_t y = 0; y < height; y++)
    {
        // Sum of the black pixels on this line.
        // Also taken as boolean (we are inside a line)
        size_t isTherePixelsOnThisLine = 0;
        // Counting every black pixel (which are 1 in the matrix)
        for (size_t x = 0; x < width; x++)
            isTherePixelsOnThisLine += binarized_matrix[y * width + x];

        // In the case we have found a new line
        if (!isInLine && isTherePixelsOnThisLine)
        {
            startingPoint = y; // for creating Line object later
            isInLine = 1; // <=> True
            continue;
        }

        // In the case we are at the end of a line
        // (precedent iteration was in a line AND no pixel found in this
        // iteration)
        if (isInLine && !isTherePixelsOnThisLine)
        {
            // We create a Line object, and fill the lines[] array
            Line newLine;
            newLine.startingPoint = startingPoint;
            newLine.endPoint = y; // this current height
            lines[nbLines] = newLine;
            nbLines++;
            isInLine = 0; // <=> False
        }
    }

    // For the last line
    if (isInLine)
    {
        Line newLine;
        newLine.startingPoint = startingPoint;
        newLine.endPoint = height - 1;
        lines[nbLines] = newLine;
        nbLines++;
    }

    return nbLines;
}

// For debugging; shows the lines characteristics on the console
void Debug_Lines(Line lines[], size_t nbLines)
{
    printf("---- Detected Lines ----\n");
    for (size_t i = 0; i < nbLines; i++)
    {
        printf("-- Line %zu --\n", i);
        printf("Starting Index : %zu\n", lines[i].startingPoint);
        printf("End Index : %zu\n", lines[i].endPoint);
    }
}

/* ******************** CHARACTER SEGMENTATION *********************** */

/* This function finds all the characters in the given line with the XY-Cut
 * algorithm. It fills the 'characters' array of the given line.
 * It is the same process as the Find_Lines function but on the X axis.
 */
void Find_Characters(Line *line, size_t binarized_matrix[], size_t width)
{
    size_t upperBound = line->startingPoint;
    size_t lowerBound = line->endPoint;
    size_t nbCharacters = 0;
    int isInChar = 0; // boolean indicating the state of the last iteration
    size_t startingPoint = 0; // <=> Character.startingPoint

    // total space width between characters for computing averageSpace
    size_t totalSpace = 0;

    for (size_t x = 0; x < width; x++)
    {
        // Sum of the black pixels on this line.
        // Also taken as boolean (we are inside a character)
        size_t isTherePixelsOnThisLine = 0;
        // Counting for black pixels
        for (size_t y = upperBound; y <= lowerBound; y++)
            isTherePixelsOnThisLine += binarized_matrix[y * width + x];

        // In the case we have found a new character
        if (!isInChar && isTherePixelsOnThisLine)
        {
            startingPoint = x;
            isInChar = 1; // <=> True

            if (nbCharacters) // <=> nbCharacters > 0
            {
                // computes the space width between this new character
                // and the previous one
                totalSpace += startingPoint -
                    line->characters[nbCharacters - 1].endPoint;
            }
        }

        // In the case we are at the end of a character
        if (isInChar && !isTherePixelsOnThisLine)
        {
            Character character;
            character.startingPoint = startingPoint;
            character.endPoint = x;
            line->characters[nbCharacters] = character;
            nbCharacters++;
            isInChar = 0; // <=> False
        }
    }

    line->nbCharacters = nbCharacters;

    // fills the avergeSpace field once this line is finished
    if (nbCharacters > 1)
        line->averageSpace = totalSpace / (nbCharacters - 1);
}

/* This is the main function for character segmentation. It calls
 * Find_Characters in order to find where are the characters in the image and
 * then associate to each character a square matrix of size MATRIX_SIZE (which
 * is defined in 'segmentation.h') in order to have a correct input to the
 * neural network.
 */
void Get_Characters(Line *line, size_t binarized_matrix[], size_t width)
{
    // Find where are the characters on the matrix for this line
    Find_Characters(line, binarized_matrix, width);

    for (size_t i = 0; i < line->nbCharacters; i++)
    {
        Character *current = &(line->characters[i]);

        size_t charHeight = line->endPoint - line->startingPoint;
        size_t charWidth = current->endPoint - current->startingPoint;

        size_t *extracted = extract_matrix(binarized_matrix, width,
            line->startingPoint, current->startingPoint, charHeight, charWidth);

        current->matrix = resize_matrix(extracted, charHeight, charWidth);

        // for debugging
        print_matrix_double(current->matrix, MATRIX_SIZE, MATRIX_SIZE);

        free(extracted); // needed
    }
}

/* ************************** MISC *********************************** */

// For debugging; draws the lines of the XY-Cut on the image, and save it to
// the tmp/ folder.
void Save_Segmentation(SDL_Surface *image, Line lines[], size_t nbLines)
{
    for (size_t i = 0; i < nbLines; i++)
    {
        size_t lineStartingPoint = lines[i].startingPoint;
        size_t lineEndPoint = lines[i].endPoint;

        // LINES BOUNDS
        draw_horizontal_line(image, lineStartingPoint);
        draw_horizontal_line(image, lineEndPoint);

        // CHARACTERS BOUNDS
        for (size_t j = 0; j < lines[i].nbCharacters; j++)
        {
            Character current = lines[i].characters[j];
            draw_vertical_line(image, current.startingPoint,
                            lineStartingPoint, lineEndPoint);
            draw_vertical_line(image, current.endPoint,
                            lineStartingPoint, lineEndPoint);
        }
    }

    save_image(image, "tmp/segmentation.bmp");
    printf("---- Segmentation saved ---- => tmp/segmentation.bmp\n");
}