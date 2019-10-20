#ifndef CIRCLE
#define CIRCLE

#include "./utils.h"
#include "./vector.h"

typedef struct circle
{
	Vector2 pos;
	Vector2 origin;
	float r;
	short int fill;
	short int growing;
	float growthSpeed;
	Color color;
} Circle;

Circle *getCircle(float x, float y, float r, short int gr, short int fill);
void circleGrow(Circle *c);
void circleDraw(Circle *c);
void circleUpdate(Circle *c, Vector2 *mouse);

#endif