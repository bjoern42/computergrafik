#include "Bresenham.hpp"

Bresenham::Bresenham(void (*drawPoint)(Point p, Color c)){
	this->drawPoint = drawPoint;
}

void Bresenham::setMirroredPoint(Point center, Point p, Color c){
	int x = p.x;
	int y = p.y;

	int delta_x = x - center.x;
	int delta_y = y - center.y;

	// Octant: 2,3,6,7
	drawPoint(Point(x, y), c);
	drawPoint(Point(center.x - delta_x, y), c);
	drawPoint(Point(center.x - delta_x, center.y - delta_y), c);
	drawPoint(Point(x, center.y - delta_y), c);

	// Octant: 1,4,5,8
	drawPoint(Point(center.x + delta_y, center.y + delta_x), c);
	drawPoint(Point(center.x + delta_y, center.y - delta_x), c);
	drawPoint(Point(center.x - delta_y, center.y + delta_x), c);
	drawPoint(Point(center.x - delta_y, center.y - delta_x), c);
}

//
// ÜBUNG 1 AUFGABE 1:
//
// Diese Funktion soll eine Gerade zwischen den Punkten
// p1 und p2 in der Farbe c malen. Benutzen Sie die Funktion
// setPoint um die individuellen Punkte zu zeichnen.
void Bresenham::bhamLine (Point p1, Point p2, Color c) {
	bool xy_swapped = false;
	bool x_inverted = false;
	bool y_inverted = false;

	Point origin(0,0);

	//draw start-/endpoint
	drawPoint(p1, c);
	drawPoint(p2, c);
	
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
		drawPoint(tmpP, c);
	}
}

//
// ÜBUNG 1 AUFGABE 2:
//
// Diese Funktion soll einen Kreis mit Radius r um den Punkt p
// malen. Benutzen Sie die Funktion setPoint um die individuellen
// Punkte zu zeichnen. Vergessen Sie nicht auch den Mittelpunkt zu
// zeichnen!
void Bresenham::bhamCircle (Point p, int r, Color c) {
	int x = 0;
	int y = r;

	int delta_x = p.x;
	int delta_y = p.y;

	int d = 5 - 4 * r;
	int delta_e, delta_se;

	// Mittelpunkt
	drawPoint (p, c);

	setMirroredPoint(p, Point(x+delta_x,y+delta_y), c);

	while ( y > x ){
		x++;
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

