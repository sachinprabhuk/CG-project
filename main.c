#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "./headers/circle.h"
#include "./headers/constants.h"
#include "./headers/utils.h"
#include "./headers/circleSys.h"
#include "./headers/vector.h"
#include "./headers/introPage.h"
#include "./headers/callbacks.h"

char string[50], temp[50], newstring[50];
int count = 0;
CircleSystem *cSystem = NULL;
Vector2 mouse = {1000, 1000};
short int firstTime = 1, introPage = 1;
const float scale = 1.6;
Pos *charPositions;

short int isInside(int x, int y, Pos *pos)
{
	if (
			(x >= pos->x && x <= (pos->x + pos->width)) &&
			(y >= pos->y && y <= (pos->y + pos->height)))
		return 1;
	return 0;
}

void updatePositionArray(int x, int y)
{
	// x = x position of string
	// y = y co-ord of string
	if (charPositions)
		free(charPositions);
	int len = strlen(string);
	charPositions = calloc(len, sizeof(Pos));
	charPositions[0].width = glutStrokeWidth(GLUT_STROKE_ROMAN, string[0]) * scale;
	charPositions[0].height = 80 * scale;
	charPositions[0].x = x;
	charPositions[0].y = y;
	for (int i = 1; i < len; ++i)
	{
		charPositions[i].width = glutStrokeWidth(GLUT_STROKE_ROMAN, string[i]) * scale;
		charPositions[i].height = 80 * scale;
		charPositions[i].x = charPositions[i - 1].x + charPositions[i - 1].width;
		charPositions[i].y = charPositions[i - 1].y;
	}
}

void drawString(char *string)
{
	const int strWidth = glutStrokeLength(GLUT_STROKE_ROMAN, string) * scale;
	const int strHeight = 80 * scale;
	const int x = (W_WIDTH - strWidth) >> 1;
	const int y = (W_HEIGHT - strHeight) >> 1;

	updatePositionArray(x, y);

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

void clean()
{
	cleanCircleSystem(cSystem);
}

int main(int argc, char *argv[])
{
	srand(time(0));

	glutInit(&argc, argv);

	// initializing window
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitWindowPosition(160, 80);
	glutCreateWindow("FLUID FONT");

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(displayMainPage);
	glutReshapeFunc(reshape);

	atexit(clean);

	glutMainLoop();

	return 0;
}

// glut callbacks
void mouseClickHandler(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		short int found = 0, i;
		int len = strlen(string);
		for (i = 0; i < len; ++i)
			if (isInside(x, y, &charPositions[i]))
			{
				found = 1;
				break;
			}
		if (found)
		{
			string[0] = string[i];
			string[1] = '\0';
			glutDisplayFunc(initDisplay);
		}
		else
		{
			for(int j=0;j<strlen(temp);j++)
				string[j]=temp[j];
			glutDisplayFunc(initDisplay);
		}
	}
}

void keyboardString(unsigned char key, int x, int y)
{
	if(key == 13)
	{
		for(int i = 0;i < strlen(string);i++)
			temp[i] = string[i];	
		glutDisplayFunc((firstTime ? initDisplay : display));
		firstTime = 0;
		introPage = 0;
		glutPostRedisplay();
		glutKeyboardFunc(keyboard);
		
	}
	else
	{
		string[count] = key;
		count++;
		drawBitmapText(string, 500, 300, 0);	
		glFlush();	
	}
		
}

void displayStringEntry()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	drawBitmapText("ENTER THE STRING", 450, 400, 0);
	glFlush();
	glutKeyboardFunc(keyboardString);
}

void keyboard(unsigned char key, int x, int y)
{	
	if ((key == 's' || key == 'S') && introPage == 1 && firstTime == 0)
	{
		introPage = 0;
		glutDisplayFunc(display);
		glutPostRedisplay();
		
	}
	if ((key == 's' || key == 'S') && introPage == 1)
	{
		introPage = 0;
		glutDisplayFunc(displayStringEntry);
		glutPostRedisplay();
		
	}
	if ((key == 'b' || key == 'B') && introPage == 0)
	{
		introPage = 1;
		glutDisplayFunc(displayMainPage);
		glutPostRedisplay();
	}
}

void initDisplay()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	if (cSystem != NULL)
		free(cSystem);
	cSystem = getCircleSystem();

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
	free(pixels);

	glutDisplayFunc(display);
	glutTimerFunc(0, animator, 0);
	glutMouseFunc(mouseClickHandler);
	glutPassiveMotionFunc(mouseHover);
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
