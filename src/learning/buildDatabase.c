#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "../image_operations.h"
#include "../preprocessing.h"
#include "../segmentation.h"
#include "../matrix_tools.h"
#include "parser.h"

int main_building(char* image_path, char* text_path)
{
    // Image loading
    SDL_Surface *image_surface;
    init_sdl();
    image_surface = load_image(image_path);
    size_t image_width = image_surface->w;
    size_t image_height = image_surface->h;
    save_image(image_surface, "tmp/original.bmp");

    // Pre-processing
    printf("------ Pre-processing started ------\n");
    size_t *binarized_matrix = image_to_matrix(image_surface);

    // Segmentation

    // Get Lines
    printf("------ Segmentation started ------\n");
    Line *lines = calloc(MAX_LINE_NUMBER, sizeof(Line));
    size_t nbLines = Find_Lines(lines, binarized_matrix,
                                image_height, image_width);
    Debug_Lines(lines, nbLines);

    size_t nbCharactersTotal = 0; //total number of characters

    // Get Characters per Line
    for (size_t i = 0; i < nbLines; i++)
    {
        Line *current = &lines[i];
        current->characters = calloc(MAX_CHARACTER_NUMBER, sizeof(Character));
        Get_Characters(current, binarized_matrix, image_width);

        nbCharactersTotal += current->nbCharacters;
        printf("On line %zu : %zu characters found\n",
               i, current->nbCharacters);
    }

    // save the image of the segmentation for the debugging (in the tmp folder)
    Save_Segmentation(image_surface, lines, nbLines);

    // Character Recognition
    printf("Recognized text :\n");
    for (size_t j = 0; j < nbLines; j++)
    {
        for (size_t k = 0; k < lines[j].nbCharacters; k++)
        {
            //searching the index of this Character IN THE IMAGE
            //sum of the nbcharacters of the previous lines
            size_t currentCharacterIndex = 0;
            for (size_t l = 0; l < j; l++)
            {
                currentCharacterIndex += lines[l].nbCharacters;
            }
            currentCharacterIndex += k; //counting this line

            // Filling 'character' attribute of this Character from the .txt file
            lines[j].characters[k].character = getCharacterFromFile(text_path, currentCharacterIndex);

            // HERE THE NN ANALYSES lines[j].characters[k].matrix
            printf("%c", lines[j].characters[k].character);
            //printf("-");

            // is there a space after this character ?
            if (k + 1 < lines[j].nbCharacters &&
                lines[j].characters[k + 1].startingPoint -
                        lines[j].characters[k].endPoint >
                    lines[j].averageSpace * 1.5)
            {
                printf(" ");
            }

            free(lines[j].characters[k].matrix); // calloc in matrix_tools.c
        }
        printf("\n");
        free(lines[j].characters); // calloc previously
    }

    free(lines); // calloc previously

    SDL_FreeSurface(image_surface);

    return 0;
}

int main()
{
    for (size_t i = 0; i < 3; i++)
    {
        printf("\n------------- LOADING Lorem%zu.png... -----------------\n\n", i);
        char image_path[40];
        snprintf(image_path, 40, "../../samples/Lorem/Lorem%zu.png", i);
        char text_path[40];
        snprintf(text_path, 40, "../../samples/Lorem/Lorem%zu.txt", i);

        main_building(image_path, text_path);
    }

    return 0;
}