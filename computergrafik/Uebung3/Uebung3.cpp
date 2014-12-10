// Sample code for Übung 2
#include <stdio.h>
#include <iostream>

using namespace std;

#include <Projection.h>
#include <Transformation.h>
#include <View.h>
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
void drawCuboid(Cuboid *cuboid, float fFocus);
void drawXYAxis(Color c, int width, int height, int meassurement);

CVec4f translateToOriginAndRotate(CVec4f vP, float degree, CMat4f (*getRotMat)(CVec4f v, float f));
void rotateWorldAxis(float degree, CMat4f (*getRotMat)(CVec4f v, float f));
void rotateCameraAxis(float degree, CMat4f (*getRotMat)(CVec4f v, float f));
void moveCamera(View* view, CVec4f vT);

void display1();

Point convertToPoint(CVec4f vec);

// window width and height (choose an appropriate size)
int g_iWidth  = 800;
int g_iHeight = 800;

//
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// private, global variables ... replace by your own ones
//
// some global state variables used to describe ...
//------------------------------------------
	

float fFocus;
const float F_FOCUS_STEP = 10;
const float F_FOCUS_INITIAL = -200;
const float ROTATION_STEP = 5;
const float MOVE_STEP = 5;
const int AMOUNT_CUBOIDS = 4;


Bresenham b(drawPoint);

Cuboid *cuboids[AMOUNT_CUBOIDS];

View *view;
//
/////////////////////////////////////////////////////////////

// function to initialize our own variables
void init () {	
	view = new View(F_FOCUS_INITIAL);
		
	//init cuboids
	//x,y,z,height,length,depth,color
	Color c(2.4f, 0.1f, 0.1f);
	cuboids[0] = new Cuboid(50, 50, -50, 200, 200, 50, c);
	
	c.set(0.1f, 2.4f, 0.1f);
	cuboids[1] = new Cuboid(-80, -150, -50, 50, 50 , 10, c);
	
	c.set(0.1f, 0.1f, 2.4f);
	cuboids[2] = new Cuboid(-200, 50, -50, 50, 100, 100, c);
	
	c.set(0.1f, 2.1f, 2.4f);
	cuboids[3] = new Cuboid(-50, -50, -25, 100, 50, 50, c);
}

void destroy(){
	for(int i=0; i<AMOUNT_CUBOIDS; i++){
		delete cuboids[i];
	}
	delete view;
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

CVec4f translateToOriginAndRotate(CVec4f vP, float degree, CMat4f (*getRotMat)(CVec4f v, float f)){
	CMat4f mat = Transformation::get3DTransMat(vP, -vP) * getRotMat(vP, degree) * Transformation::get3DTransMat(vP, vP);
	return mat * vP;	
}

void rotateWorldAxis(float degree, CMat4f (*getRotMat)(CVec4f v, float f)){
	//=rotate eyePoint and cameraAxis
	view->setEyePoint(translateToOriginAndRotate(view->getEyePoint(), degree, getRotMat));
	
	rotateCameraAxis(degree, getRotMat);
}

void rotateCameraAxis(float degree, CMat4f (*getRotMat)(CVec4f v, float f)){
	view->setViewY(translateToOriginAndRotate(view->getViewY(), degree, getRotMat));
	view->setViewZ(translateToOriginAndRotate(view->getViewZ(), degree, getRotMat));

	//view->getEyePoint().print(); cout << endl;
}

void moveCamera(View* view, CVec4f vT){
	view->setEyePoint(Transformation::translate3D(view->getEyePoint(), vT));
}

void keyboard (unsigned char key, int x, int y) {
	switch (key) {
		case 'q':
		case 'Q':
			exit (0); // quit program
			break;
		case 'f':
			view->setFocus(view->getFocus() - F_FOCUS_STEP);
			break;
		case 'F':
			view->setFocus(view->getFocus() + F_FOCUS_STEP);
			break;
		case 'r':
		case 'R':
			destroy();
			init();
			break;
		case 'x':
			rotateWorldAxis(-ROTATION_STEP, &Transformation::get3DRotMatXAxis);
			break;
		case 'X':
			rotateWorldAxis(ROTATION_STEP, &Transformation::get3DRotMatXAxis);
			break;
		case 'y':
			rotateWorldAxis(-ROTATION_STEP, &Transformation::get3DRotMatYAxis);
			break;
		case 'Y':
			rotateWorldAxis(ROTATION_STEP, &Transformation::get3DRotMatYAxis);
			break;
		case 'z':
			rotateWorldAxis(-ROTATION_STEP, &Transformation::get3DRotMatZAxis);
			break;
		case 'Z':
			rotateWorldAxis(ROTATION_STEP, &Transformation::get3DRotMatZAxis);
			break;
		case 'a':
			rotateCameraAxis(-ROTATION_STEP, &Transformation::get3DRotMatXAxis);
			break;
		case 'A':
			rotateCameraAxis(ROTATION_STEP, &Transformation::get3DRotMatXAxis);
			break;
		case 'b':
			rotateCameraAxis(-ROTATION_STEP, &Transformation::get3DRotMatYAxis);
			break;
		case 'B':
			rotateCameraAxis(ROTATION_STEP, &Transformation::get3DRotMatYAxis);
			break;
		case 'c':
			rotateCameraAxis(-ROTATION_STEP, &Transformation::get3DRotMatZAxis);
			break;
		case 'C':
			rotateCameraAxis(ROTATION_STEP, &Transformation::get3DRotMatZAxis);
			break;
		case 'u':
			{
				CVec4f vT;
				vT(0) = -MOVE_STEP;
				moveCamera(view, vT);
			}
			break;
		case 'U':
			{
				CVec4f vT;
				vT(0) = MOVE_STEP;
				moveCamera(view, vT);
			}
			break;
		case 'v':
			{
				CVec4f vT;
				vT(1) = -MOVE_STEP;
				moveCamera(view, vT);
			}
			break;
		case 'V':
			{
				CVec4f vT;
				vT(1) = MOVE_STEP;
				moveCamera(view, vT);
			}
			break;
		case 'w':
			{
				CVec4f vT;
				vT(2) = -MOVE_STEP;
				moveCamera(view, vT);
			}
			break;
		case 'W':
			{
				CVec4f vT;
				vT(2) = MOVE_STEP;
				moveCamera(view, vT);
			}
			break;
		default:
			// do nothing ...
			break;
	};
	glutPostRedisplay();
}

// display callback function
void display1 (void) {
	glClear (GL_COLOR_BUFFER_BIT);
	///////
	float fFocus = view->getFocus();
	
	//draw stuff
	Color c(0.0f, 255.0f, 0.0f);
	drawXYAxis(c, g_iWidth, g_iHeight, 10);
	
	for(int i=0; i<AMOUNT_CUBOIDS; i++){
		drawCuboid(cuboids[i], fFocus);
	}
	
	// In double buffer mode the last
	// two lines should alsways be
	glFlush ();
	glutSwapBuffers (); // swap front and back buffer
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

void drawCuboid(Cuboid *cuboid, float fFocus){
	cuboid->printPoints();
	CMat4f inv_mat = Transformation::getWorldToViewTransMat(view);
	Cuboid* projectedCuboid = Projection::projektZallg(inv_mat, fFocus, cuboid);
	//Cuboid* projectedCuboid = Projection::projektZ(fFocus, cuboid);
	Color c = cuboid->getColor();
	
	projectedCuboid->printPoints();
	
	glBegin(GL_POINTS);
	glColor3f(c.r, c.g, c.b);
	
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
	glutCreateWindow ("Uebung 3");

	init ();	// init my variables first
	initGL ();	// init the GL (i.e. view settings, ...)

	// assign callbacks
	glutKeyboardFunc (keyboard);
	glutDisplayFunc (display1);
	// you might want to add a resize function analog to
	// Übung1 using code similar to the initGL function ...

	// start main loop
	display1();
	glutPostRedisplay ();
	glutMainLoop ();
	
	destroy(); // free stuff
	
	return 0;
}
