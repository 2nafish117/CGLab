#include <GL/glut.h>
#include <iostream>
#include <algorithm>
#include <Windows.h>

int x[100] = { 100, 150, 100, 200, 200 };
int y[100] = { 100, 150, 200, 200, 100 };
int n = 5;

int m = 0;
int edges[10] = { 0 };

void detectEdges(int x0, int y0, int x1, int y1, int scan)
{
	if (x1 < x0)
		std::swap(x1, x0);
	if (y1 < y0)
		std::swap(y1, y0);

	if (scan < y1 && scan > y0)
		edges[m++] = x0 + (scan - y0) * (x0 - x1) / (y0 - y1);
}

void drawLine(int x0, int y0, int x1, int y1)
{
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();
}

void scanFill()
{
	glColor3f(0, 1, 0);
	for (int s = 0; s < 500; ++s)
	{
		m = 0;
		for (int i = 0; i < n; ++i)
		{
			detectEdges(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n], s);
		}
		//std::sort(edges, edges + m);
		for (int i = 0; i < m; i += 2)
		{
			Sleep(10);
			drawLine(edges[i], s, edges[i + 1], s);
			glFlush();
		}

	}
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; ++i)
		glVertex2i(x[i], y[i]);
	glEnd();

	scanFill();
	//glBegin(GL_LINES);
	//glVertex2i(100, 100);
	//glVertex2i(100, 200);
	//glEnd();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

	glutCreateWindow("scan line");

	glClearColor(0.1, 0.1, 0.1, 1);
	gluOrtho2D(0, 500, 0, 500);

	glutDisplayFunc(displayHandler);
	glutMainLoop();
	return 0;
}