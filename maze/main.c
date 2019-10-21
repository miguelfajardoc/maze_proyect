#include "structure.h"
#include <stdlib.h>
#include <math.h>

int main(void)
{
	SDL_Instance instance;
	int player_x = 500;
	int player_y = 300;
	float angle = 90;
	const int maze[MAP_WIDTH][MAP_HEIGHT] =
		{
			{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
			{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
			{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
			{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
			{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
			{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
			{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
			{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
			{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
			{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
			{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
			{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
			{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
			{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
			{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
			{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
			{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
			{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
			{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
			{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
			{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
			{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
			{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
		};
	if (init_instance(&instance) != 0)
		return (1);

	while ("C is awesome")
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		if (poll_events(&x, &y) == 1)
			break;
		draw_stuff(instance, maze, player_x, player_y, angle);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	printf("%i,%i\n", x, y);
	return (0);
}

void draw_stuff(SDL_Instance instance, const int**map, int player_x,
		int player_y, float angle)
{
	int times = 1260;
	int x_intr = 0;
	int y_inter = 0;
	int minim = 0;
	int proyection_x = 0;
	int proyection_y;
	float angle_ch = 60/1260;

	while (times)
	{
		x_intr = x_intersection(player_x, player_y, map, angle - 30 + angle_ch);
		y_inter = y_intersection(player_x, player_y, map, angle - 30 + angle_ch);
		minim = min(x_int, y_inter);
		proyection_calc(&proyection_x, &proyection_y, minim, angle);
		SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawLine(instance.renderer, proyection_x -low ,
				   proyection_y - low, proyection_x + hight,
				   proyection_y + hight);
		--times;
		angle_ch += angle_ch;
	}
}

int * x_intersection(int x, int y, const int **map, float angle)
{
	int A[2];
	int coord = [0, 0];
	int flag = 0

	while(1)
	{
		if (flag == 0)
		{
			if (angle < 180)
				A[1] = floor(y/TEX_WIDTH) * TEX_WIDTH - 1;
			else
				A[1] = floor(y/TEXT_WIDTH) * TEX_WIDTH + 64;
			coord[1] = floor(A[1]/64);
			A[0] = x * (y - A[1])/tan(angle);
			coord[0] = floor(A[0]/64) = 1;
			if (map[coord[0], coord[1]] != 0)
				return (coord);
			flag = 1;
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
				*x -=3 ;
				return(0);
			}
			else if (key.keysym.scancode == 0x52)
			{
				*y +=3 ;
				return(0);
			}
			else if (key.keysym.scancode == 0x51)
			{
				*y -=3 ;
				return(0);
			}
			break;
		}
	}
	return (0);
}
