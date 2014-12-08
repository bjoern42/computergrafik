// Sample code for Übung 2
#include <stdio.h>
#include <iostream>

using namespace std;

#include "Projection.h"

#include <Cuboid.h>
#include <Point.hpp>
#include <Color.hpp>
#include <Bresenham.hpp>


// might be you have to swith to
// #include "glut.h" depending on your GLUT installation
#include "GL/glut.h"

////////////////////////////////////////////////////////////
//
// system relevant global variables
//TARGET_DIR = Debug/

void drawPoint(Point p, Color c);
void drawSinglePoint(Point p, Color c);
void drawLine(Point p1, Point p2, Color c);
void drawCircle(Point p, int r, Color c);
void drawCuboid(Cuboid *cuboid, float fFocus, Color c);

Point convertToPoint(CVec4f vec);

// window width and height (choose an appropriate size)
int g_iWidth  = 800;
int g_iHeight = 800;

// global variable to tune the timer interval
int g_iTimerMSecs;

//
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// private, global variables ... replace by your own ones
//
// some global state variables used to describe ...
//------------------------------------------

	
Bresenham b(drawPoint);
Projection p;

Cuboid *c1, *c2, *c3;

//
/////////////////////////////////////////////////////////////

// function to initialize our own variables
void init () {
	// init timer interval
	g_iTimerMSecs = 10;
	float originData[4];
	originData[0] = 50;
	originData[1] = 50;
	originData[2] = -50;
	originData[3] = 1;
	
	CVec4f origin(originData);
	
	c1 = new Cuboid(origin, 200, 200, 50);
	
	originData[0] = -80;
	originData[1] = -150;
	originData[2] = -50;
	origin = CVec4f(originData);
	c2 = new Cuboid(origin, 50, 50 , 10);
	
	originData[0] = -200;
	originData[1] = 50;
	originData[2] = -50;
	origin = CVec4f(originData);
	c3 = new Cuboid(origin, 100, 50, 100);
	//c1->printPoints();
}

// function to initialize the view to ortho-projection
void initGL () {
	glViewport (0, 0, g_iWidth, g_iHeight);	// Establish viewing area to cover entire window.

	glMatrixMode (GL_PROJECTION);			// Start modifying the projection matrix.
	glLoadIdentity ();						// Reset project matrix.
	glOrtho (-g_iWidth/2, g_iWidth/2, -g_iHeight/2, g_iHeight/2, 0, 1);	// Map abstract coords directly to window coords.

	// tell GL that we draw to the back buffer and
	// swap buffers when image is ready to avoid flickering
	glDrawBuffer (GL_BACK);

	// tell which color to use to clear image
	glClearColor (0,0,0,1);
}

void destroy(){
	delete c1;
	delete c2;
	delete c3;
}

// timer callback function
void timer (int value) {
	///////
	// update your variables here ...
	//
	
	
	//
	///////

	// the last two lines should always be
	glutPostRedisplay ();
	//glutTimerFunc (g_iTimerMSecs, timer, 0);	// call timer for next iteration
}

void drawXYAxis(Color c, int width, int height, int meassurement){
	int meassurementLength = 6;
	Point x1(-width/2, 0);
	Point x2(width/2, 0);
	Point y1(0, -height/2);
	Point y2(0, height/2);
	drawLine(x1, x2, c);
	drawLine(y1, y2, c);

	for(int i=0; i< width; i+=meassurement){
		drawLine(Point(i, -meassurementLength/2), Point(i, meassurementLength/2), c);
		drawLine(Point(-i, -meassurementLength/2), Point(-i, meassurementLength/2), c);
		drawLine(Point(-meassurementLength/2, i), Point(meassurementLength/2, i), c);
		drawLine(Point(-meassurementLength/2, -i), Point(meassurementLength/2, -i), c);
	}
}

// display callback function
void display1 (void) {
	glClear (GL_COLOR_BUFFER_BIT);
	///////
	
	float fFocus = 50;
	//draw stuff
	Color c(0.0f, 255.0f, 0.0f);
	drawXYAxis(c, g_iWidth, g_iHeight, 10);
	
	c.set(2.4f, 0.1f, 0.1f);
	drawCuboid(c1, fFocus, c);
	
	c.set(0.1f, 2.4f, 0.1f);
	drawCuboid(c2, fFocus, c);
	
	c.set(0.1f, 0.1f, 2.4f);
	drawCuboid(c3, fFocus, c);
		
	// In double buffer mode the last
	// two lines should alsways be
	glFlush ();
	glutSwapBuffers (); // swap front and back buffer
}

void drawPoint(Point p, Color c){
	glVertex2i(p.x, p.y);
}

void drawSinglePoint(Point p, Color c){
	glBegin(GL_POINTS);
	glColor3f(c.r, c.g, c.b);
	drawPoint(p, c);
	glEnd();
}

void drawLine (Point p1, Point p2, Color c){
	glBegin(GL_POINTS);
	glColor3f(c.r, c.g, c.b);
	b.bhamLine(p1, p2, c);
	glEnd();
}

void drawCircle(Point p, int r, Color c){
	glBegin(GL_POINTS);
	glColor3f(c.r, c.g, c.b);
	b.bhamCircle(p, r, c);
	glEnd();
}

Point convertToPoint(CVec4f vec){
	return Point(vec(0), vec(1));
}

void drawCuboid(Cuboid *cuboid, float fFocus, Color c){
	Cuboid* projectedCuboid = p.projektZ(fFocus, cuboid);
	
	glBegin(GL_POINTS);
	glColor3f(c.r, c.g, c.b);
	
	//*
	//front
	b.bhamLine(convertToPoint(projectedCuboid->getFrontBottomLeft()), convertToPoint(projectedCuboid->getFrontBottomRight()), c);
	b.bhamLine(convertToPoint(projectedCuboid->getFrontBottomLeft()), convertToPoint(projectedCuboid->getFrontTopLeft()), c);
	b.bhamLine(convertToPoint(projectedCuboid->getFrontTopLeft()), convertToPoint(projectedCuboid->getFrontTopRight()), c);
	b.bhamLine(convertToPoint(projectedCuboid->getFrontTopRight()), convertToPoint(projectedCuboid->getFrontBottomRight()), c);
	c.darken(0.2f);
	glColor3f(c.r, c.g, c.b);
	//back
	b.bhamLine(convertToPoint(projectedCuboid->getBackBottomLeft()), convertToPoint(projectedCuboid->getBackBottomRight()), c);
	b.bhamLine(convertToPoint(projectedCuboid->getBackBottomLeft()), convertToPoint(projectedCuboid->getBackTopLeft()), c);
	b.bhamLine(convertToPoint(projectedCuboid->getBackTopLeft()), convertToPoint(projectedCuboid->getBackTopRight()), c);
	b.bhamLine(convertToPoint(projectedCuboid->getBackTopRight()), convertToPoint(projectedCuboid->getBackBottomRight()), c);
	c.lighten(0.5f);
	glColor3f(c.r, c.g, c.b);
	//diagonal
	b.bhamLine(convertToPoint(projectedCuboid->getFrontTopLeft()), convertToPoint(projectedCuboid->getBackTopLeft()), c);
	b.bhamLine(convertToPoint(projectedCuboid->getFrontTopRight()), convertToPoint(projectedCuboid->getBackTopRight()), c);
	b.bhamLine(convertToPoint(projectedCuboid->getFrontBottomRight()), convertToPoint(projectedCuboid->getBackBottomRight()), c);
	b.bhamLine(convertToPoint(projectedCuboid->getFrontBottomLeft()), convertToPoint(projectedCuboid->getBackBottomLeft()), c);

	delete projectedCuboid;
	glEnd();
}

int main (int argc, char **argv) {
	glutInit (&argc, argv);
	// we have to use double buffer to avoid flickering
	// TODO: lookup "double buffer", what is it for, how is it used ...
	// second image is drawn in the background and displayed after it's finished.
	// -> you don't see the image being drawn
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize (g_iWidth, g_iHeight);
	glutCreateWindow ("Uebung 2");

	init ();	// init my variables first
	initGL ();	// init the GL (i.e. view settings, ...)

	// assign callbacks
	//glutTimerFunc (10, timer, 0);
	glutDisplayFunc (display1);
	// you might want to add a resize function analog to
	// Übung1 using code similar to the initGL function ...

	// start main loop
	display1();
	glutMainLoop ();
	
	destroy(); // free stuff
	
	return 0;
}
