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
void drawCuboid(Cuboid *cuboid, Color c);

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
	originData[0] = 0;
	originData[1] = 0;
	originData[2] = 0;
	originData[3] = 0;
	
	CVec4f origin(originData);
	
	cuboid = new Cuboid(origin, 50, 50, 50);
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
	glutTimerFunc (g_iTimerMSecs, timer, 0);	// call timer for next iteration
}

// display callback function
void display1 (void) {
	glClear (GL_COLOR_BUFFER_BIT);
	///////
	
	//draw stuff
	Color c(255,0,0);
	Point p(10, 10);
	Point p2(10, 10);
	//drawLine(p, p2, c);
	//drawSinglePoint(p2, c);
	
	
	drawCuboid(cuboid, c);

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

void drawCuboid(Cuboid *cuboid, Color c){
	CVec4f *points = cuboid->getPoints();
	for(int i=0; i<8; i++){
		cout << points[i](0) << "/" << points[i](1) << "/" << points[i](2) << "/" << points[i](3) << endl;
	}
	p.projektZ(40, cuboid);
	
	glBegin(GL_POINTS);
	glColor3f(c.r, c.g, c.b);
	
	cout << "-----------------------------" << endl;
	for(int i=0; i<8; i++){
		cout << points[i](0) << "/" << points[i](1) << "/" << points[i](2) << "/" << points[i](3) << endl;
	}
	
	//front
	b.bhamLine(Point(points[0](0), points[0](1)), Point(points[1](0), points[1](1)), c);
	b.bhamLine(Point(points[0](0), points[0](1)), Point(points[2](0), points[2](1)), c);
	b.bhamLine(Point(points[1](0), points[1](1)), Point(points[3](0), points[3](1)), c);
	b.bhamLine(Point(points[2](0), points[2](1)), Point(points[3](0), points[3](1)), c);
	//back
	b.bhamLine(Point(points[4](0), points[4](1)), Point(points[5](0), points[5](1)), c);
	b.bhamLine(Point(points[4](0), points[4](1)), Point(points[6](0), points[6](1)), c);
	b.bhamLine(Point(points[5](0), points[5](1)), Point(points[7](0), points[7](1)), c);
	b.bhamLine(Point(points[6](0), points[6](1)), Point(points[7](0), points[7](1)), c);
	//front to back
	b.bhamLine(Point(points[0](0), points[0](1)), Point(points[4](0), points[4](1)), c);
	b.bhamLine(Point(points[1](0), points[1](1)), Point(points[5](0), points[5](1)), c);
	b.bhamLine(Point(points[2](0), points[2](1)), Point(points[6](0), points[6](1)), c);
	b.bhamLine(Point(points[3](0), points[3](1)), Point(points[7](0), points[7](1)), c);
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
	glutMainLoop ();
	
	destroy(); // free stuff
	
	return 0;
}
