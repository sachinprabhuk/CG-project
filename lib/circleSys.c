#include <stdlib.h>
#include "../headers/circleSys.h"
#include "../headers/circle.h"
#include "../headers/utils.h"
#include "../headers/list.h"

void drawCircleSystem(CircleSystem *sys)
{
	List *circles = sys->circles;
	node *curr = circles->first;
	while (curr)
	{
		circleDraw(curr->circle);
		curr = curr->next;
	}
}

void updateCircleSystem(CircleSystem *sys, Vector2 *mouse)
{
	List *circles = sys->circles;
	node *curr = circles->first;
	while (curr)
	{
		circleUpdate(curr->circle, mouse);
		curr = curr->next;
	}
}

short int addCircle(CircleSystem *sys, Circle *c)
{
	listPush(sys->circles, c);
	return 1;
}

CircleSystem *getCircleSystem()
{
	CircleSystem *resp = malloc(sizeof(CircleSystem));
	resp->circles = getList();
	return resp;
}

void cleanCircleSystem(CircleSystem *c)
{
	listDelete(c->circles);
	free(c);
}