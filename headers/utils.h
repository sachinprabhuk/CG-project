#ifndef UTILS
#define UTILS

int randomRange(int min, int max);
float distance(float x0, float y0, float x1, float y1);

typedef struct
{
	float r, g, b, a;
} Color;

typedef struct
{
	int x, y;
} Point;

#endif