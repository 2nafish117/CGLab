#include <GL/glut.h>
#include <iostream>
#include <cstdlib>

#define WIDTH 1280
#define HEIGHT 720

int numSubdivisions = 1;

struct vec2
{
	union
	{
		struct {
			float x, y;
		};
		float data[2];
	};
};

struct vec3
{
	union
	{
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
		float data[3];
	};
};

void drawPoint(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void drawTriangle(vec2 a, vec2 b, vec2 c, vec3 color)
{
	glColor3fv(color.data);
	glBegin(GL_TRIANGLES);
	glVertex2fv(a.data);
	glVertex2fv(b.data);
	glVertex2fv(c.data);
	glEnd();
}

void randomizeColor(vec3* color)
{
	if (color == nullptr)
		return;
	color->r = (rand() % 255) / 255.0f;
	color->g = (rand() % 255) / 255.0f;
	color->b = (rand() % 255) / 255.0f;
}

void serp2D(vec2 a, vec2 b, vec2 c, int m)
{
	if (m <= 0)
		return;

	vec2 mid[3];
	mid[0] = { (a.x + b.x) / 2, (a.y + b.y) / 2 };
	mid[1] = { (c.x + b.x) / 2, (c.y + b.y) / 2 };
	mid[2] = { (a.x + c.x) / 2, (a.y + c.y) / 2 };

	vec3 color = { 1, 0, 0 };
	randomizeColor(&color);

	drawTriangle(a, b, c, color);
	drawTriangle(mid[0], mid[1], mid[2], {0, 0, 0});

	serp2D(a, mid[0], mid[2], m - 1);
	serp2D(b, mid[0], mid[1], m - 1);
	serp2D(c, mid[2], mid[1], m - 1);
}

// more optimised
void serp2DNew(vec2 a, vec2 b, vec2 c, int m)
{
	vec3 color = { 1, 0, 0 };
	randomizeColor(&color);
	if (m <= 1)
	{
		drawTriangle(a, b, c, color);
		return;
	}
	vec2 mid[3];
	mid[0] = { (a.x + b.x) / 2, (a.y + b.y) / 2 };
	mid[1] = { (c.x + b.x) / 2, (c.y + b.y) / 2 };
	mid[2] = { (a.x + c.x) / 2, (a.y + c.y) / 2 };

	if (m == 2)
	{
		drawTriangle(a, mid[0], mid[2], color);
		drawTriangle(b, mid[0], mid[1], color);
		drawTriangle(c, mid[2], mid[1], color);
		return;
	}

	serp2D(a, mid[0], mid[2], m - 1);
	serp2D(b, mid[0], mid[1], m - 1);
	serp2D(c, mid[2], mid[1], m - 1);
}

void mouseHandler(int button, int state, int xpos, int ypos)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		numSubdivisions++;
		glutSwapBuffers();
	}
}

void displayHandler()
{
	vec2 a = {  0.9, 0.7758 };
	vec2 b = {  0.0, -0.7758 };
	vec2 c = { -0.9, 0.7758 };

	//vec2 a = { 0.95, 0.95 };
	//vec2 b = { 0.0, -0.95 };
	//vec2 c = { -0.95, 0.95 };

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0, 0);

	serp2DNew(a, b, c, numSubdivisions);
	glutSwapBuffers();
}

void displayDebug()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0, 0);
	glPointSize(10.0f);
	drawPoint(0, 0);
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("serp2D");

	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluOrtho2D(1, -1, 1, -1);

	glutDisplayFunc(displayHandler);
	glutMouseFunc(mouseHandler);
	glutMainLoop();
	return 0;
}