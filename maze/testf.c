#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define TIMES 1080

void x_intersection(int Px, int Py, const int map[24][24], float angle,
		    int coord[2]);
void y_intersection(int Px, int Py, const int map[24][24], float angle,
		    int y_intr[2]);
void minimum(int Px, int Py, int x_intr[2], int y_intr[2], int **min);

int main(void)
{
	int x_intr[2];
	int y_intr[2];
	int *min = NULL;
	int player_x = 500;
	int player_y = 300;
	float angle = 60;
	float angle_op = 60;

	int times = TIMES;
	float angle_ch = 0;
	const int map[24][24] =
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

	while (times)
	{
		x_intersection(player_x, player_y, map, angle - 30 + angle_ch,
			       x_intr);
		printf("x_inter points: %d, %d\n", x_intr[0], x_intr[1]);
		y_intersection(player_x, player_y, map, angle - 30 + angle_ch,
			       y_intr);
		printf("y_inter points: %d, %d, angle %f\n", y_intr[0], y_intr[1], angle - 30 + angle_ch);
		times--;
		angle_ch += angle_op/TIMES;
		minimum(player_x, player_y, x_intr, y_intr, &min);
		printf("here\n");
		printf("the minimum coordenate %d, %d\n", *(min), *(min + 1));
	}
	return 0;
}
/**
 * minimum - Find the minimum distance between two coordenates to the player and
 * saves the direction of the variable that the minimum coordenate
 * @Px: the current player position in x
 * @Py: the current player position in y
 * @x_intr: the coordenate with the x axis
 * @y_intr: the coordenate with the y axis
 * @min: the variable that holds the direction of the minimum coordenate
 */
void minimum(int Px, int Py, int x_intr[2], int y_intr[2], int ** min_coord)
{
	float hipx = 0;
	float hipy = 0;
	float min = 0;

	min_coord = min_coord;

	min = 0;
	hipx = sqrt(pow(x_intr[0] - Px, 2) + pow(x_intr[1] - Py, 2));
	printf("hipx: %f\n", hipx);
	hipy = sqrt(pow(y_intr[0] - Px, 2) + pow(y_intr[1] - Py, 2));
	printf("hipy: %f\n", hipy);
	min = MIN(hipx, hipy);
	printf("the min is: %f\n", min);
	if (min == hipx)
		*min_coord = x_intr;
	else
		*min_coord = y_intr;

}
/**
 * y_intersection - Find the coordenates that the ray intersect with the
 *                  vertical (y) maze when a wall is present
 * @Px: the current player position in x
 * @Py: the current player position in y
 * @map: the map world of the player
 * @angle: the angle of the ray
 * @y_intr: the pointer to external variable that saves the coordenates found
 */
void y_intersection(int Px, int Py, const int map[24][24], float angle,
		    int y_intr[2])
{
	float Ax, Ay;
	int flag = 0;
	int coord[2];
	float temp = 0;

	coord[0] = floor(Px/64);
	coord[1] = floor(Py/64);
	if (angle == 90 || angle == 180)
		angle += 0.001;

	while(map[coord[1]][coord[0]] == 0)
	{
		if (flag == 0)
		{
                        /* - 1 is required, ex: border in 0 is 64, so
                        64 / 64 = 1, but the cell to verf is 0.*/
			if (angle < 90 || angle > 270)
				Ax = floor(Px/64) * 64 + 64;
			else
			{
				Ax = floor(Px/64) * 64 - 1;
			}
			temp = Py + (tan(angle*3.141592653/180) * (Px - Ax));
			if ( temp < 0 )
				Ay = 0;
			else if ( temp > (24 * 64))
				Ay = 24 * 64;
			else
				Ay = Py + (tan(angle*3.141592653/180) * (Px - Ax));
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		else if(flag == 1)
		{
			if (angle < 90 || angle > 270)
				Ax = Ax + 64;
			else
				Ax = Ax - 64;
			temp = Ay - tan(angle*3.141592653/180) * 64;
			if (temp < 0)
				Ay = 0;
			else if (temp > ( 24 * 64))
				Ay = 64 * 24;
			else
				Ay = temp;
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		else
		{
			if (angle < 90 || angle > 270)
				Ax += 64;
			else
				Ax -= 64;
			temp = Ay - tan(angle*3.141592653/180) * 64;
			if (temp < 0)
				Ay = 0;
			else if (temp > ( 24 * 64))
				Ay = 64 * 24;
			else
				Ay = temp;
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		flag++;
		/*printf("coord maze: %d, %d\n", coord[0], coord[1]);
		  printf("points: %d, %d\n", Ax, Ay);*/
	}
	printf("coord maze_y: %d, %d\n", coord[1], coord[0]);
	y_intr[0] = (int)Ax;
	y_intr[1] = (int)Ay;
}

/**
 * x_intersection - Find the coordenates that the ray intersect with the
 *                  horizontal (x) maze when a wall is present
 * @Px: the current player position in x
 * @Py: the current player position in y
 * @map: the map world of the player
 * @angle: the angle of the ray
 * @x_intr: the pointer to external variable that saves the coordenates found
 */
void x_intersection(int Px, int Py, const int map[24][24], float angle, int x_intr[2])
{
	float Ax, Ay;
	int flag = 0;
	int coord[2];
	float temp = 0;

	coord[0] = floor(Px/64);
	coord[1] = floor(Py/64);

	while(map[coord[1]][coord[0]] == 0)
	{
		if (flag == 0)
		{
                        /* - 1 is required, ex: border in 0 is 64, so
                        64 / 64 = 1, but the cell to verf is 0.*/
			if (angle < 180)
				Ay = floor(Py/64) * 64 - 1;
			else
			{
				Ay = floor(Py/64) * 64 + 64;
			}
			/*if (angle > 270)
			  angle *= -1;*/
			temp = Px + (Py - Ay)/tan(angle*3.141592653/180);
			if ( temp < 0)
				Ax = 0;
			else if (temp > (24 * 64))
				Ax = 24 * 64;
			else
				Ax = temp;
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		else if(flag == 1)
		{
			Ay = Ay - 64;
			/*if (angle > 270)
			  angle *= -1;*/
			temp = Ax + 64/tan(angle*3.141592653/180);
			if ( temp < 0)
				Ax = 0;
			else if (temp > (24 * 64))
				Ax = 24 * 64;
			else
				Ax = temp;
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		else
		{
			Ay -= 64;
			temp = Ax + 64/tan(angle*3.141592653/180);
			if ( temp < 0)
				Ax = 0;
			else if (temp > (24 * 64))
				Ax = 24 * 64;
			else
				Ax = temp;
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		flag++;
		/*printf("coord maze: %d, %d\n", coord[0], coord[1]);
		  printf("points: %d, %d\n", Ax, Ay);*/
	}
	printf("coord maze_x: %d, %d\n", coord[1], coord[0]);
	x_intr[0] = (int)Ax;
	x_intr[1] = (int)Ay;
}
