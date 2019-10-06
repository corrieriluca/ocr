#include <stdio.h>
#include <stdlib.h>
#include "image_operations.h" // has SDL

// Grayscaling
void grayscale(SDL_Surface *image_surface)
{
    size_t width = image_surface->w;
    size_t height = image_surface->h;

    for (size_t x = 0; x < height; x++)
    {
        for (size_t y = 0; y < width; y++)
        {
            Uint32 pixel = get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            Uint8 average = 0.3 * r + 0.59 * g + 0.11 * b;
            pixel = SDL_MapRGB(image_surface->format,
                        average, average, average);
            put_pixel(image_surface, x, y, pixel);
        }
    }
}

// Temp function for binarization (Otsu later...)
void binarize_simple(SDL_Surface *image_surface)
{
    size_t width = image_surface->w;
    size_t height = image_surface->h;

    for (size_t x = 0; x < height; x++)
    {
        for (size_t y = 0; y < width; y++)
        {
            Uint32 pixel = get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            Uint8 average = 0.3 * r + 0.59 * g + 0.11 * b;
            if (average > 127)
                average = 255;
            else
                average = 0;
            pixel = SDL_MapRGB(image_surface->format,
                        average, average, average);
            put_pixel(image_surface, x, y, pixel);
        }
    }
}

// Convert the SDL_Surface into a matrix of 0 and 1
void image_to_bin_matrix(SDL_Surface *img_surface, size_t *bin_matrix)
{
	size_t width = img_surface->w;
	size_t height = img_surface->h;

	for (size_t y = 0; y < height; y++)                                            
	{                                                                           
        for (size_t x = 0; x < width; x++)                                         
        {
			Uint32 pixel = get_pixel(img_surface, x, y);
			Uint8 r, g, b;
			SDL_GetRGB(pixel, img_surface->format, &r, &g, &b);
            
            // 1 for black ; 0 for white
            bin_matrix[y * width + x] = (r == 0) ? 1 : 0;
		}
	}
}

// Main function of image preprocessing
size_t *image_to_matrix(SDL_Surface *image_surface)
{
    /* init_sdl(); // not necessary

    image_surface = load_image("my_image.bmp");
    screen_surface = display_image(image_surface);

    wait_for_keypressed(); */

    size_t width = image_surface->w;
    size_t height = image_surface->h;

    // Grayscale
    grayscale(image_surface);
    save_image(image_surface, "tmp/grayscale.bmp");

    // Binarization (basic for the moment)
    binarize_simple(image_surface);
    save_image(image_surface, "tmp/binarized.bmp");

    // Binary matrix creation
	size_t *bin_matrix = calloc(width*height, sizeof(size_t));
	image_to_bin_matrix(image_surface, bin_matrix);	

	SDL_FreeSurface(image_surface);

	return bin_matrix;
}