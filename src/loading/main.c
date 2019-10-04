#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "loading.h"

int main()
{
	SDL_Surface* image_surface;
	SDL_Surface* screen_surface;

	init_sdl();

	image_surface = load_image("image_to_load.bmp");

        screen_surface = display_image(image_surface);



                        // TODO: Wait for a key to be pressed.



                       // TODO: Free the image surface.

                        // TODO: Free the screen surface.
 
	return 0;
}
