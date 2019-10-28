#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void x_intersection(int Px, int Py, const int map[24][24], float angle,
		    int coord[2]);
void y_intersection(int Px, int Py, const int map[24][24], float angle,
		    int y_intr[2]);

int main(void)
{
	int x_intr[2];
	int y_intr[2];
	int player_x = 500;
	int player_y = 300;
	float angle = 90;


	int times = 1260;
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
		angle_ch += angle/1260;
	}
	return 0;
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
	int Ax, Ay;
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
			if (angle < 90 || angle > 270)
				Ax = floor(Px/64) * 64 + 64;
			else
			{
				Ax = floor(Px/64) * 64 - 1;
			}
			if (Py - (tan(angle*3.141592653/180) * (Ax - Px)) < 0)
				Ay = 0;
			else
				Ay = Py - (tan(angle*3.141592653/180) * (Ax - Px));
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		else if(flag == 1)
		{
			Ax = Ax + 64;
			temp = tan(angle*3.141592653/180) * 64;
			if (Ay - temp < 0)
				Ay = 0;
			else
				Ay = Ay - temp;
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		else
		{
			Ax += 64;
			if (Ay - temp < 0)
				Ay = 0;
			else
				Ay -= temp;
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		flag++;
		/*printf("coord maze: %d, %d\n", coord[0], coord[1]);
		  printf("points: %d, %d\n", Ax, Ay);*/
	}
	printf("coord maze_y: %d, %d\n", coord[1], coord[0]);
	y_intr[0] = Ax;
	y_intr[1] = Ay;
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
	int Ax, Ay;
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
			Ax = Px + (Py - Ay)/tan(angle*3.141592653/180);
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		else if(flag == 1)
		{
			Ay = Ay - 64;
			temp = 64/tan(angle*3.141592653/180);
			Ax = Ax + temp;
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		else
		{
			Ay -= 64;
			Ax += temp;
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		flag++;
		/*printf("coord maze: %d, %d\n", coord[0], coord[1]);
		  printf("points: %d, %d\n", Ax, Ay);*/
	}
	printf("coord maze_x: %d, %d\n", coord[1], coord[0]);
	x_intr[0] = Ax;
	x_intr[1] = Ay;
}
