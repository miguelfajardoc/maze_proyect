#ifndef STR
#define STR

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
