// Sample code for Übung 2
#include <stdio.h>
#include <iostream>
#include <math.h> 
using namespace std;

#include "vec.h"
#include "mat.h"
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
float g_iPos;		// ... position and ...
float g_iPosIncr;	// ... position increment (used in display1)

CVec2i g_vecPos;		// same as above but in vector form ...
CVec2i g_vecPosIncr;	// (used in display2)


//------------------------------------------
int r_sun = 60;
int r_earth = 40;
int r_moon = 20;
int margin_earth_moon = 10;
int margin_sun_earth = 75;

float startSun[] = {0,0};
float startEarth[] = {(startSun[0]+r_sun+r_earth+margin_sun_earth), 0};
float startMoon[] = {(startEarth[0]+r_earth+r_moon+margin_earth_moon), 0};

float angleSun = 0.5;
float angleEarth = 0.2;

float angleSunInc = 5;
float angleEarthInc = 1;

CVec2f sun(startSun);
CVec2f earth(startEarth);
CVec2f moon(startMoon);

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

	// init variables for display1
	g_iPos     = 0;
	g_iPosIncr = 2;

	// init variables for display2
	int aiPos    [2] = {0, 0};
	int aiPosIncr[2] = {2, 2};
	g_vecPos.setData (aiPos);
	g_vecPosIncr.setData (aiPosIncr);
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

// Callback Funktion um die Fenstergrößen anzupassen.
// Auch diese Funktion ist ein notwendiges Übel! Kümmern
// Sie sich im Moment nicht weiter darum.
void reshape(int w, int h) {

	g_iWidth = w;
	g_iHeight = h;

	glViewport(0, 0, w, h);					// Establish viewing area to cover entire window.

	glMatrixMode(GL_PROJECTION);			// Start modifying the projection matrix.
	glLoadIdentity();						// Reset project matrix.
	glOrtho(-w/2, w/2, -h/2, h/2, 0, 1);	// Map abstract coords directly to window coords.

	glutPostRedisplay ();
}

int min (int a, int b) { return a>b? a: b; }
// timer callback function
void timer (int value) 
{
	///////
	// update your variables here ...
	//

	int size2 = min (g_iWidth, g_iHeight) / 2;

	// variables for display1 ...
	if (g_iPos<=-size2 || g_iPos>=size2){
		g_iPosIncr = -g_iPosIncr;
	} 
	g_iPos += g_iPosIncr;

	// variables for display2 ...
	if (g_vecPos(1)<=-size2 || g_vecPos(1)>=size2) g_vecPosIncr = -g_vecPosIncr; 
	g_vecPos += g_vecPosIncr;

	//
	///////

	// the last two lines should always be
	glutPostRedisplay ();
	glutTimerFunc (g_iTimerMSecs, timer, 0);	// call timer for next iteration
}

CVec2f rotate(CVec2f p, float degree){
	float degree_rad = degree * M_PI / 180;
	float r_cos = cos(degree_rad);
	float r_sin = sin(degree_rad);
	
	float r_Array[2][2];
	r_Array[0][0] = r_cos;
	r_Array[0][1] = r_sin;
	r_Array[1][0] = -r_sin;
	r_Array[1][1] = r_cos;
	
	CMat2f r(r_Array);
	
	return r*p;
}

CVec3f translate(CVec3f vP, CVec3f vT){
	float t_Array[3][3];
	t_Array[0][0] = 1;
	t_Array[1][0] = 0;
	t_Array[2][0] = 0;
	t_Array[0][1] = 0;
	t_Array[1][1] = 1;
	t_Array[2][1] = 0;
	t_Array[0][2] = vT(0);
	t_Array[1][2] = vT(1);
	t_Array[2][2] = 1;
	
	CMat3f t(t_Array);
	
	return t*vP;
}

CVec2f translate(CVec2f vP, CVec2f vT){	
	float p_Array[3];
	p_Array[0] = vP(0);
	p_Array[1] = vP(1);
	p_Array[2] = 1;
	
	CVec3f p(p_Array);
	
	float t_Array[3][3];
	t_Array[0][0] = 1;
	t_Array[1][0] = 0;
	t_Array[2][0] = 0;
	t_Array[0][1] = 0;
	t_Array[1][1] = 1;
	t_Array[2][1] = 0;
	t_Array[0][2] = vT(0);
	t_Array[1][2] = vT(1);
	t_Array[2][2] = 1;
	
	CMat3f t(t_Array);
	
	CVec3f tmp = t*p;
	
	float data_p[2];
	tmp.getData(data_p);

	CVec2f ret(data_p);
	return ret;
} 

// display callback function
void display1 (void) 
{
	glClear (GL_COLOR_BUFFER_BIT);
	///////
	
	earth = rotate(earth, angleSun);
	moon = rotate(moon, angleSun);

	moon = translate(moon, -earth);
	moon = rotate(moon, angleEarth);
	moon = translate(moon, earth);
	
	float tmp[2];
	sun.getData(tmp);
	Point pSun(tmp[0], tmp[1]);
	earth.getData(tmp);
	Point pEarth(tmp[0], tmp[1]);
	moon.getData(tmp);
	Point pMoon(tmp[0], tmp[1]);
	
	drawCircle(pSun, r_sun, c_sun);
	drawCircle(pEarth, r_earth, c_earth);
	drawCircle(pMoon, r_moon, c_moon);
	
	// display your data here ...
	
	//exit(0);

	/*
	glBegin (GL_TRIANGLES);
		glColor3f (1,0,0);
		glVertex2i (g_iPos, 0);
		glColor3f (0,1,0);
		glVertex2i (-g_iPos, g_iPos);
		glColor3f (0,0,1);
		glVertex2i (-g_iPos, -g_iPos);
	glEnd ();
	*/
	//
	///////

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
	// display your data here ...
	//

	glBegin (GL_QUADS);
		glColor3f (1,0,0);
		glVertex2i (-g_vecPos(1), -g_vecPos(2));
		glColor3f (0,1,0);
		glVertex2i (g_vecPos(1), -g_vecPos(2));
		glColor3f (0,0,1);
		glVertex2i (g_vecPos(1), g_vecPos(2));
		glColor3f (1,1,0);
		glVertex2i (-g_vecPos(1), g_vecPos(2));
	glEnd ();

	//
	///////

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
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize (g_iWidth, g_iHeight);
	glutCreateWindow ("Uebung 2");

	init ();	// init my variables first
	initGL ();	// init the GL (i.e. view settings, ...)

	// assign callbacks
	glutTimerFunc (10, timer, 0);
	glutKeyboardFunc (keyboard);
	glutDisplayFunc (display1);
	//glutReshapeFunc (reshape);	// zuständig für Größenänderungen des Fensters
	// you might want to add a resize function analog to
	// Übung1 using code similar to the initGL function ...

	// start main loop
	glutMainLoop ();

	return 0;
}
