#ifndef CIRCLE
#define CIRCLE

struct Circle
{
	float x, y, r;
};

void circleGrow(struct Circle *c);
void circleDraw(struct Circle *c);

#endif