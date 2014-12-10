#include "View.h"

View::View(float fFocus){
	float tmp[4];
	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = 0;
	//Bei Punkten muss homogenisierende (=[3]) 1 sein!
	tmp[3] = 1;
	CVec4f eyePoint(tmp);
	
	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = -1;
	//Bei Vektoren muss homogenisierende (=[3]) 0 sein!
	tmp[3] = 0;
	CVec4f viewZ(tmp);
	
	tmp[0] = 0;
	tmp[1] = 1;
	tmp[2] = 0;
	//Bei Vektoren muss homogenisierende (=[3]) 0 sein!
	tmp[3] = 0;
	CVec4f viewY(tmp);
	
	init(eyePoint, viewZ, viewY, fFocus);
}

View::View(CVec4f eyePoint, CVec4f viewZ, CVec4f viewY, float fFocus){
	init(eyePoint, viewZ, viewY, fFocus);
}

View::~View(){}

void View::setEyePoint(CVec4f v){
	this->eyePoint = v;
}

void View::setViewZ(CVec4f v){
	this->viewZ = v;
}

void View::setViewY(CVec4f v){
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
	return x;
}

void View::setFocus(float fFocus){
	this->fFocus = fFocus;
}

float View::getFocus(){
	return this->fFocus;
}

//private methods
void View::init(CVec4f eyePoint, CVec4f viewZ, CVec4f viewY, float fFocus){
	setEyePoint(eyePoint);
	setViewZ(viewZ);
	setViewY(viewY);
	setFocus(fFocus);
}
