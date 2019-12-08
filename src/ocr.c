#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <gtk/gtk.h>
#include "image_operations.h"
#include "matrix_tools.h"
#include "preprocessing.h"
#include "segmentation.h"
#include "neural/test/print.h"
#include "neural/test/save_and_load.h"

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

    // Initializing the Neural Network
    //Choosing the number of input neurons
    int nb_input_neurons = 16*16;

    //Choosing the number of output neurons
    int nb_output_neurons = 67;

    //Choosing the number of neurons in the hidden layer
    int nb_hidden_layer_neurons = 12000;

    //Init all the weights, biais and activation point
    //-------------------------------------------------------------------------
    int size_a0[] = {nb_input_neurons,1};
    double a0[size_a0[0] * size_a0[1]];

    int size_a1[] = {nb_hidden_layer_neurons,1};
    double a1[size_a1[0] * size_a1[1]];

    int size_a2[] = {nb_output_neurons,1};
    double a2[size_a2[0] * size_a1[1]];

    int size_w0[] = {nb_hidden_layer_neurons,nb_input_neurons};
    double *weight0 = malloc((size_w0[0]*size_w0[1]) * sizeof(double));

    int size_w1[] = {nb_output_neurons,nb_hidden_layer_neurons};
    double *weight1 = malloc((size_w1[0]*size_w1[1]) * sizeof(double));

    int size_b0[] = {nb_hidden_layer_neurons,1};
    double b0[size_b0[0] * size_b0[1]];

    int size_b1[] = {nb_output_neurons,1};
    double b1[size_b1[0] * size_b1[1]];

    file_to_mat(weight0, weight1, b0, b1,
            size_w0, size_w1, size_b0, size_b1,
            "weights_and_biais.ocr");

    // Character Recognition
    printf("Recognized text :\n");
    gchar *result = "";
    for (size_t j = 0; j < nbLines; j++)
    {
        for (size_t k = 0; k < lines[j].nbCharacters; k++)
        {
            // HERE THE NN ANALYSES lines[j].characters[k].matrix
            char resultChar = recognize(lines[j].characters[k].matrix,
                weight0, weight1, a0, a1, a2, b0, b1, size_w0, size_w1,
                size_a0, size_a1, size_a2, size_b0, size_b1);
            char resultString[2] = { resultChar, 0 };
            result = g_strconcat(result, resultString, NULL);

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

    printf("Recognition done !\n");

    free(lines); // calloc previously

    free(weight0);
    free(weight1);

    SDL_FreeSurface(image_surface);

    return result;
}
