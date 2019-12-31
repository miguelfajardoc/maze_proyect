#ifndef STR
#define STR

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define WH 64
#define HT 64
#define PI 3.14189265
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define TIMES 800
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/* functions in init_instance.c*/
int init_instance(SDL_Instance *);

/*functions in main.c*/
void draw_stuff(SDL_Instance instance, const int map[24][24], int player_x,
		 int player_y, float angle, int *ray);
int poll_events(int *x, int *y, float *angle, int *ray);

/*functions in raycasting.c*/
void x_intersection(int Px, int Py, const int map[24][24], float angle,
		    int coord[2]);
void y_intersection(int Px, int Py, const int map[24][24], float angle,
		    int y_intr[2]);
void minimum(int Px, int Py, int x_intr[2], int y_intr[2], int **min);

/*functions in helper_functions.c*/
int distance_to_wall(int Px, int Py, const int * min, float angle, float angle_ray);
int fishbowl_corrector(float brute_distance, float angle, float angle_ray);

#endif
