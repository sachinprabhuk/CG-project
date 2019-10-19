#ifndef CIRCLESYS
#define CIRCLESYS

#include "./circle.h"

typedef struct sys
{
	int maxCircleCount;
	int circleCount;
	Circle **circles;
} CircleSystem;

CircleSystem *getCircleSystem(int maxCircleCount);

void updateCircleSystem(CircleSystem *sys, Vector2 *mouse);

short int fitsInSystem(CircleSystem *sys, Circle *c);

void drawCircleSystem(CircleSystem *sys);

short int addCircle(CircleSystem *sys, Circle *c);

#endif