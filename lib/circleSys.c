#include <stdlib.h>
#include "../headers/circleSys.h"
#include "../headers/circle.h"
#include "../headers/utils.h"

void drawCircleSystem(CircleSystem *sys)
{
	Circle **circles = sys->circles;
	const int count = sys->circleCount;
	for (int i = 0; i < count; ++i)
		circleDraw(circles[i]);
}

void updateCircleSystem(CircleSystem *sys, Vector2 *mouse)
{
	Circle **circles = sys->circles;
	const int count = sys->circleCount;
	for (int i = 0; i < count; ++i)
		circleUpdate(circles[i], mouse);
}

short int addCircle(CircleSystem *sys, Circle *c)
{
	sys->circles[sys->circleCount] = c;
	++sys->circleCount;
	return 1;
}

CircleSystem *getCircleSystem(int maxCircleCount)
{
	CircleSystem *resp = malloc(sizeof(CircleSystem));
	resp->maxCircleCount = maxCircleCount;
	resp->circleCount = 0;
	resp->circles = calloc(maxCircleCount, sizeof(Circle));
	return resp;
}