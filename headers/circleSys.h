#ifndef CIRCLESYS
#define CIRCLESYS

#include "./circle.h"
#include "./list.h"

typedef struct sys
{
	List *circles;
} CircleSystem;

CircleSystem *getCircleSystem();

void updateCircleSystem(CircleSystem *, Vector2 *);

void drawCircleSystem(CircleSystem *);

short int addCircle(CircleSystem *, Circle *);

void cleanCircleSystem(CircleSystem *);

#endif