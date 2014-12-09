#include "View.h"

View::View(CVec4f eyePoint, CVec4f viewZ, CVec4f viewY){
	this->eyePoint = eyePoint;
	setViewZ(viewZ);
	setViewY(viewY);
	setFocus(-eyePoint(2));
}

View::~View(){
	
}

void View::setEyePoint(CVec4f v){
	v(3) = 1;
	this->eyePoint = v;
}

void View::setViewZ(CVec4f v){
	v(3) = 1;
	this->viewZ = v;
}

void View::setViewY(CVec4f v){
	v(3) = 1;
	this->viewY = v;
}
		
CVec4f View::getEyePoint(){
	return this->eyePoint;
}

CVec4f View::getViewZ(){
	return this->viewZ;
}

CVec4f View::getViewY(){
	return this->viewY;
}

CVec4f View::getViewX(){
	CVec4f x = this->viewZ.crossProduct3D(this->viewY);
	x(3) = 1;
	return x;
}

void View::setFocus(float fFocus){
	this->fFocus = fFocus;
}

float View::getFocus(){
	return this->fFocus;
}
