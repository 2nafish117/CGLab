#include <GL/glut.h>

int x1, y1;
int x2, y2;
int clicks = 0;

void drawLine();

void mouseHandler(int button, int state, int xpos, int ypos)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (clicks == 0)
		{
			x1 = xpos - 250;
			y1 = 250 - ypos;
		}
		if (clicks == 1)
		{
			x2 = xpos - 250;
			y2 = 250 - ypos;
			drawLine();
		}
		clicks = (clicks + 1) % 2;
	}
	
	glFlush();
}

void displayHandler()
{
	
}

void drawPoint(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void drawLine()
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int incx = 1, incy = 1;
	if (dx < 0)
	{
		incx = -1;
		dx = 0 - dx;
	}
	if (dy < 0)
	{
		incy = -1;
		dy = -dy;
	}

	int x = x1;
	int y = y1;
	if (dx > dy)
	{
		int e = 2 * dy - dx;
		int inc1 = 2 * (dy - dx);
		int inc2 = 2 * dy;
		for (int i = 0; i <= dx; ++i)
		{
			drawPoint(x, y);
			if (e > 0)
			{
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
		}
	}
	else
	{
		int e = 2 * dx - dy;
		int inc1 = 2 * (dx - dy);
		int inc2 = 2 * dx;
		for (int i = 0; i <= dy; ++i)
		{
			drawPoint(x, y);
			if (e > 0)
			{
				e += inc1;
				x += incx;
			}
			else
				e += inc2;
			y += incy;
		}
	}
}

int main(int ac, char* av[])
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("bres line");
	glutMouseFunc(mouseHandler);
	glutDisplayFunc(displayHandler);

	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-250, 250, -250, 250);

	glutMainLoop();
}
