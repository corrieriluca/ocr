#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface *load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface *display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE | SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
             img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if (SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while (event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while (event.type != SDL_KEYUP);
}

/*size_t otsu(SDL_Surface *img)
{
	int width = img->w;                                               
    int height = img->h;

	float hist[256] = {0};


	for (int x = 0; x < height; x++)                                            
    {                                                                           
        for (int y = 0; y < width; y++)                                         
        {                                                                       
            Uint32 pixel = get_pixel(img, x, y);                      
            Uint8 r, g, b;                                                      
            SDL_GetRGB(pixel, img->format, &r, &g, &b);               
            hist[r] += 1;                              
        }                                                                       
    }

	int nb_pixels = width*height;

	for (int i=0; i<256; ++i)
		hist[i] /= nb_pixels;

	float ut = 0;

    for (int i = 0; i < 256; i++)
        ut += i*hist[i];



    int max_k = 0;

    float max_sigma_k = 0;

    for (int k = 0; k < 256; k++)
    {

        float wk = 0;

        for (int i = 0; i <= k; i++)
            wk += hist[i];

        float uk = 0;

        for (int i = 0; i <= k; i++)
            uk += i*hist[i];



        float sigma_k = 0;

        if (wk != 0 && wk != 1)
            sigma_k = ((ut*wk - uk)*(ut*wk - uk)) / (wk*(1 - wk));

        if (sigma_k > max_sigma_k)
        {

            max_k = k;

            max_sigma_k = sigma_k;

        }

    }

    return (size_t)max_k;
}

void binarize(SDL_Surface *image_surface, size_t threshold)
{
    size_t width = image_surface->w;
    size_t height = image_surface->h;

    for(size_t x=0; x < width; x++)
    {
        for(size_t y=0; y < height; y++)
        {
            Uint32 pixel;
            pixel = get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel,image_surface->format, &r, &g, &b);
            size_t graylevel = r;

            if (graylevel < threshold)
            	{ r = 0; g = 0; b = 0; }
            else
				{ r = 255; g = 255; b=255; }

            pixel = SDL_MapRGB(image_surface->format, r, g, b);
            put_pixel(image_surface, x, y, pixel);
        }
    }
}*/

void image_to_bin_matrix(SDL_Surface *img_surface, size_t *bin_matrix)
{
	size_t width = img_surface->w;
	size_t height = img_surface->h;

	for (size_t x = 0; x < height; x++)                                            
	{                                                                           
        	for (size_t y = 0; y < width; y++)                                         
        	{
			Uint32 pixel = get_pixel(img_surface, x, y);
			Uint8 r, g, b;
			SDL_GetRGB(pixel,img_surface->format, &r, &g, &b);
			bin_matrix[x*width+y] = (r==0)?1:0;
		}
	}
}


size_t *image_to_matrix()
{
    SDL_Surface *image_surface;
    SDL_Surface *screen_surface;

    init_sdl();

    image_surface = load_image("my_image.bmp");
    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    size_t width = image_surface->w;
    size_t height = image_surface->h;

    for (size_t x = 0; x < height; x++)
    {
        for (size_t y = 0; y < width; y++)
        {
            Uint32 pixel = get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            Uint8 average = 0.3*r + 0.59*g + 0.11*b;
            if (average>127)
				average = 255;
			else
				average = 0;
	pixel = SDL_MapRGB(image_surface->format,average,average,average);
            put_pixel(image_surface, x, y, pixel);
        }
    }

    update_surface(screen_surface, image_surface);

    wait_for_keypressed();

	//binarize(image_surface,otsu(image_surface));

	//wait_for_keypressed();

	size_t *bin_matrix = calloc(width*height, sizeof(size_t));

	image_to_bin_matrix(image_surface, bin_matrix);	

	SDL_FreeSurface(image_surface);
	SDL_FreeSurface(screen_surface);

	return bin_matrix;
}
