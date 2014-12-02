#include "Cuboid.h"

Cuboid::Cuboid(CVec4f origin, float height, float length, float depth){
	float tmp[4];
	this->points = new CVec4f[8];
	this->height = height;
	this->length = length;
	this->depth = depth;
	
	//front bottom left
	origin.getData(tmp);
	this->points[0] = origin;
	
	//front bottom right
	tmp[0] += length;
	this->points[1] = CVec4f(tmp);
	
	//front top left
	origin.getData(tmp);
	tmp[1] += height;
	this->points[2] = CVec4f(tmp);
	
	//front top right
	origin.getData(tmp);
	tmp[0] += length;
	tmp[1] += height;
	this->points[3] = CVec4f(tmp);
	
	//back bottom left
	origin.getData(tmp);
	tmp[2] -= depth;
	this->points[4] = CVec4f(tmp);
	
	//back bottom right
	origin.getData(tmp);
	tmp[2] -= depth;
	tmp[0] += length;
	this->points[5] = CVec4f(tmp);
	
	//back top left
	origin.getData(tmp);
	tmp[2] -= depth;
	tmp[1] += height;
	this->points[6] = CVec4f(tmp);
	
	//back top right
	origin.getData(tmp);
	tmp[2] -= depth;
	tmp[1] += height;
	tmp[0] += length;
	this->points[7] = CVec4f(tmp);
}

Cuboid::~Cuboid(){
	delete [] points;
}

CVec4f* Cuboid::getPoints(){
	return points;
}

CVec4f Cuboid::getFrontBottomLeft(){
	return this->points[0];
}
CVec4f Cuboid::getFrontBottomRight(){
	return this->points[1];
}
CVec4f Cuboid::getFrontTopLeft(){
	return this->points[2];
}
CVec4f Cuboid::getFrontTopRight(){
	return this->points[3];
}
CVec4f Cuboid::getBackBottomLeft(){
	return this->points[4];
}
CVec4f Cuboid::getBackBottomRight(){
	return this->points[5];
}
CVec4f Cuboid::getBackTopLeft(){
	return this->points[6];
}
CVec4f Cuboid::getBackTopRight(){
	return this->points[7];
}
		
float Cuboid::getHeight(){
	return this->height;
}
float Cuboid::getLength(){
	return this->length;
}
float Cuboid::getDepth(){
	return this->depth;
}


