#include "structure.h"

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
	/*printf("hipx: %f\n", hipx);*/
	hipy = sqrt(pow(y_intr[0] - Px, 2) + pow(y_intr[1] - Py, 2));
	/*printf("hipy: %f\n", hipy);*/
	min = MIN(hipx, hipy);
	/*printf("the min is: %f\n", min);*/
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
	int sign = 0;

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
			{
				Ax = floor(Px/64) * 64 + 64;
			}
			else
			{
				Ax = floor(Px/64) * 64 - 1;
			}
			if ( angle < 180 )
				sign = -1;
			else
				sign = 1;
			temp = Py + sign * abs((tan(angle*3.141592653/180) * (Ax - Px)));
			if ( temp < 0 )
				Ay = 0;
			else if ( temp > (24 * 64))
				Ay = 24 * 64;
			else
				Ay = temp;
			coord[0] = floor(Ax/64);
			coord[1] = floor(Ay/64);
		}
		else if(flag == 1)
		{
			if (angle < 90 || angle > 270)
				Ax = Ax + 64;
			else
				Ax = Ax - 64;
			temp = Ay + sign * abs(tan(angle*3.141592653/180) * 64);
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
			temp = Ay + sign * abs(tan(angle*3.141592653/180) * 64);
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
	/*printf("coord maze_y: %d, %d\n", coord[1], coord[0]);*/
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
	int sign = 0;

	coord[0] = floor(Px/64);
	coord[1] = floor(Py/64);

	while(map[coord[1]][coord[0]] == 0)
	{
		if (flag == 0)
		{
                        /* - 1 is required, ex: border in 0 is 64, so
                        64 / 64 = 1, but the cell to verf is 0.*/
			if (angle < 180)
			{
				Ay = floor(Py/64) * 64 - 1;
			}
			else
			{
				Ay = floor(Py/64) * 64 + 64;
			}
			if (angle > 270 || angle < 90)
				sign = 1;
			else
				sign = -1;

			temp = Px + sign * abs((Py - Ay)/tan(angle*3.141592653/180));
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
			if (angle > 180)
				Ay = Ay + 64;
			else
				Ay = Ay - 64;
			temp = Ax + sign * abs(64/tan(angle*3.141592653/180));
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
			if (angle > 180)
				Ay = Ay + 64;
			else
				Ay = Ay - 64;
			temp = Ax + sign * abs(64/tan(angle*3.141592653/180));
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
	/*printf("coord maze_x: %d, %d\n", coord[1], coord[0]);*/
	x_intr[0] = (int)Ax;
	x_intr[1] = (int)Ay;
}
