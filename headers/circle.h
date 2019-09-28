#ifndef CIRCLE
#define CIRCLE

#include "./utils.h"

typedef struct circle
{
	float x, y, r;
	short int fill;
	short int growing;
	Color color;
} Circle;

Circle *getCircle(float x, float y, float r, short int gr, short int fill);
void circleGrow(Circle *c);
void circleDraw(Circle *c);

#endif