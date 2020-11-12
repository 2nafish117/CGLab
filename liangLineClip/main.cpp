
# if 0
#include<GL/glut.h>
#include<algorithm>
#include<iostream>

using namespace std;

double xmin = 20, xmax = 100, ymin = 20, ymax = 100;
double xvmin = 200, xvmax = 450, yvmin = 250, yvmax = 450;

int n = 4;
double lines[20][4] = {
	{ 20, 50 , 120, 90 },	// partially inside (in out)
	{ 90, 250, 150, 120},	// completely outside
	{ 30, 30 , 90, 90},	    // completely inside
	{ 50, 120, 150, 50 },	// partially inside (out, in, out)
};

void drawLine(double x1, double y1, double x2, double y2)
{
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void drawClipWindow(int left, int bottom, int right, int top)
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(left, bottom);
	glVertex2i(right, bottom);
	glVertex2i(right, top);
	glVertex2i(left, top);
	glEnd();
}

int clipTest(int *p, int *q, double* u0, double* u1)
{
	double u[4] = { 0.0 };

	for (int i = 0; i < 4; i++)
	{
		if (p[i] == 0) //completely oustide or parallel to clipper
			return 0;
		else
		{
			u[i] = (double)q[i] / (double)p[i];

			if (p[i] < 0) // line entering out to in
				*u0 = max(*u0, u[i]);
			else if (p[i] > 0) // line exiting in to out
				*u1 = min(*u1, u[i]);
		}
	}
	return 1;
}

void liangBarsky(double x1, double y1, double x2, double y2)
{
	//xwmin <= x1 + u*(x2-x1) <= xwmax
	//ywmin <= y1 + u*(y2-y1) <= ywmax 
	//expressthe above 4 inequalities as u*pk <= qk to get corresponding pk , qk values

	int p[4], q[4];
	double u0 = 0, u1 = 1;
	double dx = x2 - x1, dy = y2 - y1;
	p[0] = -dx; p[1] = dx; p[2] = -dy; p[3] = dy;
	q[0] = x1 - xmin; q[1] = xmax - x1; q[2] = y1 - ymin; q[3] = ymax - y1;

	if (clipTest(p, q, &u0, &u1))
	{
		if (u0 > u1)
			return;

		else
		{
			double x11 = x1, y11 = y1;
			//parametric form
			x1 = x11 + u0 * dx;
			y1 = y11 + u0 * dy;
			x2 = x11 + u1 * dx;
			y2 = y11 + u1 * dy;
		}
	}

	double sx, sy;
	sx = (double)(xvmax - xvmin) / (double)(xmax - xmin);
	sy = (double)(yvmax - yvmin) / (double)(ymax - ymin);
	double vx0 = xvmin + (x1 - xmin) * sx;
	double vy0 = yvmin + (y1 - ymin) * sy;
	double vx1 = xvmin + (x2 - xmin) * sx;
	double vy1 = yvmin + (y2 - ymin) * sy;

	drawLine(vx0, vy0, vx1, vy1);
}

void display()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.f, 0.f, 1.f);
	drawClipWindow(xmin, ymin, xmax, ymax);
	for (int i = 0; i < n; i++)
		drawLine(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);

	glColor3f(0.f, 1.f, 0.f);
	drawClipWindow(xvmin, yvmin, xvmax, yvmax);
	for (int i = 0; i < n; i++)
		liangBarsky(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);

	glFlush();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(500, 500);

	glutCreateWindow("liang barsky");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
# endif

# if 1
#include <GL/glut.h>
#include <iostream>
#include <algorithm>

int xmin = 20, xmax = 100, ymin = 20, ymax = 100;
int xvmin = 200, xvmax = 280, yvmin = 200, yvmax = 280;

int lines[10][4] = {
	10, 10, 150, 50,
	20, 20, 100, 100
};
int numLines = 1;

void drawViewport(int xmin, int ymin, int xmax, int ymax)
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(xmin, ymin);
	glVertex2i(xmax, ymin);
	glVertex2i(xmax, ymax);
	glVertex2i(xmin, ymax);
	glEnd();
}

void drawLine(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}

int clipTest(int* p, int* q, float* u0, float* u1)
{
	float u[4] = {0};
	for (int i = 0; i < 4; ++i)
	{
		if (p[i] == 0)
			return 0;
		u[i] = (float)q[i] / p[i];
		if (p[i] < 0)
			*u0 = std::max(*u0, u[i]);
		else if (p[i] > 0)
			*u1 = std::min(*u1, u[i]);
	}
	return 1;
}

void liangLineClip(int x1, int y1, int x2, int y2)
{
	// clip it
	// xmin <=	x = x1 + u * (x2 - x1)	<= xmax
	// ymin <=	y = y1 + u * (y2 - y1)	<= ymax
	// p * u <= q

	float u0 = 0, u1 = 1;
	int dx = x2 - x1;
	int dy = y2 - y1;

	int p[4] = { -dx, dx, -dy, dy};
	int q[4] = {  x1 - xmin, xmax - x1, y1 - ymin, ymax - y1};

	if (clipTest(p, q, &u0, &u1))
	{
		if (u0 > u1)
			return;
		int x11 = x1;
		int y11 = y1;
		x1 = x11 + u0 * dx;
		y1 = y11 + u0 * dy;
		x2 = x11 + u1 * dx;
		y2 = y11 + u1 * dy;
	}

	// draw to new vieport

	int xv1 = xvmin + (x1 - xmin) * (xvmax - xvmin) / (xmax - xmin);
	int yv1 = yvmin + (y1 - ymin) * (yvmax - yvmin) / (ymax - ymin);
	int xv2 = xvmin + (x2 - xmin) * (xvmax - xvmin) / (xmax - xmin);
	int yv2 = yvmin + (y2 - ymin) * (yvmax - yvmin) / (ymax - ymin);
	drawLine(xv1, yv1, xv2, yv2);
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);

	for (int i = 0; i < numLines; ++i)
		drawLine(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);

	for(int i = 0;i < numLines;++i)
		liangLineClip(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
	
	glColor3f(0, 1, 0);
	drawViewport(xmin, ymin, xmax, ymax);
	glColor3f(1, 0, 0);
	drawViewport(xvmin, yvmin, xvmax, yvmax);
	glFlush();
}

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow("liang barsky clipping");

	glutDisplayFunc(displayHandler);
	
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(0.1, 0.1, 0.1, 0.1);
	
	glutMainLoop();
	
	return 0;
}
#endif