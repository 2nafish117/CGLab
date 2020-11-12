#include <GL/glut.h>
#include <iostream>

# if 1
struct vec3
{
	union
	{
		struct
		{
			float r, g, b;
		};
		float data[3];
	};
};


double x[4] = { 100, 200, 300, 400 };
double y[4] = { 200, 50, 120, 350 };
int pointIndex = 0;


void drawPoint(double x, double y, vec3 color)
{
	glColor3fv(color.data);
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (double t = 0; t <= 1; t += 0.01)
	{
		double xt = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
		double yt = pow(1 - t, 3) * y[0] + 3 * t * pow(1 - t, 2) * y[1] + 3 * pow(t, 2) * (1 - t) * y[2] + pow(t, 3) * y[3];
		drawPoint(xt, yt, { 0, 1, 0 });
	}

	for (int i = 0; i < 4; ++i)
	{
		drawPoint(x[i], y[i], { 1, 0, 0 });
	}

	glFlush();
}

void mouseHandler(int button, int state, int xpos, int ypos)
{
	std::cout << xpos << " " << 500 - ypos << "\n";
	if (button == GLUT_LEFT && state == GLUT_DOWN)
	{
		x[pointIndex] = xpos;
		y[pointIndex] = 500 - ypos;
		pointIndex++;
		pointIndex = pointIndex % 4;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("curves");

	glutDisplayFunc(displayHandler);
	glutMouseFunc(mouseHandler);
	
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(0, 0, 0, 1);
	glPointSize(10);
	glutMainLoop();

	return 0;
}
# endif
