#include "structure.h"

/**
 * distance_to_wall - calculate the distance between 2 points, (Px, Py)
 * and (coord[0], coord[1])
 * @Px: player position in the x axis
 * @Py: player position in te y axis
 * @coord: coordenate of the ray
 * @angle: the angle of the ray
 * Return: an integer that is the distance from the player to the wall
 */
int distance_to_wall(int Px, int Py, const int * coord, float angle, float angle_ray)
{
	int distance = 0;
	float brute_distance = 0;

	if (angle_ray == 90 || angle_ray == 270)
	{
		distance = abs(Py - coord[1]);
		return distance;
	}
	if (angle_ray == 0 || angle_ray == 180)
	{
		distance = abs(Px - coord[1]);
		return distance;
	}
	brute_distance  = abs(Px - coord[0]) / cos(angle_ray * PI / 180);
	distance = fishbowl_corrector(brute_distance, angle, angle_ray);
	return distance;
}

/**
 * fishbowl_correcter - correct the lenght of a distance of the fish bowl efect
 * @brute_distance: the brute distance to the wall
 * @angle: the angle of the point
 * Return: an integer fixing the distance
 */
int fishbowl_corrector(float brute_distance, float angle, float angle_ray)
{
	int distance = 0;
	float complement_angle = 0;

	if (angle_ray == 0 || angle_ray == 180)
	{
		complement_angle = complement_angle;
		return (int)brute_distance;
	}
	complement_angle = abs(angle - angle_ray);
	distance = brute_distance * cos(complement_angle * PI / 180);

	return distance;
}
