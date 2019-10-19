#include "../headers/constants.h"
#include "../headers/circle.h"
#include "../headers/vector.h"
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

Circle *getCircle(float x, float y, float r, short int gr, short int fill)
{
	Circle *circle = malloc(sizeof(Circle));
	circle->pos.x = x;
	circle->pos.y = y;
	circle->origin.x = x;
	circle->origin.y = y;
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
	if (c->r > 8)
		c->growing = -1;
	else if (c->r < 4)
		c->growing = 1;

	c->r += (CIRCLE_GROWTH_SPEED * c->growing);
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
		glVertex2f(c->pos.x + c->r * cos(angle), c->pos.y + c->r * sin(angle));
	glEnd();
}

Vector2 *getMouseForce(Circle *circle, Vector2 *mouse)
{
	Vector2 *mouseForce = vecGetSub(&circle->pos, mouse);
	const float mouseForceMag = vecGetMag(mouseForce);
	if (mouseForceMag < MOUSE_DIST_THRESHOLD)
		vecMult(mouseForce, REPELL_DRAG);
	else
		mouseForce->x = mouseForce->y = 0;
	return mouseForce;
}

Vector2 *getPullBackForce(Circle *circle)
{
	Vector2 *vec = vecGetSub(&circle->origin, &circle->pos);
	vecMult(vec, PULL_BACK_DRAG);
	return vec;
}

void circleUpdate(Circle *circle, Vector2 *mouse)
{
	circleGrow(circle);

	Vector2 *mouseForce = getMouseForce(&circle->pos, mouse);
	Vector2 *pullBack = getPullBackForce(circle);
	Vector2 *resultant = vecGetAdd(mouseForce, pullBack);

	circle->pos.x += resultant->x;
	circle->pos.y += resultant->y;

	free(resultant);
	free(mouseForce);
	free(pullBack);
}