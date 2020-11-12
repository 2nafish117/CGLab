# if 0
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
# endif

# if 1

#include<GL/glut.h>
#include<iostream>
#include<algorithm>

//#include<windows.h> // along with Sleep()

using namespace std;

int poly[20][20] = {
	//triangle
	// {100, 100},
	// {200, 200},
	// {300, 100}

	// right arrow poly
	{50 , 100 },
	{50 , 150},
	{200, 150},
	{200, 200},
	{250, 125},
	{200, 50 },
	{200, 100}

};
float xIntresections[20];
int n = 7, num_intersections;
int w, h;
void drawPoly()
{
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
		glVertex2f(poly[i][0], poly[i][1]);
	glEnd();
}

void findXIntersection(float x1, float y1, float x2, float y2, int sy)
{
	if (sy > y1 && sy < y2 || sy > y2 && sy < y1)
		xIntresections[num_intersections++] = x1 + (x2 - x1) / (y2 - y1) * (sy - y1); // solving line equation
}

void scanFill()
{
	for (int sy = h; sy > 0; sy--)
	{
		num_intersections = 0;
		for (int i = 0; i < n; i++)
			findXIntersection(poly[i][0], poly[i][1], poly[(i + 1) % n][0], poly[(i + 1) % n][1], sy);

		sort(xIntresections, xIntresections + num_intersections);

		if (num_intersections >= 2)
			for (int i = 0; i < num_intersections; i += 2)
			{
				glColor3f(1, 0, 0);
				glBegin(GL_LINES);
				glVertex2f(xIntresections[i], sy);
				glVertex2f(xIntresections[i + 1], sy);
				glEnd();
				Sleep(1);
				glFlush();
			}
	}

	glFlush();
}

void displayHandler()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 0);
	drawPoly();

	scanFill();

	glFlush();
}
int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);

	glutCreateWindow("ScanLine");
	glutDisplayFunc(displayHandler);

	glMatrixMode(GL_PROJECTION);
	w = 500; h = 500;
	gluOrtho2D(0, w, 0, h);

	glutMainLoop();
	return 0;
}

# endif

# if 0
#include <GL/glut.h>
#include <algorithm>

int w = 500, h = 500;

int poly[7][2] = {
	//100, 100,
	//200, 100,
	//100, 300,

	{50 , 100 },
	{50 , 150},
	{200, 150},
	{200, 200},
	{250, 125},
	{200, 50 },
	{200, 100}
};
int poly_size = 7;

int intersections[100];
int num_intersections = 0;

void getXIntersection(int x1, int y1, int x2, int y2, int sy)
{
	if (sy > y1 && sy < y2 || sy > y2 && sy < y1)
		intersections[num_intersections++] = x1 + (x2 - x1) / (y2 - y1) * (sy - y1); // solving line equation
}

void scanFill()
{
	for (int sy = h; sy > 0; sy--)
	{
		num_intersections = 0;
		for (int i = 0; i < poly_size; i++)
			getXIntersection(poly[i][0], poly[i][1], poly[(i + 1) % poly_size][0], poly[(i + 1) % poly_size][1], sy);

		std::sort(intersections, intersections + num_intersections);

		if (num_intersections >= 2)
			for (int i = 0; i < num_intersections; i += 2)
			{
				glColor3f(1, 0, 0);
				glBegin(GL_LINES);
				glVertex2f(intersections[i], sy);
				glVertex2f(intersections[i + 1], sy);
				glEnd();
				Sleep(1);
				glFlush();
			}
	}

	glFlush();
}

void drawPolygon()
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < poly_size; ++i)
		glVertex2i(poly[i][0], poly[i][1]);
	glEnd();
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawPolygon();

	scanFill();
	//glColor3f(0, 1, 0);
	//for (int s = h; s >= 0; --s)
	//{
	//	num_intersections = 0;
	//	for (int i = 0; i < poly_size; ++i)
	//	{
	//		int xmin = std::min(poly[i][0], poly[(i + 1) % poly_size][0]);
	//		int ymin = std::min(poly[i][1], poly[(i + 1) % poly_size][1]);
	//		int xmax = std::max(poly[i][0], poly[(i + 1) % poly_size][0]);
	//		int ymax = std::max(poly[i][1], poly[(i + 1) % poly_size][1]);
	//		getXIntersection(poly[i][0], poly[i][1], poly[(i + 1) % poly_size][0], poly[(i + 1) % poly_size][1], s);
	//	}
	//
	//	std::sort(intersections, intersections + num_intersections);
	//
	//	//Sleep(1);
	//
	//	if (num_intersections >= 2)
	//	{
	//		for (int i = 0; i < num_intersections; i += 2)
	//		{
	//			glBegin(GL_LINES);
	//			glVertex2i(intersections[i], s);
	//			glVertex2i(intersections[i + 1], s);
	//			glEnd();
	//			glFlush();
	//		}
	//	}
	//
	//}

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(w, h);
	glutCreateWindow("scan line");

	glClearColor(0.1, 0.1, 0.1, 1);
	gluOrtho2D(0, 500, 0, 500);
	glutDisplayFunc(displayHandler);
	glutMainLoop();

	return 0;
}
# endif