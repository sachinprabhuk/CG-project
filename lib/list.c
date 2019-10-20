#include <stdlib.h>
#include "../headers/list.h"

List *getList()
{
	List *resp = malloc(sizeof(List));
	resp->first = resp->last = NULL;
	resp->size = 0;
	return resp;
}

void listPush(List *list, Circle *circle)
{
	node *el = malloc(sizeof(node));
	el->circle = circle;
	el->next = NULL;

	list->size++;
	if (list->first)
	{
		list->last->next = el;
		list->last = el;
	}
	else
		list->first = list->last = el;
}

void listDelete(List *list)
{
	node *curr = list->first, *temp;
	while (curr)
	{
		temp = curr->next;
		free(curr->circle);
		free(curr);
		curr = temp;
	}
}