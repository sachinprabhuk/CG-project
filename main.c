#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include "./headers/circle.h"
#include "./headers/constants.h"
#include "./headers/utils.h"
#include "./headers/circleSys.h"
#include "./headers/vector.h"
#include "./headers/introPage.h"

char string[50];
CircleSystem *cSystem;
Vector2 mouse = {1000, 1000};
short int firstTime = 1, introPage = 1;
const float scale = 1.6;

void drawString(char *string)
{
	const int strWidth = glutStrokeLength(GLUT_STROKE_ROMAN, string) * scale;
	const int strHeight = 80 * scale;
	const int x = (W_WIDTH - strWidth) >> 1;
	const int y = (W_HEIGHT - strHeight) >> 1;
	glPushMatrix();
	glLineWidth(50);
	glColor3f(0, 0, 0);
	glTranslatef(x, y, 0);
	glScalef(scale, scale, 1);
	for (char *c = string; *c != '\0'; ++c)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	glPopMatrix();
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

	updateCircleSystem(cSystem, &mouse);
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
	mouse.x = x;
	mouse.y = W_HEIGHT - y;
}

void initDisplay()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	drawString(string);

	unsigned char *pixels = getPixels();
	const int pixelsArrSize = W_WIDTH * W_HEIGHT * 3;

	for (int i = 0; i < pixelsArrSize; i += 9)
	{
		if (
				(int)pixels[i] == 0 &&
				(int)pixels[i + 1] == 0 &&
				(int)pixels[i + 2] == 0 &&
				(rand() % 11) > 9)
		{
			const int currPixel = i / 3;
			int x = currPixel % W_WIDTH;
			int y = currPixel / W_WIDTH;
			const int radius = randomRange(MIN_CIRCLE_RAD, MAX_CIRCLE_RAD);
			Circle *newCircle = getCircle(x, y, radius, 1, 1);
			addCircle(cSystem, newCircle);
		}
	}

	glutDisplayFunc(display);
	glutTimerFunc(0, animator, 0);
	glutPassiveMotionFunc(mouseHover);
}

void clean()
{
	cleanCircleSystem(cSystem);
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

void keyboard(unsigned char key, int x, int y)
{
	if ((key == 's' || key == 'S') && introPage == 1)
	{
		glutDisplayFunc((firstTime ? initDisplay : display));
		firstTime = 0;
		introPage = 0;
		glutPostRedisplay();
	}
	if ((key == 'b' || key == 'B') && introPage == 0)
	{
		introPage = 1;
		glutDisplayFunc(displayMainPage);
		glutPostRedisplay();
	}
}

int main(int argc, char *argv[])
{
	srand(time(0));

	// input
	printf("Enter string : ");
	scanf("%s", string);

	cSystem = getCircleSystem();
	glutInit(&argc, argv);

	// initializing window
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitWindowPosition(160, 80);
	glutCreateWindow("CG PROJECT");

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(displayMainPage);
	glutReshapeFunc(reshape);

	atexit(clean);

	glutMainLoop();

	return 0;
}
