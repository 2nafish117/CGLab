
# if 0
#include <iostream>
#include <cstdio>
#include <GL/glut.h>

void spinCube(float speed);

float cube[8][3] = {
	{ 0.5,  0.5,  0.5},
	{ 0.5,  0.5, -0.5},
	{ 0.5, -0.5,  0.5},
	{ 0.5, -0.5, -0.5},
	{-0.5,  0.5,  0.5},
	{-0.5,  0.5, -0.5},
	{-0.5, -0.5,  0.5},
	{-0.5, -0.5, -0.5}
};

float colors[8][3] = {
	{1, 1, 1},
	{1, 1, 0},
	{1, 0, 1},
	{1, 0, 0},
	{0, 1, 1},
	{0, 1, 0},
	{0, 0, 1},
	{0, 0, 0}
};

float theta[3] = { 0, 0, 0 };
int axis = 2;

void drawFace(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex3fv(cube[a]);
		glColor3fv(colors[b]);
		glVertex3fv(cube[b]);
		glColor3fv(colors[c]);
		glVertex3fv(cube[c]);
		glColor3fv(colors[d]);
		glVertex3fv(cube[d]);
	glEnd();
}

void drawCube()
{
	drawFace(0, 1, 2, 3);
	drawFace(0, 4, 5, 1);
	drawFace(0, 2, 6, 4);
	drawFace(7, 5, 1, 3);
	drawFace(6, 2, 3, 7);
	drawFace(6, 7, 5, 4);
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	spinCube(0.7);
	drawCube();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void mouseHandler(int button, int state, int xpos, int ypos)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
}

void spinCube(float speed)
{
	theta[axis] += speed;
	if (theta[axis] >= 360.0)
		theta[axis] -= 360.0;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	// glutInitWindowPosition(100, 100);
	glutCreateWindow("cube");

	//glOrtho(500, -500, 500, -500, 500, -500);
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(displayHandler);
	glutMouseFunc(mouseHandler);
	glutMainLoop();
	return 0;
}
#endif

#include <GL/glut.h>
#include <iostream>

float cube[8][3] = {
	-250.0f, -250.0f , -250.0f,
	+250.0f, -250.0f , -250.0f,
	+250.0f, +250.0f , -250.0f,
	-250.0f, +250.0f , -250.0f,

	-250.0f, -250.0f , +250.0f,
	+250.0f, -250.0f , +250.0f,
	+250.0f, +250.0f , +250.0f,
	-250.0f, +250.0f , +250.0f,
};

float color[8][3] = {
	0.0f, 0.0f , 0.0f,
	1.0f, 0.0f , 0.0f,
	1.0f, 1.0f , 0.0f,
	0.0f, 1.0f , 0.0f,

	0.0f, 0.0f , 1.0f,
	1.0f, 0.0f , 1.0f,
	1.0f, 1.0f , 1.0f,
	0.0f, 1.0f , 1.0f,
};

float angle[3] = { 0.0, 0.0, 0.0 };
float speed = 0.5;

int axis = 0;

void drawFace(int a, int b, int c, int d);
void drawCube()
{

	drawFace(0, 1, 2, 3);
	drawFace(4, 5, 6, 7);
	//drawFace();
	//drawFace();
	//drawFace();
	//drawFace();
}

void drawFace(int a, int b, int c, int d)
{
	glBegin(GL_QUADS);

	glColor3fv(color[a]);
	glVertex3fv(cube[a]);

	glColor3fv(color[b]);
	glVertex3fv(cube[b]);

	glColor3fv(color[c]);
	glVertex3fv(cube[c]);

	glColor3fv(color[d]);
	glVertex3fv(cube[d]);

	glEnd();
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	angle[axis] += speed;
	glLoadIdentity();
	glRotatef(angle[0], 1, 0, 0);
	glRotatef(angle[1], 0, 1, 0);
	glRotatef(angle[2], 0, 0, 1);

	drawCube();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void mouseHandler(int b, int s, int xpos, int ypos)
{
	if (b == GLUT_LEFT && s == GLUT_DOWN)
		axis = (axis + 1) % 3;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("cube");

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500, 500, -500, 500, -500, 500);
	glClearColor(0.1, 0.1, 0.1, 1);
	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(displayHandler);
	glutMouseFunc(mouseHandler);
	glutMainLoop();


	return 0;
}