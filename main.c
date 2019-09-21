#include <GL/glut.h>
#include <stdio.h>

char string[10];

void drawBitmapText(char *string, float x, float y, float z)
{
	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(180.0, 1, 0, 0);
	glScalef(1.8, 1.8, 1);
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

void displaytext(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0, 1, 1);

	drawBitmapText(string, 400, 450, 0);

	glutSwapBuffers();
}
int main(int argc, char *argv[])
{
	// input
	printf("Enter string : ");
	scanf("%s", string);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CG PROJECT");
	glutDisplayFunc(displaytext);
	// glutIdleFunc(displaytext);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
