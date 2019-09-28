#include "../headers/constants.h"
#include "../headers/circle.h"
#include <GL/glut.h>
#include <math.h>

Circle *getCircle(float x, float y, float r, short int gr, short int fill)
{
	Circle *circle = malloc(sizeof(Circle));
	circle->x = x;
	circle->y = y;
	circle->r = r;
	circle->growing = gr;
	circle->fill = fill;
	(circle->color).r = randomRange(0, 255) / (float)255;
	(circle->color).g = randomRange(0, 255) / (float)255;
	(circle->color).b = randomRange(0, 255) / (float)255;

	return circle;
}

void circleGrow(Circle *c)
{
	if (c->growing == 1)
	{
		c->r += CIRCLE_GROWTH_SPEED;
		int x = c->x, y = c->y, r = c->r;
		if ((x + r) >= W_WIDTH || (x - r) <= 0 || (y + r) >= W_HEIGHT || (y - r) <= 0)
			c->growing = 0;
	}
}

void circleDraw(Circle *c)
{
	glLineWidth(1);
	glColor3f(c->color.r, c->color.g, c->color.b);
	if (c->fill)
		glBegin(GL_POLYGON);
	else
		glBegin(GL_LINE_LOOP);
	for (float angle = 0; angle <= TWO_PI; angle += 0.1)
		glVertex2f(c->x + c->r * cos(angle), c->y + c->r * sin(angle));
	glEnd();
}
