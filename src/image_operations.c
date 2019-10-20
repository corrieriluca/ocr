#include <err.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "image_operations.h"

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

static inline Uint8 *pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8 *)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;
    }

    return 0;
}

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void update_surface(SDL_Surface *screen, SDL_Surface *image)
{
    if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);
}

// Save an image in the BMP format at the specified path
void save_image(SDL_Surface *image, char *path)
{
    if ((SDL_SaveBMP(image, path)) != 0)
        exit(EXIT_FAILURE);
}

// Draws an horizontal red line on the surface, at the specified line (y)
// Designed to be used for segmentation debugging (showing lines)
void draw_horizontal_line(SDL_Surface *image, size_t line)
{
    size_t width = image->w;
    for (size_t x = 0; x < width; x++)
    {
        Uint8 r = 255, g = 0, b = 0;
        Uint32 pixel = SDL_MapRGB(image->format, r, g, b);
        put_pixel(image, x, line, pixel);
    }
}

// Draw an vertical blue line on the surface, at the specified column (x)
// Designed to be used for segmentation debugging (showing characters)
void draw_vertical_line(SDL_Surface *image, size_t column,
    size_t start, size_t end)
{
    for (size_t y = start; y < end; y++)
    {
        Uint8 r = 0, g = 0, b = 255;
        Uint32 pixel = SDL_MapRGB(image->format, r, g, b);
        put_pixel(image, column, y, pixel);
    }
}
