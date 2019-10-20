#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "image_operations.h" // has SDL

// Grayscaling
void grayscale(SDL_Surface *image_surface)
{
    size_t width = image_surface->w;
    size_t height = image_surface->h;

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
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

// Calculate the Otsu threshold
size_t otsu(SDL_Surface *image_surface, size_t h, size_t w)
{

	// Calculate histogram
	float histogram[256] = { 0.0F }; // Number of each levels of grey

        // Double 'for' to fill the histogram
        for (size_t y = 0; y < h; y++)
        {
                for (size_t x = 0; x < w; x++)
                {
                        Uint32 pixel = get_pixel(image_surface, x, y);
                        Uint8 r, g, b;
                        SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                        size_t graylevel = r;
                        histogram[graylevel] += 1;
                }
        }

	// Number of pixels
	int nb_pixels = w * h;

	float sum = 0;

	for (int i = 0 ; i < 256 ; i++)
	{
		sum += i * histogram[i];
	}

	float sumB = 0;
	int BackG = 0;
	int ForeG = 0;

	float varMax = 0;
	int threshold = 0;

	for (int t=0 ; t<256 ; t++)
	{
   		BackG += histogram[t];
   		if (BackG == 0) continue;

   		ForeG = nb_pixels - BackG;
   		if (ForeG == 0) break;

   		sumB += (float) (t * histogram[t]);

   		float mB = sumB / BackG;
   		float mF = (sum - sumB) / ForeG;

   		// Calculate Between Class Variance
   		float var_inter = 
			(float)BackG * (float)ForeG * (mB - mF) * (mB -mF);

   		// Check if new maximum found
  		if (var_inter > varMax)
		{
      			varMax = var_inter;
      			threshold = t;
   		}
	}

	return (size_t)threshold;
}

// Change pixel to black or white depending on the treshold from Otsu
void binarize(SDL_Surface *image_surface)
{
	size_t width = image_surface->w;
   	size_t height = image_surface->h;

	size_t threshold = otsu(image_surface, height, width);

	int black_pixels = 0;
	int white_pixels = 0;

	for (size_t y = 0; y < height; y++)
    {
		for (size_t x = 0; x < width; x++)
       	{
			Uint32 pixel = get_pixel(image_surface, x, y);
           	Uint8 r, g, b;
           	SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
			Uint8 bin_pixel_color = 255;
			if ((size_t) r < threshold)
			{
				bin_pixel_color = 0;
				black_pixels++;
			}
			else
			{
				white_pixels++;
			}
			pixel = SDL_MapRGB(image_surface->format,
           		bin_pixel_color, bin_pixel_color, bin_pixel_color);
			put_pixel(image_surface, x, y, pixel);
       	}
   	}

	if (black_pixels > white_pixels)
		for (size_t y = 0; y < height; y++)
    	{
        	for (size_t x = 0; x < width; x++)
        	{
       		    Uint32 pixel = get_pixel(image_surface, x, y);
            	Uint8 r, g, b;
            	SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            	Uint8 bin_pixel_color = 0;
				if (r == 0)
            	{
					bin_pixel_color = 255;
				}
            	pixel = SDL_MapRGB(image_surface->format,
            		bin_pixel_color, bin_pixel_color, bin_pixel_color);
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
    size_t width = image_surface->w;
    size_t height = image_surface->h;

    // Grayscale
    grayscale(image_surface);
    save_image(image_surface, "tmp/grayscale.bmp"); // for debug
	printf("--- Grayscaling done --- => tmp/grayscale.bmp\n");

    // Binarization (basic for the moment)
    binarize(image_surface);
    save_image(image_surface, "tmp/binarized.bmp"); // for debug
	printf("--- Binarization done --- => tmp/binarized.bmp\n");

    // Binary matrix creation
	size_t *bin_matrix = calloc(width*height, sizeof(size_t));
	image_to_bin_matrix(image_surface, bin_matrix);
	printf("--- Image to Matrix done ---\n");

	return bin_matrix;
}
