#include "../headers/vector.h"
#include <math.h>
#include <stdlib.h>
Vector2 *getVector(float x, float y)
{
	Vector2 *resp = malloc(sizeof(Vector2));
	resp->x = x;
	resp->y = y;
	return resp;
}

Vector2 *vecGetSub(Vector2 *vec1, Vector2 *vec2)
{
	Vector2 *resp = getVector(0, 0);
	resp->x = vec1->x - vec2->x;
	resp->y = vec1->y - vec2->y;
	return resp;
}

float vecGetMag(Vector2 *vec)
{
	float x = vec->x, y = vec->y;
	return sqrt(x * x + y * y);
}

void vecMult(Vector2 *vec, float val)
{
	vec->x *= val;
	vec->y *= val;
}

Vector2 *vecGetAdd(Vector2 *vec1, Vector2 *vec2)
{
	return getVector(vec1->x + vec2->x, vec1->y + vec2->y);
}
