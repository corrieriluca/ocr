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
	float hist_proba[256] = { 0.0F }; //array of prob of each grey pixel
	float P = 1 / (h * w);

	// double for loop to fill the hist_proba
	for (size_t y = 0; y < h; y++)                   
        {                                                                           
		for (size_t x = 0; x < w; x++)                                      
		{
			Uint32 pixel = get_pixel(image_surface, x, y);                      
            		Uint8 r, g, b;                                                      
            		SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
			size_t graylevel = r;
            		hist_proba[graylevel] += P;
        	}                                                                       
	}

	float max_var = 0;
	int threshold = 0;

	for (int i = 0; i < 256; ++i)
	{
		float c1 = 0;
		//float c2 = 0;

		for (int j = 0; j<i; ++j)
			c1 += hist_proba[j];

		//c2 = 1 - c1;
		
		float m1 = 0;
		//float m2 = 0;

		for(int n = 0; n<i; ++n)
			m1 += (n*hist_proba[n]); // /c1;

		/*for(int n = i; n<256; ++n)
			m2 += (n*hist_proba[n])/c2;*/

		float var1 = 0;
		//float var2 = 0;

		/*for(int n = 0; n<i; ++n)
			var1 += (n-m1)*(n-m1)*hist_proba[n];*/

		/*for(int n = i; n<256; ++n)
			var2 += (n-m2)*(n-m2)*hist_proba[n];*/

		float sum_c = 0;

		var1 = ((sum_c*c1 - m1)*(sum_c*c1 - m1))/(c1-c1*c1)

		for (i=0; i<256; ++i)
			sum_c += i*hist_proba[i];

		if (max_var < var1)
		{
			min_var = var1 + var2;
			threshold = i;
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

	for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            Uint32 pixel = get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
			Uint8 bin_pixel_color = (size_t)r > threshold ? 255 : 0;
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
    /* init_sdl(); // not necessary

    image_surface = load_image("my_image.bmp");
    screen_surface = display_image(image_surface);

    wait_for_keypressed(); */

    size_t width = image_surface->w;
    size_t height = image_surface->h;

    // Grayscale
    grayscale(image_surface);
    save_image(image_surface, "tmp/grayscale.bmp"); // for debug

    // Binarization (basic for the moment)
    binarize(image_surface);
    save_image(image_surface, "tmp/binarized.bmp"); // for debug

    // Binary matrix creation
	size_t *bin_matrix = calloc(width*height, sizeof(size_t));
	image_to_bin_matrix(image_surface, bin_matrix);	

	//SDL_FreeSurface(image_surface);

	return bin_matrix;
}
