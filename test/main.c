#include "structure.h"
#include <stdlib.h>


int main(void)
{
	SDL_Instance instance;
	int x = 500;
	int y = 300;

	if (init_instance(&instance) != 0)
		return (1);

	while ("C is awesome")
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		if (poll_events(&x, &y) == 1)
			break;
		draw_stuff(instance, x, y);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	printf("%i,%i\n", x, y);
	return (0);
}

void draw_stuff(SDL_Instance instance, int x, int y)
{
	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(instance.renderer, 500, 500, x, y);
}

int poll_events(int *x, int *y)
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			key = event.key;
			/* if escape is pressed */
			if (key.keysym.scancode == 0x29)
				return (1);
			else if (key.keysym.scancode == 0x4F)
			{
				*x += 3;
				return (0);
			}
			else if (key.keysym.scancode == 0x50)
			{
				*y -=3 ;
				return(0);
			}
			break;
		}
	}
	return (0);
}
