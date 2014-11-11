// Sample code for Übung 2
#include <stdio.h>
#include <iostream>

using namespace std;

#include "Transformation.h"
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
void drawLine(Point p1, Point p2, Color c);
void drawCircle(Point p, int r, Color c);

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
/*
float g_iPos;		// ... position and ...
float g_iPosIncr;	// ... position increment (used in display1)

CVec2i g_vecPos;		// same as above but in vector form ...
CVec2i g_vecPosIncr;	// (used in display2)
*/

//------------------------------------------
int r_sun = 60;
int r_earth = 40;
int r_moon = 20;
int margin_earth_moon = 10;
int margin_sun_earth = 75;

float startSun[] = {0, 0};
float startEarth[] = {(startSun[0]+r_sun+r_earth+margin_sun_earth), 0};
float startMoon[] = {(startEarth[0]+r_earth+r_moon+margin_earth_moon), 0};

float startSun3[] = {0, 0, 1};
float startEarth3[] = {(startSun[0]+r_sun+r_earth+margin_sun_earth), 0, 1};
float startMoon3[] = {(startEarth[0]+r_earth+r_moon+margin_earth_moon), 0, 1};

float angleSun = 0.5;
float angleEarth = 0.2;

float angleSunInc = 5;
float angleEarthInc = 1;

CVec2f sun(startSun);
CVec2f earth(startEarth);
CVec2f moon(startMoon);

CVec3f sun3(startSun3);
CVec3f earth3(startEarth3);
CVec3f moon3(startMoon3);

Color c_sun(1, 1, 0);
Color c_earth(0, 0, 1);
Color c_moon(1, 1, 1);
	
Bresenham b(drawPoint);
//
/////////////////////////////////////////////////////////////

// function to initialize our own variables
void init () 
{
	// init timer interval
	g_iTimerMSecs = 10;

	/*
	// init variables for display1
	g_iPos     = 0;
	g_iPosIncr = 2;

	// init variables for display2
	int aiPos    [2] = {0, 0};
	int aiPosIncr[2] = {2, 2};
	g_vecPos.setData (aiPos);
	g_vecPosIncr.setData (aiPosIncr);
	*/ 
}

// function to initialize the view to ortho-projection
void initGL () 
{
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

int min (int a, int b) { return a>b? a: b; }
// timer callback function
void timer (int value) 
{
	///////
	// update your variables here ...
	//
	
	/* don't know what these lines do ?!?

	int size2 = min (g_iWidth, g_iHeight) / 2;

	// variables for display1 ...
	if (g_iPos<=-size2 || g_iPos>=size2){
		g_iPosIncr = -g_iPosIncr;
	} 
	g_iPos += g_iPosIncr;

	// variables for display2 ...
	if (g_vecPos(1)<=-size2 || g_vecPos(1)>=size2) g_vecPosIncr = -g_vecPosIncr; 
	g_vecPos += g_vecPosIncr;
*/
	//
	///////

	// the last two lines should always be
	glutPostRedisplay ();
	glutTimerFunc (g_iTimerMSecs, timer, 0);	// call timer for next iteration
}

// display callback function
void display1 (void) 
{
	glClear (GL_COLOR_BUFFER_BIT);
	///////
	
	//transformation
	earth = Transformation::rotate(earth, angleSun);
	moon = Transformation::rotate(moon, angleSun);

	moon = Transformation::translate(moon, -earth);
	moon = Transformation::rotate(moon, angleEarth);
	moon = Transformation::translate(moon, earth);
	
	
	//draw stuff
	Point pSun(sun(0), sun(1));
	Point pEarth(earth(0), earth(1));
	Point pMoon(moon(0), moon(1));
	
	drawCircle(pSun, r_sun, c_sun);
	drawCircle(pEarth, r_earth, c_earth);
	drawCircle(pMoon, r_moon, c_moon);

	// In double buffer mode the last
	// two lines should alsways be
	glFlush ();
	glutSwapBuffers (); // swap front and back buffer
}

// display callback function
void display2 (void) 
{
	glClear (GL_COLOR_BUFFER_BIT);

	///////

	//transformation
	//*
	earth3 = Transformation::rotateArroundVec(earth3, sun3, angleSun);
	moon3 = Transformation::rotateArroundVec(moon3, sun3, angleSun);
	moon3 = Transformation::rotateArroundVec(moon3, earth3, angleEarth);
	//*/
	/*
	earth3 = rotate(earth3, -angleSun);
	moon3 = rotate(moon3, -angleSun);

	moon3 = translate(moon3, -earth3);
	moon3 = rotate(moon3, -angleEarth);
	moon3 = translate(moon3, earth3);
	*/
	
	//draw stuff
	Point pSun(sun3(0), sun3(1));
	Point pEarth(earth3(0), earth3(1));
	Point pMoon(moon3(0), moon3(1));
	
	drawCircle(pSun, r_sun, c_moon);
	drawCircle(pEarth, r_earth, c_sun);
	drawCircle(pMoon, r_moon, c_earth);

	// In double buffer mode the last
	// two lines should alsways be
	glFlush ();
	glutSwapBuffers (); // swap front and back buffer
}

void keyboard (unsigned char key, int x, int y) 
{
	switch (key) {
		case 'q':
		case 'Q':
			exit (0); // quit program
			break;
		case '1':
			glutDisplayFunc (display1);
			//glutPostRedisplay ();	// not needed since timer triggers redisplay
			break;
		case '2':
			glutDisplayFunc (display2);
			//glutPostRedisplay ();	// not needed since timer triggers redisplay
			break;
		default:
			// do nothing ...
			break;
	};
}

void drawPoint(Point p, Color c){
	glVertex2i(p.x, p.y);
}

void drawLine (Point p1, Point p2, Color c){
	glBegin (GL_POINTS);
	glColor3f (c.r, c.g, c.b);
	
	b.bhamLine(p1, p2, c);
	
	glEnd ();
}

void drawCircle(Point p, int r, Color c){
	glBegin (GL_POINTS);
	glColor3f (c.r, c.g, c.b);
	
	b.bhamCircle(p, r, c);
	
	glEnd ();
}


int main (int argc, char **argv) 
{
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
	glutTimerFunc (10, timer, 0);
	glutKeyboardFunc (keyboard);
	glutDisplayFunc (display1);
	// you might want to add a resize function analog to
	// Übung1 using code similar to the initGL function ...

	// start main loop
	glutMainLoop ();

	return 0;
}
