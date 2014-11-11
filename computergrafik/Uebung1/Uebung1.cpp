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

#include <Point.hpp>
#include <Color.hpp>
#include <Bresenham.hpp>

// Include-File für die GLUT-Library
#include <GL/glut.h>



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

	Bresenham b(setPoint);
	//draw axis of coordinates
	Point x_axis_1(-29, 0);		
	Point x_axis_2(29, 0);	
	Point y_axis_1(0, -29);
	Point y_axis_2(0, 29);

	Color axis_color(0,0,0);
	b.bhamLine (x_axis_1, x_axis_2, axis_color);
	b.bhamLine (y_axis_1, y_axis_2, axis_color);

	Point p1(-10, 20);		// ersten Punkt für Gerade definieren
	Point p2(20, -15);		// ebenso den zweiten Punkt
	Color cl(1,0,0);		// es soll eine rote Gerade sein ...

	b.bhamLine (p2, p1, cl);	// Gerade zeichnen ...
	

	Point p(-3, -5);		// Mittelpunkt für Kreis definieren
	int r = 17;				// Radius festlegen
	Color cc(0,0,1);		// es soll ein blauer Kreis sein ...

	b.bhamCircle (p, r, cc);	// Kreis zeichnen ...

	/*
	Color c_test(0,1,0);
	
	b.bhamLine(Point(29,-r+p.y), Point(-29, -r+p.y), c_test);
	b.bhamLine(Point(29, r+p.y), Point(-29, r+p.y), c_test);
	b.bhamLine(Point(r+p.x, 29), Point(r+p.x, -29), c_test);
	b.bhamLine(Point(-r+p.x,29), Point(-r+p.x, -29), c_test);
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
