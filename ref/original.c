#include<GL/glut.h>	
void drawBitmapText(char *string,float x,float y,float z) 
{  
	char *c;
	glRasterPos3f(x, y, z);
	for (c=string; *c != '\0'; c++) 
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}
void reshape(int w,int h) 
{ 
	glViewport(0,0,w,h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(0,w,h,0); 
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 
}
void displaytext(void)
{ 
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	glColor3f(1,1,1);
	drawBitmapText("USN",400,100,0);
	drawBitmapText("NAME",600,100,0);
	drawBitmapText("4NM16CS121",400,150,0);
	drawBitmapText("SACHIN PRABHU",600,150,0);
	drawBitmapText("4NM16CS122",400,200,0);
	drawBitmapText("SAHANA KAMATH",600,200,0);
	drawBitmapText("4NM16CS123",400,250,0);
	drawBitmapText("SAHANA M",600,250,0);
	drawBitmapText("CG PROJECT TITLE - WORD DESIGN",400,400,0);
	glutSwapBuffers(); 
} 
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); 
	glutInitWindowSize(1366,768); 
	glutInitWindowPosition(100,100); 
	glutCreateWindow("CG PROJECT"); 
	glutDisplayFunc(displaytext);
	glutIdleFunc(displaytext);
    glutReshapeFunc(reshape); 
	glutMainLoop(); 
	return 0;
}
