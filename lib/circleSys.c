#include <stdlib.h>
#include "../headers/circleSys.h"
#include "../headers/circle.h"

void drawCircleSystem(CircleSystem *sys)
{
	Circle **circles = sys->circles;
	const int count = sys->circleCount;
	for (int i = 0; i < count; ++i)
	{
		circleDraw(circles[i]);
		circleGrow(circles[i]);
	}
}

unsigned short int addCircle(CircleSystem *sys, Circle *c)
{
	if (sys->circleCount == sys->maxCircleCount)
		return 0;

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