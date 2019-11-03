#include <GL/glut.h>

void drawBitmapText(char *string, float x, float y, float z)
{
	char *c;
	glColor3f(0, 0, 0);
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void displayText()
{
	drawBitmapText("WORD DESIGN", 450, 250, 0);
	drawBitmapText("USN", 300, 500, 0);
	drawBitmapText("NAME", 600, 500, 0);
	drawBitmapText("4NM16CS121", 300, 450, 0);
	drawBitmapText("SACHIN PRABHU", 600, 450, 0);
	drawBitmapText("4NM16CS122", 300, 400, 0);
	drawBitmapText("SAHANA KAMATH", 600, 400, 0);
	drawBitmapText("4NM16CS123", 300, 350, 0);
	drawBitmapText("SAHANA M", 600, 350, 0);

	glFlush();
}

void displayMainPage()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	displayText();
}


