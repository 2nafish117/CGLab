#include <GL/glut.h>

#define CIRCLE 0
#define ELLIPSE 1

int option = CIRCLE;
int xc, yc, rc = 100;
int xce, yce, rx = 200, ry = 100;

void drawMirroredCircle(int xc, int yc, int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(xc + x, yc + y);
	glVertex2i(yc + y, xc + x);

	glVertex2i(xc - x, yc - y);
	glVertex2i(yc - y, xc - x);

	glVertex2i(xc + x, yc - y);
	glVertex2i(yc + y, xc - x);

	glVertex2i(xc - x, yc + y);
	glVertex2i(yc - y, xc + x);
	glEnd();
}

void drawCircle()
{
	int x = 0;
	int y = rc;
	int d = 3 - 2 * rc;
	while (x <= y)
	{
		drawMirroredCircle(xc, yc, x, y);
		if (d < 0)
		{
			d += 4 * x + 6;
		}
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

#include <cmath>

void drawCirclePolar()
{
	for (float theta = 0; theta <= 2 * 3.1415926; theta += 0.01)
	{
		glBegin(GL_POINTS);
		glVertex2f(rc * cos(theta) + xc, rc * sin(theta) + yc);
		glEnd();
	}
}

void drawMirroredEllipse(int xce, int yce, int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x + xce, y + yce);
	glVertex2i(-x + xce, y + yce);
	glVertex2i(x + xce, -y + yce);
	glVertex2i(-x + xce, -y + yce);
	glEnd();
}

void drawEllipse()
{
	float dx, dy, d1, d2, x, y;
	x = 0;
	y = ry;

	// Initial decision parameter of region 1 
	d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;

	// For region 1 
	while (dx < dy)
	{

		// Print points based on 4-way symmetry 
		drawMirroredEllipse(xce, yce, x, y);

		// Checking and updating value of 
		// decision parameter based on algorithm 
		if (d1 < 0)
		{
			x++;
			dx = dx + (2 * ry * ry);
			d1 = d1 + dx + (ry * ry);
		}
		else
		{
			x++;
			y--;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d1 = d1 + dx - dy + (ry * ry);
		}
	}

	// Decision parameter of region 2 
	d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
		((rx * rx) * ((y - 1) * (y - 1))) -
		(rx * rx * ry * ry);

	// Plotting points of region 2 
	while (y >= 0)
	{

		// Print points based on 4-way symmetry 
		drawMirroredEllipse(xce, yce, x, y);

		// Checking and updating parameter 
		// value based on algorithm 
		if (d2 > 0)
		{
			y--;
			dy = dy - (2 * rx * rx);
			d2 = d2 + (rx * rx) - dy;
		}
		else
		{
			y--;
			x++;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d2 = d2 + dx - dy + (rx * rx);
		}
	}
}

void drawEllipsePolar()
{
	for (float theta = 0; theta <= 2 * 3.1415926; theta += 0.001)
	{
		glBegin(GL_POINTS);
		glVertex2f(rx * cos(theta) + xce, ry * sin(theta) + yce);
		glEnd();
	}
}

void mouseHandler(int button, int state, int xpos, int ypos)
{

}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawEllipsePolar();
	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("circle bres");

	glClearColor(0.2, 0.2, 0.2, 1);
	gluOrtho2D(-250, 250,-250, 250);

	glutMouseFunc(mouseHandler);
	glutDisplayFunc(displayHandler);
	glutMainLoop();

	return 0;
}