#include <GL/glut.h>
#include <iostream>

#define WIDTH 500
#define HEIGHT 500

void drawPoint(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0, 0);
	glPointSize(10.0f);
	drawPoint(0, 0);
}

void mouseHandler(int button, int state, int xpos, int ypos)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float xnorm = -2.0f * xpos / WIDTH  + 1.0f;
		float ynorm =  2.0f * ypos / HEIGHT - 1.0f;
		std::cout << "xpos: " << xpos << " ypos: " << ypos << std::endl;
		std::cout << "normailised " << xnorm << " " << ynorm << std::endl;
		drawPoint(xnorm, ynorm);
		glFlush();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello world");

	gluOrtho2D(1, -1, 1, -1);
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouseHandler);
	glutMainLoop();
	return 0;
}