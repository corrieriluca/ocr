#include "ocr.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        errx(1, "Error: You must specify the path of the image");

    printf("%s\n", ocr_main(argv[1]));
    return EXIT_SUCCESS;
}
