#ifndef CIRCLE
#define CIRCLE

typedef struct circle
{
	float x, y, r;
	short int growing;
} Circle;

Circle *getCircle(float x, float y, float r, short int gr);
void circleGrow(Circle *c);
void circleDraw(Circle *c);

#endif