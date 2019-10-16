#include <SDL2/SDL.h>
#include <stdio.h>

/** draw funcion
*
*/
void draw_stuff(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(renderer, 10, 10, 100, 100);
}
int main(void)
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	/*initialice SDL*/
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	/* Create a new window */
	window = SDL_CreateWindow("SDL2 \\o/", SDL_WINDOWPOS_CENTERED,
				  SDL_WINDOWPOS_CENTERED, 1260, 720, 0);
	if (window == NULL)
	{
		fprintf(stderr, "SQLCreateWindow Error: %sn", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/* Create a new Renderer instance linked to the window */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
				      | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		fprintf(stderr, "SQLCreateRenderer Error: %sn", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	while ("C is awesome")
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		draw_stuff(renderer);
		SDL_RenderPresent(renderer);
	}
	return (0);
}
