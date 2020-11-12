#include <GL/glut.h>

int carListHandle = 1;
float position = 0.0f;
float speed = 1.0f;
int wheelListHandle = 2;
float radius = 50;
float wheelOffsetX = 40;
float wheelOffsetY = 25;

void makeWheelList()
{
	glNewList(wheelListHandle, GL_COMPILE);
	glColor3f(0.7, 0.3, 0.2);
	glutSolidSphere(radius, 10, 10);
	glEndList();
}

void makeCarList()
{
	glNewList(carListHandle, GL_COMPILE);
	glColor3f(0.7, 0.3, 0.2);
	glBegin(GL_QUADS);
	glVertex2f( 25,  200);
	glVertex2f( 25, -25);
	glVertex2f(-25, -25);
	glVertex2f(-25,  200);
	glEnd();
	glEndList();
}

void updateCar()
{
	position += speed;
}

void mouseHandler(int button, int state, int xpos, int ypos)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		speed =  10.0f;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		speed = -10.0f;
	updateCar();
	glutPostRedisplay();
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(position, 0, 0);
	glCallList(carListHandle);

	glLoadIdentity();
	glTranslatef(position + wheelOffsetX, -wheelOffsetY, 0);
	glCallList(wheelListHandle);

	glLoadIdentity();
	glTranslatef(position - wheelOffsetX, -wheelOffsetY, 0);
	glCallList(wheelListHandle);

	glLoadIdentity();
	glTranslatef(position, 200, 0);
	glScalef(0.5, 0.5, 0.5);
	glCallList(wheelListHandle);

	glutPostRedisplay();
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Car list");
	
	glutDisplayFunc(displayHandler);
	glutMouseFunc(mouseHandler);

	glClearColor(0.1, 0.1, 0.1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -250, 250);
	glMatrixMode(GL_MODELVIEW);

	makeCarList();
	makeWheelList();
	glutMainLoop();
	
	return 0;
}