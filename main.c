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
unsigned char *pixels;

typedef struct
{
	int x, y;
} Point;
Point points[100000];
int pointsCount = 0;

void drawText(char *string, float x, float y, float z)
{
	// glPushMatrix();
	glLineWidth(50);
	glColor3f(0, 0, 0);
	// glTranslatef(x, y, z);
	// glScalef(1.2, 1.2, 1);
	for (char *c = string; *c != '\0'; ++c)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	// glPopMatrix();
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
	glColor3f(0, 0, 1);

	const int radius = randomRange(1, 2);
	const Point currPoint = points[randomRange(0, pointsCount)];
	Circle *temp = getCircle(currPoint.x, currPoint.y, radius, 1, 0);
	unsigned short int status = addCircle(cSystem, temp);
	if (status == 0)
		free(temp);

	updateCircleSystem(cSystem);
	drawCircleSystem(cSystem);

	glFlush();
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

void initDisplay()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	drawText(string, 100, 190, 0);

	unsigned char *pixels = getPixels();
	const int pixelCount = W_WIDTH * W_HEIGHT;
	for (int i = 0; i < pixelCount; i += 3)
	{
		if ((int)pixels[i] == 0 && (int)pixels[i + 1] == 0 && (int)pixels[i + 2] == 0)
		{
			const int currPixel = i / 3;
			const int x = currPixel % W_WIDTH;
			const int y = currPixel / W_WIDTH;
			points[pointsCount].x = x;
			points[pointsCount].y = y;
			++pointsCount;
		}
	}
	printf("required pixel count: %d\n", pointsCount);

	// glFlush();
	glutDisplayFunc(display);
	glutTimerFunc(0, animator, 0);
	glutPassiveMotionFunc(mouseHover);
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitWindowPosition(200, 80);
	glutCreateWindow("CG PROJECT");

	glutDisplayFunc(initDisplay);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}
