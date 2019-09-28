// #include <GL/glut.h>
// #include <stdio.h>
// #include <math.h>
// #include <time.h>

// static int n = 0;

// #define PI 3.14

// struct Circle
// {
// 	int x, y, r;
// 	bool growing = true;
// };

// struct Circle circle[100];

// void delay(int number_of_seconds)
// {
// 	int milli_seconds = 1000 * number_of_seconds;
// 	clock_t start_time = clock();
// 	while (clock() < start_time + milli_seconds)
// 		;
// }

// void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius)
// {
// 	glClearColor(0, 0, 0, 0);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glColor3f(1, 0, 0);
// 	int i;
// 	int lineAmount = 100;
// 	GLfloat twicePi = 2.0f * PI;
// 	glLineWidth(3);
// 	glBegin(GL_LINE_LOOP);
// 	for (i = 0; i <= lineAmount; i++)
// 	{
// 		glVertex2f(
// 				x + (radius * cos(i * twicePi / lineAmount)),
// 				y + (radius * sin(i * twicePi / lineAmount)));
// 	}
// 	glEnd();
// 	delay(10);
// }

// bool edges(struct Circle *circle)
// {
// 	return (circle->x + circle->r >= 1000 || circle->x - circle->r <= 0 || circle->y + circle->r >= 500 || circle->y - circle->r <= 0);
// }

// void grow(struct Circle *circle)
// {
// 	if (circle->growing)
// 		circle->r += 1;
// }

// void show(struct Circle *circle)
// {
// 	drawHollowCircle(circle->x, circle->y, circle->r);
// 	glFlush();
// }

// void draw()
// {
// 	srand(time(0));
// 	circle[n].x = rand() % 1000;
// 	circle[n].y = rand() % 500;
// 	circle[n].r = 1;
// 	while (true)
// 	{
// 		if (edges(&circle[n]))
// 		{
// 			circle[n].growing = false;
// 			glFlush();
// 			break;
// 		}
// 		show(&circle[n]);
// 		grow(&circle[n]);
// 	}
// }

// void display()
// {
// 	glClearColor(0, 0, 0, 0);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	while (n <= 100)
// 	{
// 		draw();
// 		n++;
// 	}
// }

// void init()
// {
// 	glClearColor(0, 0, 0, 0);
// 	glColor3f(1, 1, 1);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	gluOrtho2D(0, 1000, 0, 500);
// }

// void resize(int w, int h)
// {
// 	glViewport(0, 0, w, h);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	gluOrtho2D(0, 1000, 0, 500);
// }

// int main(int argc, char *argv[])
// {
// 	glutInit(&argc, argv);
// 	glutInitWindowSize(1366, 768);
// 	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
// 	glutCreateWindow("CG-Project");
// 	glutDisplayFunc(display);
// 	glutReshapeFunc(resize);
// 	init();
// 	glutMainLoop();
// }
