#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include "./headers/circle.h"
#include "./headers/constants.h"
#include "./headers/utils.h"
#include "./headers/circleSys.h"
#include "./headers/vector.h"

char string[50];
CircleSystem *cSystem;
Vector2 mouse = {1000, 1000};
short int firstTime = 1, introPage = 1;
const float scale = 1.6;

Vector2 *getPosition(char *string)
{
	int strWidth = glutStrokeLength(GLUT_STROKE_ROMAN, string) * scale;
	int strHeight = 80 * scale;
	Vector2 *pos = getVector(0, 0);
	pos->x = (W_WIDTH - strWidth) >> 1;
	pos->y = (W_HEIGHT - strHeight) >> 1;
	return pos;
}

void drawBitmapText(char *string, float x, float y, float z)
{
	char *c;
	glColor3f(0, 0, 0);
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void drawText(char *string, float x, float y, float z)
{
	glPushMatrix();
	glLineWidth(50);
	glColor3f(0, 0, 0);
	glTranslatef(x, y, z);
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

	Vector2 *pos = getPosition(string);
	drawText(string, pos->x, pos->y, 0);
	free(pos);

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
	W_WIDTH = w;
	W_HEIGHT = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void displayText()
{
	drawBitmapText("WORD DESIGN", 200, 50, 0);
	drawBitmapText("USN", 100, 300, 0);
	drawBitmapText("NAME", 300, 300, 0);
	drawBitmapText("4NM16CS121", 100, 250, 0);
	drawBitmapText("SACHIN PRABHU", 300, 250, 0);
	drawBitmapText("4NM16CS122", 100, 200, 0);
	drawBitmapText("SAHANA KAMATH", 300, 200, 0);
	drawBitmapText("4NM16CS123", 100, 150, 0);
	drawBitmapText("SAHANA M", 300, 150, 0);

	glFlush();
}

void displayMainPage()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	displayText();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 's' && introPage == 1)
	{
		glutDisplayFunc((firstTime ? initDisplay : display));
		firstTime = 0;
		introPage = 0;
		glutPostRedisplay();
	}
	if (key == 'b' && introPage == 0)
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
