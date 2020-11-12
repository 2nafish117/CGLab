
/*
poly/clipeers/clockwise/ doesnt work
3
200 350
350 350
300 450
4
100 100
100 400
400 400
400 100

poly/clipeers/antoclockwise/ works!!!
3
200 350
300 450
350 350
4
100 100
400 100
400 400
100 400
*/



# if 0
#include <GL/glut.h>
#include <iostream>

# define MAX_POINTS 100

struct vec2
{
	union {
		struct { int x, y; };
		int data[2];
	};
};

vec2 clipped_polygon[MAX_POINTS] = {
	200, 350,
	300, 450,
	350, 350
};
int clipped_size = 3;

vec2 og_polygon[MAX_POINTS] = { 
	200, 350,
	300, 450,
	350, 350
};
int og_size = 3;

vec2 clipping_polygon[MAX_POINTS] = { 
	100, 100,
	400, 100,
	400, 400,
	100, 400
};
int clipping_size = 4;

void drawPolygon(vec2 poly[], int size)
{
	glBegin(GL_LINE_LOOP);
	for(int i = 0;i < size;++i)
		glVertex2iv(poly[i].data);
	glEnd();
}

void printPoly(vec2 poly[], int size)
{
	for (int i = 0; i < size; ++i)
		std::cout << poly[i].x << " " << poly[i].y << "\n";
}


void drawPoint(vec2 pt)
{
	glBegin(GL_POINTS);
		glVertex2iv(pt.data);
	glEnd();
}

vec2 intersection(vec2 p1, vec2 p2, vec2 p3, vec2 p4)
{
	vec2 res;

	int a1 = p2.y - p1.y;
	int b1 = p1.x - p2.x;
	int c1 = p1.y * p2.x - p1.x * p2.y;

	int a2 = p4.y - p3.y;
	int b2 = p3.x - p4.x;
	int c2 = p3.y * p4.x - p3.x * p4.y;

	/*
	int num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x3 * y4 - y3 * x4) * (x1 - x2);
	int den = (x1 - x2) * (y3 - y4) - (x3 - x4) * (y1 - y2);
	*/

	int denom = (a1 * b2 - a2 * b1);
	/*
	if (denom == 0)
	{
		std::cout << "awww shit here we go again\n";
		return { 0, 0 };
	}
	*/
	res.x = (b1 * c2 - c1 * b2) / denom;
	res.y = (a2 * c1 - a1 * c2) / denom;
	return res;
}



bool check_in(vec2 point, vec2 line_pt1, vec2 line_pt2)
{
	return ((line_pt2.y - line_pt1.y) * (point.x - line_pt1.x) - (line_pt2.x - line_pt1.x) * (point.y - line_pt1.y)) >= 0;
}

void clipEdge(vec2 p1, vec2 p2)
{
	vec2 new_poly[MAX_POINTS];
	int size = 0;
	
	for (int j = 0; j < clipped_size; ++j)
	{
		vec2 poly1 = clipped_polygon[j];
		vec2 poly2 = clipped_polygon[(j + 1) % clipped_size];

		// check if they are inside or outside
		bool inside1 = check_in(poly1, p1, p2);
		bool inside2 = check_in(poly2, p1, p2);
		vec2 intersect = intersection(p1, p2, poly1, poly2);
		if (intersect.x == INT_MAX)
			return;

		if (inside1 && inside2)
		{
			// Both vertices are inside : Only the second vertex is added to the output list
			new_poly[size++] = poly2;
		}
		else if (inside1 && !inside2)
		{
			// First vertex is inside while second one is outside : 
			// Only the point of intersection of the edge with the clip boundary is added to the output list

			new_poly[size++] = intersect;
		}
		else if (!inside1 && inside2)
		{
			// First vertex is outside while second one is inside : 
			// Both, the point of intersection of the edge with the clip boundary 
			// and the second vertex are added to the output list

			new_poly[size++] = intersect;
			new_poly[size++] = poly2;
		}
		else
		{
			// Both vertices are outside : No vertices are added to the output list

		}
	}

	clipped_size = size;
	for (int i = 0; i < size; ++i)
		clipped_polygon[i] = new_poly[i];

	printPoly(clipped_polygon, clipped_size);

	// 
	// glColor3f(0, 0, 1);
	// drawPoint(intersect);
}

void clipPolygon()
{
	for (int i = 0; i < clipping_size; ++i)
	{
		vec2 p1 = clipping_polygon[i];
		vec2 p2 = clipping_polygon[(i + 1) % clipping_size];
		clipEdge(p1, p2);
	}
}

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	glLineWidth(3);
	//drawPolygon(og_polygon, og_size);
	glColor3f(0, 1, 0);
	drawPolygon(clipping_polygon, clipping_size);

	printPoly(clipped_polygon, clipped_size);

	clipPolygon();

	printPoly(clipped_polygon, clipped_size);

	glLineWidth(1);
	glColor3f(1, 0, 0);
	drawPolygon(clipped_polygon, clipped_size);
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow("poly clipping");
	
	glClearColor(0.1, 0.1, 0.1, 1);
	glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500, 500, -500, 500, -500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(displayHandler);
	glutMainLoop();
	return 0;
}
# endif

# if 0
#include <GL/glut.h>
#include<iostream>

int polygon[20][2], numVertices, orig_polygon[20][2], orig_numVertices, clipWin[20][2], clip_numVertices;

int w = 500, h = 500;
int x_intersection(int x1, int y1, int x2, int y2,
	int x3, int y3, int x4, int y4)
{
	int num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x3 * y4 - y3 * x4) * (x1 - x2);
	int den = (x1 - x2) * (y3 - y4) - (x3 - x4) * (y1 - y2);
	return num / den;
}

int y_intersection(int x1, int y1, int x2, int y2,
	int x3, int y3, int x4, int y4)
{
	int num = (x1 * y2 - y1 * x2) * (y3 - y4) - (x3 * y4 - y3 * x4) * (y1 - y2);
	int den = (x1 - x2) * (y3 - y4) - (x3 - x4) * (y1 - y2);
	return num / den;
}

//clip against one edge of the window
void clip(int x1, int y1, int x2, int y2)
{
	int i, k;
	int newPoly[20][2], newNumVertices = 0;

	//(ix, iy) and (kx, ky) are adjacent vertices
	for (i = 0; i < numVertices; i++)
	{
		k = (i + 1) % numVertices;
		int ix = polygon[i][0], iy = polygon[i][1];
		int kx = polygon[k][0], ky = polygon[k][1];

		//decision paramters
		int i_pos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);
		int k_pos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);

		//CASE 1: both inside
		if (i_pos >= 0 && k_pos >= 0)
		{
			newPoly[newNumVertices][0] = kx;
			newPoly[newNumVertices][1] = ky;
			newNumVertices++;
		}

		//CASE 2: 1st outside, 2nd inside
		if (i_pos < 0 && k_pos >= 0)
		{
			newPoly[newNumVertices][0] = x_intersection(x1, y1, x2, y2, ix, iy, kx, ky);
			newPoly[newNumVertices][1] = y_intersection(x1, y1, x2, y2, ix, iy, kx, ky);
			newNumVertices++;
			newPoly[newNumVertices][0] = kx;
			newPoly[newNumVertices][1] = ky;
			newNumVertices++;
		}

		//CASE 3: 1st inside, 2nd outside
		if (i_pos >= 0 && k_pos < 0)
		{
			newPoly[newNumVertices][0] = x_intersection(x1, y1, x2, y2, ix, iy, kx, ky);
			newPoly[newNumVertices][1] = y_intersection(x1, y1, x2, y2, ix, iy, kx, ky);
			newNumVertices++;
		}

		//CASE 4: both outside - do nothing
		if (i_pos < 0 && k_pos < 0) {}
	}

	//COPY ONLY IF CLIPPING WAS DONE
	for (i = 0; i < newNumVertices; i++)
	{
		polygon[i][0] = newPoly[i][0];
		polygon[i][1] = newPoly[i][1];
	}
	numVertices = newNumVertices;


}

void drawPolygon(int poly[][2], int nrOfVertices)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < nrOfVertices; i++)
		glVertex2iv(poly[i]);
	glEnd();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Clip window
	glColor3f(1.f, 0.f, 0.f);
	drawPolygon(clipWin, clip_numVertices);

	//Original polygon
	glColor3f(0.f, 1.f, 0.f);
	drawPolygon(orig_polygon, orig_numVertices);

	//Clip - get clipped Polygon
	int i, k;
	for (i = 0; i < clip_numVertices; i++)
	{
		k = (i + 1) % clip_numVertices;
		int ix = clipWin[i][0]; int iy = clipWin[i][1];
		int kx = clipWin[k][0]; int ky = clipWin[k][1];

		clip(ix, iy, kx, ky);
	}

	//Draw clipped polygon
	glColor3f(0.f, 0.f, 1.f);
	drawPolygon(polygon, numVertices);

	//std::cout << "Numvertices = "<<numVertices;


	glFlush();
}

void init()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
}

void getInput()
{
	int i;
	std::cout << "No. of vertices of polygon : " << std::endl;
	std::cin >> numVertices;
	orig_numVertices = numVertices;

	std::cout << "Enter coordinates \n";
	for (i = 0; i < numVertices; i++)
	{
		std::cin >> polygon[i][0] >> polygon[i][1];
		orig_polygon[i][0] = polygon[i][0];
		orig_polygon[i][1] = polygon[i][1];
	}

	std::cout << "No. of vertices of Clipping Window: " << std::endl;
	std::cin >> clip_numVertices;

	std::cout << "Enter clipping coordinates \n";
	for (i = 0; i < clip_numVertices; i++)
	{
		std::cin >> clipWin[i][0] >> clipWin[i][1];
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);

	getInput();

	glutCreateWindow("Sutherland - Hodgeman");
	glutDisplayFunc(display);
	init();

	glutMainLoop();
	return 0;
}
# endif

# if 0
#include <GL/glut.h>

void displayHandler()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_SCISSOR_TEST);
	

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(300, 100);
	glVertex2f(300, 300);
	glVertex2f(100, 300);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(200, 200);
	glVertex2f(400, 200);
	glVertex2f(250, 400);
	glEnd();

	glScissor(100, 100, 200, 200);
	glColor3f(0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(200, 200);
	glVertex2f(400, 200);
	glVertex2f(250, 400);
	glEnd();

	//glScissor(0, 0, 400, 400);
	//glColor3d(0, 1, 0);
	//glBegin(GL_POLYGON);
	//glVertex2f(-400, -400);
	//glVertex2f(400, -400);
	//glVertex2f(400, 400);
	//glVertex2f(-400, 400);
	//glEnd();
	//
	//glScissor(0, 0, 200, 200);
	//glColor3d(1, 0, 0);
	//glBegin(GL_POLYGON);
	//glVertex2f(-400, -400);
	//glVertex2f(400, -400);
	//glVertex2f(400, 400);
	//glVertex2f(-400, 400);
	//glEnd();



	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow("poly clipping");

	glClearColor(0.1, 0.1, 0.1, 1);
	glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 500, 0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(displayHandler);
	glutMainLoop();
	return 0;
}

# endif

#include<GL/glut.h>

typedef struct
{
	double x, y;
}vect;

vect poly[10];

void init()
{
	poly[0].x = 100; poly[0].y = 450;
	poly[1].x = 250; poly[1].y = 300;
	poly[2].x = 500; poly[2].y = 250;
	poly[3].x = 350; poly[3].y = 100;
}

void draw(vect* i, int y)
{
	glBegin(GL_POLYGON);
	for (int k = 0; k < y; k++)
		glVertex2f(i[k].x, i[k].y);
	glEnd();
}


// void scissorScam()
// {
// 	glClearColor(1, 1, 1, 1);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glColor3f(0.6, 0.2, 0.8);
// 	glBegin(GL_POLYGON);
// 		// topleft : 500 ,600 ; bottom right : 900, 200
// 		glVertex2f(200, 200);
// 		glVertex2f(200, 450);
// 		glVertex2f(450, 450);
// 		glVertex2f(450, 200);
// 	glEnd();
// 	glFlush();

// 	glColor3f(0, 1, 1);
// 	draw(poly, 4);
// 	glFlush();	

// 	glColor3f(1, 1, 0);
// 	glEnable(GL_SCISSOR_TEST);	
// 	glScissor(200, 200, 250, 250);
// 	draw(poly, 4);
// 	glFlush();
// }

void stencilScam()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1); //draw your polygon here	
	draw(poly, 4);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glColor3f(0, 1, 0); //draw the clipping window
	glBegin(GL_POLYGON);
	glVertex2f(200, 100);
	glVertex2f(200, 350);
	glVertex2f(450, 400);
	glVertex2f(450, 100);
	glEnd();

	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glColor3f(1.0, 0, 0);//draw the polygon again	
	draw(poly, 4);

	// glDisable(GL_STENCIL_TEST);
	glFlush();

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB
		| GLUT_STENCIL);
	glutInitWindowSize(500, 500);
	init();
	glutCreateWindow("hkk nin amman");
	gluOrtho2D(0, 500, 0, 500);
	//glutDisplayFunc(scissorScam);
	//glutDisplayFunc(stencilScam);
	stencilScam();
	glutMainLoop();
}
