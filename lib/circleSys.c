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
	{
		circleUpdate(circles[i], mouse);
	}
	// int count = sys->circleCount;
	// float centerDist;
	// Circle **circles = sys->circles;
	// for (int i = 0; i < count; ++i)
	// 	for (int j = i + 1; j < count; ++j)
	// 		if (circles[i] != circles[j])
	// 		{
	// 			centerDist = distance(circles[i]->x, circles[i]->y, circles[j]->x, circles[j]->y);
	// 			if (centerDist <= (circles[i]->r + circles[j]->r))
	// 				circles[i]->growing = 0, circles[j]->growing = 0;
	// 		}
}

short int fitsInSystem(CircleSystem *sys, Circle *c)
{
	// checking for limit
	if (sys->circleCount == sys->maxCircleCount)
		return 0;

	// checking if the new circle is inside existing circle.
	int count = sys->circleCount;
	for (int i = 0; i < count; ++i)
	{
		Circle *curr = sys->circles[i];
		if (distance(curr->pos.x, curr->pos.y, c->pos.x, c->pos.y) < (c->r + curr->r))
			return 0;
	}

	return 1;
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