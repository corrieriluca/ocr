#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <ctype.h>

char getCharacterFromFile(char* path, size_t characterIndex)
{
    FILE *input_file;
    input_file = fopen(path, "r");

    if (input_file == 0)
    {
        errx(1, "Cannot open the .txt file fir char");
    }

    char character = fgetc(input_file);
    size_t alphaIndex = 0;
    while (alphaIndex < characterIndex)
    {
        character = fgetc(input_file);
        if (isalpha(character) || ispunct(character) || isdigit(character))
            alphaIndex++;
    }

	fclose(input_file);

    return character;
}
