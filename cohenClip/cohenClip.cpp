#include <iostream>
#include <GL/glut.h>

enum {
	TOP		= (1 << 3),
	BOTTOM	= (1 << 2),
	LEFT	= (1 << 1),
	RIGHT	= (1 << 0)
};

float xmin = 10, xmax = 100;
float ymin = 10, ymax = 100;

float xvmin = 200, xvmax = 400;
float yvmin = 200, yvmax = 400;

float line[2][2] = {
	20, 50, 120, 90,	// partially inside (in out)
};

float lines[4][2][2] = {
	20, 50, 120, 90,	// partially inside (in out)
	100, 250, 120, 120,	// complletely otside
	20, 20, 120, 120,	// completely inside
	50, 120, 150, 50,	// partially inside (out, in, out)
};

void drawLine(float x0, float y0, float x1, float y1)
{
	glBegin(GL_LINES);
	glVertex2f(x0, y0);
	glVertex2f(x1, y1);
	glEnd();
}

void drawViewport(float xmin, float ymin, float xmax, float ymax)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();
}

int getCode(float x, float y)
{
	int code = 0;
	if (y > ymax)
		code |= TOP;
	else if (y < ymin)
		code |= BOTTOM;

	if (x > xmax)
		code |= RIGHT;
	else if (x < xmin)
		code |= LEFT;

	return code;
}

void cohenSutherland(float x0, float y0, float x1, float y1)
{
	bool accept = false, done = false;
	
	int code0 = getCode(x0, y0);
	int code1 = getCode(x1, y1);

	while (!done)
	{
		if (code0 == 0 && code1 == 0)
		{
			// both inside
			done = true;
			accept = true;
			break;
		}
		
		if (code0 & code1)
		{
			// share common side, completely outside
			done = true;
			accept = false;
			break;
		}

		int code = code0 ? code0 : code1;
		float x = 0, y = 0;
		if (code & TOP)
		{
			y = ymax;
			x = x0 + (y - y0) * (x0 - x1) / (y0 - y1);
		}
		else if (code & BOTTOM)
		{
			y = ymin;
			x = x0 + (y - y0) * (x0 - x1) / (y0 - y1);
		}

		if (code & RIGHT)
		{
			x = xmax;
			y = y0 + (x - x0) * (y0 - y1) / (x0 - x1);
		}
		else if (code & LEFT)
		{
			x = xmin;
			y = y0 + (x - x0) * (y0 - y1) / (x0 - x1);
		}

		if (code == code0)
		{
			x0 = x;
			y0 = y;
			code0 = getCode(x0, y0);
		}
		else
		{
			x1 = x;
			y1 = y;
			code1 = getCode(x1, y1);
		}
	}

	if (accept)
	{
		// draw it on v stuff

		float xv0 = xvmin + (x0 - xmin) * (xvmax - xvmin) / (xmax - xmin);
		float yv0 = yvmin + (y0 - ymin) * (yvmax - yvmin) / (ymax - ymin);

		float xv1 = xvmin + (x1 - xmin) * (xvmax - xvmin) / (xmax - xmin);
		float yv1 = yvmin + (y1 - ymin) * (yvmax - yvmin) / (ymax - ymin);

		std::cout << "here";
		glColor3f(0, 1, 1);
		// drawLine(x0, y0, x1, y1);
		drawLine(xv0, yv0, xv1, yv1);
	}
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	drawViewport(xmin, ymin, xmax, ymax);

	glColor3f(0, 1, 0);
	drawViewport(xvmin, yvmin, xvmax, yvmax);

	glColor3f(0, 0, 1);
	

	for (int i = 0; i < 4; ++i)
	{
		drawLine(lines[i][0][0], lines[i][0][1], lines[i][1][0], lines[i][1][1]);
	}

	for (int i = 0; i < 4; ++i)
	{
		cohenSutherland(lines[i][0][0], lines[i][0][1], lines[i][1][0], lines[i][1][1]);
	}

	//drawLine(line[0][0], line[0][1], line[1][0], line[1][1]);
	//cohenSutherland(line[0][0], line[0][1], line[1][0], line[1][1]);

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("cohen sutherland");

	glutDisplayFunc(displayHandler);
	glClearColor(0.1, 0.1, 0.1, 1);

	gluOrtho2D(0, 500, 0, 500);
	glutMainLoop();

	return 0;
}