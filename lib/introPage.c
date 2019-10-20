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
