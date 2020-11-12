#include <GL/glut.h>
#include <cmath>

struct vec2
{
	union {
		struct { float x, y; };
		float data[2];
	};
};

vec2 house[] = {
	0, 0,
	100, 0,
	100, 75,
	50, 100,
	0, 75
};
float angle = 45;
float c = 100;
float m = 3;

void drawHouse()
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 5; ++i)
		glVertex2fv(house[i].data);
	glEnd();
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	// default house
	glColor3f(1, 1, 1);
	glLoadIdentity();
	drawHouse();

	// rotation by angle
	glColor3d(1, 0, 0);
	glLoadIdentity();
	glRotatef(angle, 0, 0, 1);
	drawHouse();

	// draw mirror line
	glColor3f(1, 0, 1);
	glLoadIdentity();
	glBegin(GL_LINES);
	glVertex2f(200, 200 * m + c);
	glVertex2f(-200, (-200) * m + c);
	glEnd();

	// reflection of house
	glColor3f(0, 0, 1);
	glLoadIdentity();
	glTranslatef(0, c, 0);
	float a = atan(m);
	a = 180 * a / 3.1415;
	glRotatef(a, 0, 0, 1);
	glScalef(1, -1, 1);
	glRotatef(-a, 0, 0, 1);
	glTranslatef(0, -c, 0);
	drawHouse();

	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("House Rotation");
	glutDisplayFunc(displayHandler);

	glMatrixMode(GL_PROJECTION);
	glOrtho(-250, 250, -250, 250, -250, 250);
	glClearColor(0.1, 0.1, 0.1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutMainLoop();
}