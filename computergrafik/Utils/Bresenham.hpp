#ifndef BRESENHAM_H
#define BRESENHAM_H

#include "Point.hpp"
#include "Color.hpp"

class Bresenham{
private:
	void (*drawPoint)(Point p, Color c);
	void setMirroredPoint(Point center, Point p, Color c);
	
public:
	Bresenham(void (*drawPoint)(Point p, Color c));
	//
	// ÜBUNG 1 AUFGABE 1:
	//
	// Diese Funktion soll eine Gerade zwischen den Punkten
	// p1 und p2 in der Farbe c malen. Benutzen Sie die Funktion
	// setPoint um die individuellen Punkte zu zeichnen.
	void bhamLine(Point p1, Point p2, Color c);
	
	//
	// ÜBUNG 1 AUFGABE 2:
	//
	// Diese Funktion soll einen Kreis mit Radius r um den Punkt p
	// malen. Benutzen Sie die Funktion setPoint um die individuellen
	// Punkte zu zeichnen. Vergessen Sie nicht auch den Mittelpunkt zu
	// zeichnen!
	void bhamCircle(Point p, int r, Color c);
};

#endif // BRESENHAM_H
