#include "structure.h"

int main(void)
{
	SDL_Instance instance;
	int player_x = 480;
	int player_y = 357;
	float angle = 90;
	int *ray = malloc(sizeof(int) * 2);
	int * dist_wall;

	const int map[MAP_WIDTH][MAP_HEIGHT] =
		{
			{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
			{4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
			{4,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
			{4,0,2,0,0,5,5,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
			{4,0,3,0,0,5,0,0,0,5,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
			{4,0,4,0,0,5,0,0,0,5,5,5,0,0,5,5,7,7,0,7,7,7,7,7},
			{4,0,5,0,0,5,0,0,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
			{4,0,6,0,0,5,5,5,5,5,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
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
		if (angle >= 360)
			angle -= 360;
		else if (angle < 0)
			angle += 360;

		draw_stuff(instance, map, player_x, player_y, angle, ray, dist_wall);
		if (poll_events(&player_x, &player_y, &angle, ray, dist_wall) == 1)
			break;
		SDL_RenderPresent(instance.renderer);
	}
	free(ray);
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	/*printf("%i,%i\n", player_x, player_y);*/
	return (0);
}

void draw_stuff(SDL_Instance instance, const int map[24][24], int player_x,
		int player_y, float angle, int *ray, int * dist_wall)
{
	int times = TIMES;
	int slice = 0;
	int x_intr[2];
	int y_intr[2];
	int *min = NULL;
	/*int dist_wall = 0;*/
	/*int proyection_x = 0;
	  int proyection_y;*/
	float angle_op = 60;
	float angle_ch = 0;
	int height_wall = 0;

	/*dist_wall = dist_wall;*/

	while (times)
	{
		x_intersection(player_x, player_y, map, angle - (angle_op / 2 )
			       + angle_ch, x_intr);
		/*printf("x_inter points: %d, %d\n", x_intr[0], x_intr[1]);*/
		y_intersection(player_x, player_y, map, angle - (angle_op / 2 )
			       + angle_ch, y_intr);
		/*printf("y_inter points: %d, %d, angle %f\n", y_intr[0], y_intr[1], angle - (angle_op / 2 )+ angle_ch);*/
		
		minimum(player_x, player_y, x_intr, y_intr, &min);
		/*printf("here\n");
		  printf("the minimum coordenate %d, %d\n", *(min), *(min + 1));*/
		*dist_wall = distance_to_wall(player_x, player_y, min, angle, angle - (angle_op / 2 ) + angle_ch);
		/*proyection_calc(&proyection_x, &proyection_y, minim, angle);*/
		if (*dist_wall == 0)
			height_wall = SCREEN_HEIGHT + 1;
		else
			height_wall = (64 * 277)/ *dist_wall;
		SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		/*SDL_RenderDrawLine(instance.renderer, player_x, player_y, min[0]
				   , min[1]);*/
		SDL_RenderDrawLine(instance.renderer, times, (SCREEN_HEIGHT / 2) + (height_wall / 2) , times , (SCREEN_HEIGHT / 2)
		- (height_wall / 2));
		--times;
		angle_ch += angle_op/TIMES;
	}
	*ray = min[0];
	*(ray + 1) = min[1];
}

int poll_events(int *x, int *y, float *angle, int *ray, int * dist_wall)
{
	SDL_Event event;
	SDL_KeyboardEvent key;
	int speed = 3;

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
				move_calculation(*angle, speed, 'r', x, y);
			}
			else if (key.keysym.scancode == 0x50)
			{
				move_calculation(*angle, speed, 'l', x, y);
			}
			else if (key.keysym.scancode == 0x52)
			{
				move_calculation(*angle, speed, 'u', x, y);
			}
			else if (key.keysym.scancode == 0x51)
			{
				move_calculation(*angle, speed, 'd', x, y);
			}
			else if (key.keysym.scancode == 0x004)
			{
				*angle +=1 ;
			}
			else if (key.keysym.scancode == 0x007)
			{
				*angle -=1 ;
			}
			printf("angle:%f\n", *angle);
			printf("ray: %d, %d\n", ray[0], ray[1]);
			printf("position: %d, %d\n", *x, *y);
			printf("dist wall: %d\n", *dist_wall);
			/*printf("distance to wall: %d\n", distance_to_wall(*x, *y, ray, *angle));*/
			/*else if (key.keysym.scancode != SDL_GetScancodeFromKey
			    (key.keysym.sym)) {
				SDL_Log("Physical %s key acting as %s key",
					SDL_GetScancodeName(key.keysym.
							    scancode),
					SDL_GetKeyName(key.keysym.sym));
					}*/

			break;
		}
	}
	return (0);
}

void move_calculation(int angle, int speed, char direction, int * x, int * y)
{
	if (direction == 'r')
		angle -= 90;
	else if (direction == 'l')
		angle += 90;
	else if (direction == 'u')
		angle += 180;
	printf("angle move: %d\n", angle);
	*x += floor(10 * speed * cos(angle * PI / 180)) / 10;
	printf("x change: %f\n", floor(10 * speed * cos(angle * PI / 180)) / 10);
	*y += floor(10 * speed * sin(angle * PI / 180)) / 10;
	printf("y change: %f\n", floor(10 * speed * sin(angle * PI / 180)) / 10);
}

