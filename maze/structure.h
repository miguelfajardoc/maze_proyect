#ifndef STR
#define STR

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define WH 64
#define HT 64
#define PI 3.14189265
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define TIMES 20

#include <SDL2/SDL.h>

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *);
void draw_stuff(SDL_Instance instance, const int map[24][24], int player_x,
		 int player_y, float angle, int *ray);
int poll_events(int *x, int *y, float *angle, int *ray);
void x_intersection(int Px, int Py, const int map[24][24], float angle,
		    int coord[2]);
void y_intersection(int Px, int Py, const int map[24][24], float angle,
		    int y_intr[2]);
void minimum(int Px, int Py, int x_intr[2], int y_intr[2], int **min);

#endif
