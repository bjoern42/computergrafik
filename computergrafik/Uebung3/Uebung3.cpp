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

Cuboid *cuboid;

//
/////////////////////////////////////////////////////////////

// function to initialize our own variables
void init () {
	// init timer interval
	g_iTimerMSecs = 10;
	float originData[4];
	originData[0] = 10;
	originData[1] = 10;
	originData[2] = -10;
	originData[3] = 0;
	
	CVec4f origin(originData);
	
	cuboid = new Cuboid(origin, 10, 10, 10);
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
	delete cuboid;
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
	int meassurementLength = 10;
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
	
	//draw stuff
	Color c_axis(0,255,0);
	drawXYAxis(c_axis, g_iWidth, g_iHeight, 10);
	
	Color c(255,0,0);
	drawCuboid(cuboid, 100, c);

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
	p.projektZ(fFocus, cuboid);
	
	glBegin(GL_POINTS);
	glColor3f(c.r, c.g, c.b);
	
	//*
	//front
	b.bhamLine(convertToPoint(cuboid->getFrontBottomLeft()), convertToPoint(cuboid->getFrontBottomRight()), c);
	b.bhamLine(convertToPoint(cuboid->getFrontBottomLeft()), convertToPoint(cuboid->getFrontTopLeft()), c);
	b.bhamLine(convertToPoint(cuboid->getFrontTopLeft()), convertToPoint(cuboid->getFrontTopRight()), c);
	b.bhamLine(convertToPoint(cuboid->getFrontTopRight()), convertToPoint(cuboid->getFrontBottomRight()), c);
	glColor3f(0, 0, 255);
	//back
	b.bhamLine(convertToPoint(cuboid->getBackBottomLeft()), convertToPoint(cuboid->getBackBottomRight()), c);
	b.bhamLine(convertToPoint(cuboid->getBackBottomLeft()), convertToPoint(cuboid->getBackTopLeft()), c);
	b.bhamLine(convertToPoint(cuboid->getBackTopLeft()), convertToPoint(cuboid->getBackTopRight()), c);
	b.bhamLine(convertToPoint(cuboid->getBackTopRight()), convertToPoint(cuboid->getBackBottomRight()), c);
	//diagonal
	b.bhamLine(convertToPoint(cuboid->getFrontTopLeft()), convertToPoint(cuboid->getBackTopLeft()), c);
	b.bhamLine(convertToPoint(cuboid->getFrontTopRight()), convertToPoint(cuboid->getBackTopRight()), c);
	b.bhamLine(convertToPoint(cuboid->getFrontBottomRight()), convertToPoint(cuboid->getBackBottomRight()), c);
	b.bhamLine(convertToPoint(cuboid->getFrontBottomLeft()), convertToPoint(cuboid->getBackBottomLeft()), c);

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
