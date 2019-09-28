#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "./headers/circle.h"
#include "./headers/constants.h"
#include "./headers/utils.h"

char string[20];
const int MAX_CIRCLES = 1200;
const int initRadius = 50;
Circle *circles[1200];
int circleCount = 0;

void drawText(char *string, float x, float y, float z)
{
	glPushMatrix();
	glLineWidth(50);
	glColor3f(1, 0, 0);
	glTranslatef(x, y, z);
	glScalef(1.5, 1.5, 1);
	for (char *c = string; *c != '\0'; ++c)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	glPopMatrix();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

unsigned char *getPixels()
{
	// use this for reading pixels ->
	// start = (row * W_WIDTH + col) * 3;
	const int pixelCount = W_WIDTH * W_HEIGHT;

	// since each pixel has R, G and B component
	unsigned char *pixels = calloc(pixelCount * 3, sizeof(char));
	glReadPixels(0, 0, W_WIDTH, W_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	return pixels;
}

void display(void)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0, 0, 1);

	if (circleCount < MAX_CIRCLES)
	{
		circles[circleCount] = getCircle(
				randomRange(initRadius, W_WIDTH - initRadius),
				randomRange(initRadius, W_HEIGHT - initRadius),
				initRadius, 1);
		++circleCount;
	}
	for (int i = 0; i < circleCount; ++i)
	{
		circleGrow(circles[i]);
		circleDraw(circles[i]);
	}

	drawText(string, 0, 100, 0);

	glutSwapBuffers();
}

void animator(int a)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, animator, 0);
}

int main(int argc, char *argv[])
{
	srand(time(0));

	// input
	printf("Enter string : ");
	scanf("%s", string);

	glutInit(&argc, argv);

	// initializing window
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CG PROJECT");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, animator, 0);

	glutMainLoop();
	return 0;
}
