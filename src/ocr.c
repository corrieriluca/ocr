#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <gtk/gtk.h>
#include "image_operations.h"
#include "matrix_tools.h"
#include "preprocessing.h"
#include "segmentation.h"

gchar* ocr_main(char* image_path)
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

    // Get Characters per Line
    for (size_t i = 0; i < nbLines; i++)
    {
        Line *current = &lines[i];
        current->characters = calloc(MAX_CHARACTER_NUMBER, sizeof(Character));
        Get_Characters(current, binarized_matrix, image_width);

        printf("On line %zu : %zu characters found\n",
                    i, current->nbCharacters);
    }

    // save the image of the segmentation for the debugging (in the tmp folder)
    Save_Segmentation(image_surface, lines, nbLines);

    // Character Recognition
    printf("Recognized text :\n");
    gchar *result = "";
    for (size_t j = 0; j < nbLines; j++)
    {
        for (size_t k = 0; k < lines[j].nbCharacters; k++)
        {
            // HERE THE NN ANALYSES lines[j].characters[k].matrix
            //printf("-");
            result = g_strconcat(result, "-", NULL);

            // is there a space after this character ?
            if (k + 1 < lines[j].nbCharacters &&
                    lines[j].characters[k + 1].startingPoint -
                    lines[j].characters[k].endPoint >
                    lines[j].averageSpace * 1.5)
            {
                //printf(" ");
                result = g_strconcat(result, " ", NULL);
            }

            free(lines[j].characters[k].matrix); // calloc in matrix_tools.c
        }
        //printf("\n");
        result = g_strconcat(result, "\n", NULL);
        free(lines[j].characters); // calloc previously
    }

    free(lines); // calloc previously

    SDL_FreeSurface(image_surface);

    return result;
}
