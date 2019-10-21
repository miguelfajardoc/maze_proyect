#ifndef STR
#define STR

#define MAP_WIDTH = 24
#define MAP_HEIGHT = 24
#define TEX_WIDTH = 64
#define TEX_HEIGHT = 64

#include <SDL2/SDL.h>

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *);
void draw_stuff(SDL_Instance instance, int, int);
int poll_events(int *x, int *y);

#endif
