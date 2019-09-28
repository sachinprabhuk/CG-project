#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include "./headers/circle.h"
#include "./headers/constants.h"
#include "./headers/utils.h"
#include "./headers/circleSys.h"

char string[20];
const int initRadius = 100;
CircleSystem *cSystem;

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

	drawText(string, 200, 300, 0);

	const int radius = randomRange(2, 40);
	Circle *temp = getCircle(
			randomRange(radius, W_WIDTH - radius),
			randomRange(radius, W_HEIGHT - radius),
			radius,
			1, 0);
	unsigned short int status = addCircle(cSystem, temp);
	if (status == 0)
		free(temp);

	updateCircleSystem(cSystem);
	drawCircleSystem(cSystem);

	glutSwapBuffers();
}

void animator(int a)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, animator, 0);
}

void mouseHover(int x, int y)
{
	y = W_HEIGHT - y;
	int count = cSystem->circleCount;
	Circle **circles = cSystem->circles;

	// clear fill
	for (int i = 0; i < count; ++i)
		circles[i]->fill = 0;

	// paint the required one.
	for (int i = 0; i < count; ++i)
		if (distance(circles[i]->x, circles[i]->y, x, y) < circles[i]->r)
		{
			circles[i]->fill = 1;
			break;
		}
}

int main(int argc, char *argv[])
{
	srand(time(0));

	// input
	printf("Enter string : ");
	scanf("%s", string);

	cSystem = getCircleSystem(500);
	glutInit(&argc, argv);

	// initializing window
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CG PROJECT");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, animator, 0);
	glutPassiveMotionFunc(mouseHover);

	glutMainLoop();
	return 0;
}
