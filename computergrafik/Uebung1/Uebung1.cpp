///////////////////////////////////////////////////////////////////////
//										                             //
// Codegerüst für Vorlesung Computergraphik WS 2011/12 Übung 1       //
//										                             //
///////////////////////////////////////////////////////////////////////


// Include-File für die Text Ein-/Ausgabe
//#include "stdafx.h"
#include <stdio.h>
#include <iostream>
using namespace std;

// Include-File für die GLUT-Library
#include "GL/glut.h"



/////////////////////////////////////////////////////////////////////////////////////////
//
// Hier wird einiges initialisiert. Sie dürfen sich gerne den Code anschauen und
// versuchen ihn zu verstehen. Das sollte Ihnen nicht allzu schwer fallen. Es werden
// jedoch einige Techniken benutzt (Texturen, ...) die wir in der Vorlesung noch
// nicht besprochen haben, die wir aber aus techn. Gründen hier benötigen.
//
// Weiter unten finden Sie einen Vermerk, ab dem Sie den Code jedoch vollständig
// verstehen sollten!!!


// Auflösungen der gesamten Textur
// !!!ACHTUNG!!! nicht alle Texturauflösungen funktionieren!
// Stichwort ungefähr: POT2 Problematik
#define TEX_RES_X 60
#define TEX_RES_Y 60
// Anzahl der Pixel der Textur
#define TEX_RES TEX_RES_X*TEX_RES_Y
// Achsenlänge der Textur (Achsen sind asymmetrisch von -TexRes#/2 bis TesRes#/2-1)
#define TEX_HALF_X TEX_RES_X/2
#define TEX_HALF_Y TEX_RES_Y/2
// Konvertiert Indices von (x,y) Koordinaten in ein lineares Array
#define TO_LINEAR(x, y) (((x)) + TEX_RES_X*((y)))

// globaler Speicher für Texturdaten
char g_Buffer[3*TEX_RES];
// Textur ID Name
GLuint g_TexID = 0;

// Auflösung des Hauptfensters (kann sich durch User ändern)
int g_WinWidth = 800;
int g_WinHeight = 800;

// Funktion organisiert die Textur.
// Kümmern Sie sich nicht weiter um diese Funktion, da
// sie momentan nur ein notwendiges Übel darstellt!
void manageTexture () {

	glEnable (GL_TEXTURE_2D);

	if (g_TexID==0)	glGenTextures (1, &g_TexID);

	glBindTexture (GL_TEXTURE_2D, g_TexID);

	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, TEX_RES_X, TEX_RES_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, g_Buffer);
	
	glBindTexture (GL_TEXTURE_2D, 0);

	glDisable (GL_TEXTURE_2D);
}

// Callback Funktion um die Fenstergrößen anzupassen.
// Auch diese Funktion ist ein notwendiges Übel! Kümmern
// Sie sich im Moment nicht weiter darum.
void reshape(int w, int h) {

	g_WinWidth = w;
	g_WinHeight = h;

	glViewport(0, 0, w, h);					// Establish viewing area to cover entire window.

	glMatrixMode(GL_PROJECTION);			// Start modifying the projection matrix.
	glLoadIdentity();						// Reset project matrix.
	glOrtho(-w/2, w/2, -h/2, h/2, 0, 1);	// Map abstract coords directly to window coords.

	glutPostRedisplay ();
}




//
//
/////////////////////////////////////////////////////////////////////////////////////////
//
// Hier fängt der für Sie wirklich relevante Teil des Programms an.
//




// Eine überaus primitive Punktklasse
class Point {
public:

	Point (int x=0, int y=0) {
		this->x = x;
		this->y = y;
	}

	void swapXY(){
		int tmp = x;
		x = y;
		y = tmp;
	}

	void print(){
		cout << "(" << x << "/" << y << ")";
	}

	int x, y;
};

// Eine überaus primitive Farbklasse
class Color {
public:

	Color (float r=1.0f, float g=1.0f, float b=1.0f) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	float r, g, b;
};

// Funktion löscht den Bildschirm mit der angegebenen Farbe
// Usage z.B.: clearImage (Color (1,1,1))
// löscht den Bildschirm in Weiß.
// Ohne Farbangabe ist der Standard Weiß
void clearImage (Color c=Color()) {
	for (int i=0; i<TEX_RES; i++) {
		g_Buffer[3*i  ] = 255.0*c.r;
		g_Buffer[3*i+1] = 255.0*c.g;
		g_Buffer[3*i+2] = 255.0*c.b;
	}
}

// Funktion malt einen Punkt an die angegebenen Koordinaten
// Usage z.B.: setPoint (Point(10, 5), Color (1,0,0))
// malt einen Punkt an die Koordinate (10, 5)
// Ohne Farbangabe ist die standard Malfarbe Schwarz
//
// Nutzen Sie diese Funktion ...
void setPoint (Point p, Color c=Color(0,0,0)) {
	int x = p.x + TEX_HALF_X;
	int y = p.y + TEX_HALF_Y;
	if (x < 0 || y < 0 || x >= TEX_RES_X || y >= TEX_RES_Y) {
		cerr << "Illegal point co-ordinates (" << p.x << ", " << p.y << ")\n" << flush;
		return;
	}

	g_Buffer[3*TO_LINEAR (x, y)  ] = 255.0*c.r;
	g_Buffer[3*TO_LINEAR (x, y)+1] = 255.0*c.g;
	g_Buffer[3*TO_LINEAR (x, y)+2] = 255.0*c.b;
}

void setMirroredPoint(Point center, Point p, Color c){
	int x = p.x;
	int y = p.y;

	int delta_x = x - center.x;
	int delta_y = y - center.y;

	// Octant: 2,3,6,7
	setPoint(Point(x, y), c);
	setPoint(Point(center.x - delta_x, y), c);
	setPoint(Point(center.x - delta_x, center.y - delta_y), c);
	setPoint(Point(x, center.y - delta_y), c);

	// Octant: 1,4,5,8
	setPoint(Point(center.x + delta_y, center.y + delta_x), c);
	setPoint(Point(center.x + delta_y, center.y - delta_x), c);
	setPoint(Point(center.x - delta_y, center.y + delta_x), c);
	setPoint(Point(center.x - delta_y, center.y - delta_x), c);
}

//
// ÜBUNG 1 AUFGABE 1:
//
// Diese Funktion soll eine Gerade zwischen den Punkten
// p1 und p2 in der Farbe c malen. Benutzen Sie die Funktion
// setPoint um die individuellen Punkte zu zeichnen.
void bhamLine (Point p1, Point p2, Color c) {
	bool xy_swapped = false;
	bool x_inverted = false;
	bool y_inverted = false;

	Point origin(0,0);

	//draw start-/endpoint
	setPoint(p1, c);
	setPoint(p2, c);
	
	//set p1 as origin -> move p2 accordingly
	p2.x -= p1.x;
	p2.y -= p1.y;
	
	//invert x if negativ
	if( p2.x < 0 ){
		x_inverted = true;
		p2.x = -p2.x;
	}
	//invert y if negativ
	if( p2.y < 0 ){
		y_inverted = true;
		p2.y = -p2.y;
	}
	//swapp x and y if m > 1
	if( p2.x < p2.y ){
		xy_swapped = true;
		int tmp = p2.x;
		p2.x = p2.y;
		p2.y = tmp;
	}

	int x = origin.x;
	int y = origin.y;

	int delta_x = p2.x -  origin.x;
	int delta_y = p2.y - origin.y;
	
	int delta_ne = 2 * (delta_y - delta_x);
	int delta_e = 2 * delta_y;

	int d = 2 * delta_y - delta_x;

	Point tmpP;

	while( x < p2.x ){
		x++;
		if( d > 0 ) {
			//NE is next point
			d += delta_ne;
			y++;
		}else{
			//E is next point
			d += delta_e;
		}

		tmpP = Point(x, y);

		//revert all changes made in inverted order
		if( xy_swapped ) {
			int tmp = tmpP.x;
			tmpP.x = tmpP.y;
			tmpP.y = tmp;
		}
		if( y_inverted ){
			tmpP.y = -tmpP.y;
		}
		if( x_inverted ){
			tmpP.x = -tmpP.x;
		}
		
		tmpP.x += p1.x;
		tmpP.y += p1.y;

		//draw point
		setPoint(tmpP, c);
	}
}

//
// ÜBUNG 1 AUFGABE 2:
//
// Diese Funktion soll einen Kreis mit Radius r um den Punkt p
// malen. Benutzen Sie die Funktion setPoint um die individuellen
// Punkte zu zeichnen. Vergessen Sie nicht auch den Mittelpunkt zu
// zeichnen!
void bhamCircle (Point p, int r, Color c) {
	int x = 0;
	int y = r;

	int delta_x = p.x;
	int delta_y = p.y;

	int d = 5 - 4 * r;
	int delta_e, delta_se;

	// Mittelpunkt
	setPoint (p, c);

	setMirroredPoint(p, Point(x+delta_x,y+delta_y), c);

	while ( y > x ){
		x++;
		cout << d << endl;
		if( d < 0 ){
			//E is next point
			delta_e = 4 * (2 * x + 3);
			d += delta_e;
		}else{
			//SE is next point
			delta_se = 4 * (2 * (x - y) + 5);
			d += delta_se;
			y--;
		}
		setMirroredPoint(p, Point(x+delta_x,y+delta_y), c);
	}
}

// Die Callback Funktion die für das eigentliche Malen
// zuständig ist. Im Wesentlichen brauchen Sie sich nur
// um den Bereich zwischen den Kommentaren zu kümmern,
// alles andere ist wiederum ein notwendiges Übel!
void display (void) {

	//////////////////////////////////////////////////////////////////
	//
	// Hier sollen Ihre Bresenham-Funktionen
	// eine Gerade und einen Kreis zeichnen.
	//
	// Im Prinzip brauchen Sie hier keine
	// großartigen Änderungen vorzunehmen, es
	// sei denn Sie wollen "spielen" :-D
	//

	clearImage ();			// altes Bild löschen

	//draw axis of coordinates
	Point x_axis_1(-29, 0);		
	Point x_axis_2(29, 0);	
	Point y_axis_1(0, -29);
	Point y_axis_2(0, 29);

	Color axis_color(0,0,0);
	bhamLine (x_axis_1, x_axis_2, axis_color);
	bhamLine (y_axis_1, y_axis_2, axis_color);

	Point p1(-10, 20);		// ersten Punkt für Gerade definieren
	Point p2(20, -15);		// ebenso den zweiten Punkt
	Color cl(1,0,0);		// es soll eine rote Gerade sein ...

	bhamLine (p2, p1, cl);	// Gerade zeichnen ...
	

	Point p(-3, -5);		// Mittelpunkt für Kreis definieren
	int r = 17;				// Radius festlegen
	Color cc(0,0,1);		// es soll ein blauer Kreis sein ...

	bhamCircle (p, r, cc);	// Kreis zeichnen ...

	/*
	Color c_test(0,1,0);
	
	bhamLine (Point(29,-r+p.y), Point(-29, -r+p.y), c_test);
	bhamLine (Point(29, r+p.y), Point(-29, r+p.y), c_test);
	bhamLine (Point(r+p.x, 29), Point(r+p.x, -29), c_test);
	bhamLine (Point(-r+p.x,29), Point(-r+p.x, -29), c_test);
	*/

	//
	// Ab hier sollten Sie nichts mehr ändern!
	//
	//////////////////////////////////////////////////////////////////

	manageTexture ();

	glClear (GL_COLOR_BUFFER_BIT);
	glBindTexture (GL_TEXTURE_2D, g_TexID);
	
	glEnable (GL_TEXTURE_2D);
	glBegin (GL_QUADS);
		glColor3f (1, 0, 0);
		glTexCoord2f (0, 0);
		glVertex2f (-g_WinWidth/2, -g_WinHeight/2);
		glTexCoord2f (1, 0);
		glVertex2f (g_WinWidth/2, -g_WinHeight/2);
		glTexCoord2f (1, 1);
		glVertex2f (g_WinWidth/2, g_WinHeight/2);
		glTexCoord2f (0, 1);
		glVertex2f (-g_WinWidth/2, g_WinHeight/2);
	glEnd ();

	glBindTexture (GL_TEXTURE_2D, 0);
	glDisable (GL_TEXTURE_2D);

	glFlush ();
}

// Die Main-Funktion
int main (int argc, char **argv) {

	glutInit (&argc, argv);
	glutInitWindowSize (g_WinWidth, g_WinHeight);
	glutCreateWindow ("Uebung 1: Bresenham");

	glutReshapeFunc (reshape);	// zuständig für Größenänderungen des Fensters
	glutDisplayFunc (display);	// zuständig für das wiederholte Neuzeichnen des Bildschirms

	glutMainLoop ();

	glDeleteTextures (1, &g_TexID); // löscht die oben angelegte Textur

	return 0;
}
