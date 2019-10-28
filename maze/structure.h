#ifndef STR
#define STR

#define MAP_WIDTH = 24
#define MAP_HEIGHT = 24
#define WH = 64
#define HT = 64
#define PI = 3.14189265
#include <SDL2/SDL.h>

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *);
void draw_stuff(SDL_Instance instance, int, int);
int poll_events(int *x, int *y);
void x_intersection(int Px, int Py, const int map[24][24],
		    float angle, int x_intr[2]);

#endif
