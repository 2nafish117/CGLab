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
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	// glutInitWindowPosition(100, 100);
	glutCreateWindow("cube");

	glOrtho(500, -500, 500, -500, 500, -500);
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(displayHandler);
	glutMouseFunc(mouseHandler);
	glutMainLoop();
	return 0;
}