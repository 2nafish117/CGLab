#include <iostream>
#include <GL/glut.h>
#include <cmath>

float red = 1;
float green = 0;
float blue = 0;

struct vec2
{
	float x, y;
};

enum CurveType { LICK_MY_ASS = 1, CANCER_PATIENT, WEED, TOO_HIGH };
int currentCurve = LICK_MY_ASS;

void drawPoint(vec2 pt)
{
	glBegin(GL_POINTS);
	glVertex2f(pt.x, pt.y);
	glEnd();
}

void drawCurve(int type)
{
	// std::cout << "drawCurve called\n";
	const float a = 100, b = 50;
	const float twoPi = 2 * 3.1415926;
	vec2 centre = { 0, 0 };
	float theta = 0.0;
	float dtheta = 0.01;
	// drawPoint({ 0, 0 });
	while (theta <= twoPi)
	{
		// float r = a * cos(theta);
		// vec2 point = { centre.x + a * cos(theta), centre.y + a * sin(theta) };

		float r = 0;
		switch (type) 
		{
		case LICK_MY_ASS: r = a * cos(theta) + b; break;
		case CANCER_PATIENT: r = a * (1 + cos(theta)); break;
		case WEED: r = a * cos(3 * theta); break;
		case TOO_HIGH: r = (a / 4.0) * theta; break;
		default: break;
		}

		vec2 point = {
			centre.x + r * cos(theta),
			centre.y + r * sin(theta)
		};

		drawPoint(point);
		theta += dtheta;
	}
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(red, green, blue);
	drawCurve(currentCurve);
	glFlush();
}

void curvePickerMenu(int item)
{
	currentCurve = item;
	glutPostRedisplay();
}

void colorPickerMenu(int item)
{
	switch (item)
	{
	case 1:
		red = 1;
		green = 0;
		blue = 0;
		break;
	case 2:
		red = 0;
		green = 1;
		blue = 0;
		break;
	case 3:
		red = 0;
		green = 0;
		blue = 1;
		break;
	case 4:
		red = 0.2;
		green = 0.2;
		blue = 0.2;
		break;
	default:
		std::cout << "some shaat is wrong in colorPickerMenu\n";
		break;
	}
	glutPostRedisplay();
}

void mainMenu(int item)
{
	switch (item)
	{
	case 3:
		exit(0);
	default:
		std::cout << "some shaat is wrong in mainMenu\n";
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("HKK suck Shaat!!");

	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250, 250, -250, 250);
	glPointSize(2);

	int curvePickerId = glutCreateMenu(curvePickerMenu);
	glutAddMenuEntry("lickMyAss", 1);
	glutAddMenuEntry("cancerPatient", 2);
	glutAddMenuEntry("weedLeaf", 3);
	glutAddMenuEntry("tooHighForThisShit", 4);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	int colorPickerId = glutCreateMenu(colorPickerMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("BBC", 4);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	glutCreateMenu(mainMenu);
	glutAddSubMenu("drawShit", curvePickerId);
	glutAddSubMenu("colors", colorPickerId);
	glutAddMenuEntry("quit", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	glutDisplayFunc(displayHandler);
	glutMainLoop();

	return 0;
}