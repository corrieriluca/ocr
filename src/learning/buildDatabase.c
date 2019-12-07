#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "../image_operations.h"
#include "../preprocessing.h"
#include "../segmentation.h"
#include "../matrix_tools.h"
#include "parser.h"

int main_building(char* image_path, char* text_path, FILE* matrix_database, FILE* char_database)
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

    printf("Total number of characters detected : %zu\n", nbCharactersTotal);

    // save the image of the segmentation for the debugging (in the tmp folder)
    Save_Segmentation(image_surface, lines, nbLines);

    // Character association to the wantedCharacter and building the .ocr Database file
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

            // Writing the corresponding character to the char_database
            fputc(getCharacterFromFile(text_path, currentCharacterIndex), char_database);
            fputc('\n', char_database); //newline char

            //Writing the matrix in the matrix_database
            for (size_t m = 0; m < MATRIX_SIZE * MATRIX_SIZE; m++)
            {
                char val;
                val = lines[j].characters[k].matrix[m] == 1.0 ? '1' : '0';
                fputc(val, matrix_database);
            }
            fputc('\n', matrix_database); // newline char

            free(lines[j].characters[k].matrix); // calloc in matrix_tools.c
        }
        free(lines[j].characters); // calloc previously
    }

    free(lines); // calloc previously

    SDL_FreeSurface(image_surface);

    return 0;
}

int main()
{
    FILE *matrix_database;
    FILE *char_database;
    matrix_database = fopen("matrix_database.ocr", "w+");
    char_database = fopen("character_database.ocr", "w+");

    for (size_t i = 0; i < 27; i++)
    {
        printf("\n------------- LOADING %zu.png... -----------------\n\n", i);
        char image_path[40];
        snprintf(image_path, 40, "../../samples/Training/%zu.png", i);
        char text_path[40];
        snprintf(text_path, 40, "../../samples/Training/%zu.txt", i);

        main_building(image_path, text_path, matrix_database, char_database);
    }

    fclose(matrix_database);
    fclose(char_database);
    
    FILE *matrix_database_test;
    FILE *char_database_test;
    matrix_database_test = fopen("matrix_database_test.ocr", "w+");
    char_database_test = fopen("character_database_test.ocr", "w+");

		printf("\n------------- LOADING Lorem_test.png... -----------------\n\n");
		char image_path[40];
		snprintf(image_path, 40, "../../samples/Lorem_test.png");
		char text_path[40];
		snprintf(text_path, 40, "../../samples/Lorem_test.txt");

		main_building(image_path, text_path, matrix_database_test, char_database_test);

    fclose(matrix_database_test);
    fclose(char_database_test);
   

    return 0;
}
