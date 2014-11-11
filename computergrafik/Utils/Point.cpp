#include "Point.hpp"

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

void Point::print(){
	std::cout << "(" << x << "/" << y << ")";
}

