#include<GL/glut.h>
#include<cstdio>

int iterations = 4;

struct vec3
{
	union {
		struct {
			double x, y, z;
		};
		double data[3];
	};
};

vec3 tetra[4] = {
	100, -100, -100,	// 0
	-100, -100, -100,	// 1
	0, 100, 0,			// 2
	0, 0, 100			// 3
};

// 0 1 2
// 3 2 1
// 3 0 2
// 3 0 1

void drawTriangle(vec3 a, vec3 b, vec3 c)
{
	glBegin(GL_TRIANGLES);
	glVertex3dv(a.data);
	glVertex3dv(b.data);
	glVertex3dv(c.data);
	glEnd();
}

void subdivideTriangle(vec3 a, vec3 b, vec3 c, int iter)
{
	if (iter <= 0)
	{
		drawTriangle(a, b, c);
		return;
	}

	vec3 p1, p2, p3;
	for (int i = 0; i < 3; ++i)
		p1.data[i] = (a.data[i] + b.data[i]) / 2;
	for (int i = 0; i < 3; ++i)
		p2.data[i] = (b.data[i] + c.data[i]) / 2;
	for (int i = 0; i < 3; ++i)
		p3.data[i] = (c.data[i] + a.data[i]) / 2;

	subdivideTriangle(a, p1, p3, iter - 1);
	subdivideTriangle(b, p1, p2, iter - 1);
	subdivideTriangle(c, p2, p3, iter - 1);
}

void serp3D(int iter)
{
	glColor3f(0, 0, 0);
	subdivideTriangle(tetra[0], tetra[1], tetra[2], iter);
	glColor3f(0, 1, 0);
	subdivideTriangle(tetra[3], tetra[2], tetra[1], iter);
	glColor3f(0, 0, 1);
	subdivideTriangle(tetra[3], tetra[0], tetra[2], iter);
	glColor3f(1, 0, 0);
	subdivideTriangle(tetra[3], tetra[0], tetra[1], iter);
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	serp3D(iterations);
	//glColor3f(1, 0, 0);
	//glBegin(GL_TRIANGLES);
	//glVertex2d(100, 100);
	//glVertex2d(100, 0);
	//glVertex2d(0, 100);
	//glEnd();

	glFlush();
}

int main(int argv, char** argc)
{
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Seirpinski Gasket");
	
	glutDisplayFunc(displayHandler);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1, 0.1, 0.1, 1);
	glOrtho(-250, 250, -250, 250, -250, 250);

	glutMainLoop();
}