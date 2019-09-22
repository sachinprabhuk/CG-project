#include <GL/glut.h>
#include <stdio.h>
#include "./headers/constants.h"

char string[20];

void drawText(char *string, float x, float y, float z)
{
	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(180.0, 1, 0, 0);
	glScalef(1.5, 1.5, 1);
	glLineWidth(500);
	for (char *c = string; *c != '\0'; ++c)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);

	glPopMatrix();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

unsigned char *getPixels()
{
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

	drawText(string, 20, 240, 0);

	// rectangle at left bottom corner
	glRectd(0, W_HEIGHT - 100, 100, W_HEIGHT);

	////// getting pixels works before glutSwapBuffer call.. not after. //////////
	unsigned char *pixels = getPixels();

	int row, col, start;

	row = 99;
	col = 99;
	start = (row * W_WIDTH + col) * 3;
	printf("%d %d %d\n", pixels[start], pixels[start + 1], pixels[start + 2]);

	row = 100;
	col = 100;
	start = (row * W_WIDTH + col) * 3;
	printf("%d %d %d\n", pixels[start], pixels[start + 1], pixels[start + 2]);

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
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

	glutMainLoop();
	return 0;
}
