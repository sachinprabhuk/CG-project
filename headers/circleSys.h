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

void drawCircleSystem(CircleSystem *sys);

unsigned short int addCircle(CircleSystem *sys, Circle *c);

#endif