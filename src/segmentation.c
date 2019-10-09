#include <stdio.h>
#include <stdlib.h>
#include "segmentation.h"
#include "image_operations.h"

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
    printf("------- Debugging lines -------\n");
    for (size_t i = 0; i < nbLines; i++)
    {
        printf("--- Line %zu ---\n", i);
        printf("Starting Point : %zu\n", lines[i].startingPoint);
        printf("End Point : %zu\n", lines[i].endPoint);
    }
}

// For debugging; draws the lines of the XY-Cut on the image, and save it to
// the tmp/ folder.
void Show_Segmentation(SDL_Surface *image, Line lines[], size_t nbLines)
{
    for (size_t i = 0; i < nbLines; i++)
    {
        draw_horizontal_line(image, lines[i].startingPoint);
        draw_horizontal_line(image, lines[i].endPoint);
    }

    save_image(image, "tmp/segmentation.bmp");
}