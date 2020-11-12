#include <GL/glut.h>
#include <iostream>
#include <cstdlib>

#define WIDTH 1000
#define HEIGHT 1000

int numSubdivisions = 5;
float theta[3] = { 0, 0, 0 };
int axis = 0;

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

void drawTriangle(vec3 a, vec3 b, vec3 c, vec3 color)
{
	glColor3fv(color.data);
	glBegin(GL_TRIANGLES);
		glVertex3fv(a.data);
		glVertex3fv(b.data);
		glVertex3fv(c.data);
	glEnd();
}

void drawTetrahedron(vec3 a, vec3 b, vec3 c, vec3 d, vec3 color)
{
	drawTriangle(a, b, c, color);
	drawTriangle(d, c, b, color);
	drawTriangle(d, a, b, color);
	drawTriangle(d, a, c, color);
}

void randomizeColor(vec3* color)
{
	if (color == nullptr)
		return;
	color->r = (rand() % 255) / 255.0f;
	color->g = (rand() % 255) / 255.0f;
	color->b = (rand() % 255) / 255.0f;
}

void serp3D(vec3 a, vec3 b, vec3 c, vec3 d, int m)
{
	vec3 color = { 1, 0, 0 };
	// randomizeColor(&color);

	if (m <= 0)
	{
		drawTetrahedron(a, b, c, d, color);
		return;
	}

	vec3 mid[6];
	mid[0] = { (a.x + b.x) / 2, (a.y + b.y) / 2 , (a.z + b.z) / 2 };
	mid[1] = { (c.x + b.x) / 2, (c.y + b.y) / 2 , (c.z + b.z) / 2 };
	mid[2] = { (a.x + c.x) / 2, (a.y + c.y) / 2 , (a.z + c.z) / 2 };
	mid[3] = { (a.x + d.x) / 2, (a.y + d.y) / 2 , (a.z + d.z) / 2 };
	mid[4] = { (d.x + b.x) / 2, (d.y + b.y) / 2 , (d.z + b.z) / 2 };
	mid[5] = { (d.x + c.x) / 2, (d.y + c.y) / 2 , (d.z + c.z) / 2 };

	if (m == 1)
	{
		drawTetrahedron(mid[1], mid[0], mid[4], b, color);
		drawTetrahedron(mid[1], mid[2], mid[5], c, color);
		drawTetrahedron(mid[2], mid[0], mid[3], a, color);
		drawTetrahedron(mid[5], mid[4], mid[3], d, color);
		return;
	}

	serp3D(mid[1], mid[0], mid[4], b, m - 1);
	serp3D(mid[1], mid[2], mid[5], c, m - 1);
	serp3D(mid[2], mid[0], mid[3], a, m - 1);
	serp3D(mid[5], mid[4], mid[3], d, m - 1);
	return;
}

void mouseHandler(int button, int state, int xpos, int ypos)
{
	//if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	//{
	//	numSubdivisions++;
	//	glutSwapBuffers();
	//}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
}

void spin(float speed)
{
	theta[axis] += speed;
	if (theta[axis] >= 360.0)
		theta[axis] -= 360.0;
	glutPostRedisplay();
}

void displayHandler()
{
	vec3 a = { 0.95, 0.95 , 0.0};
	vec3 b = { 0.0, -0.95 , 0.0};
	vec3 c = { -0.95, 0.95 , 0.0};
	vec3 d = { 0.0, 0.0 , 0.95};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0, 0);

	glLoadIdentity();
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	spin(0.1);

	serp3D(a, b, c, d, numSubdivisions);
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("serp3D");

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glOrtho(1, -1, 1, -1, 1, -1);

	glutDisplayFunc(displayHandler);
	glutMouseFunc(mouseHandler);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}