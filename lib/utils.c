#include "../headers/utils.h"
#include <stdlib.h>
#include <math.h>

int randomRange(int min, int max)
{
	return ((rand() % (max - min + 1)) + min);
}

float distance(float x0, float y0, float x1, float y1)
{
	return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}
