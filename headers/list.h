#ifndef LIST
#define LIST

#include "./circle.h"

typedef struct Node
{
	struct Node *next;
	Circle *circle;
} node;

typedef struct
{
	node *first;
	node *last;
	int size;
} List;

List *getList();
void listPush(List *list, Circle *el);
void listDelete(List *list);

#endif
