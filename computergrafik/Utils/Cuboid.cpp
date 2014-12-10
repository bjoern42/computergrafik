#include "Cuboid.h"

//constructors
Cuboid::Cuboid(CVec4f points[8], Color color){
	int i;
	setColor(color);
	this->height = -1;
	this->length = -1;
	this->depth = -1;
	this->points = new CVec4f[8];
	for(i=0; i<8; i++){
		this->points[i] = points[i];
	}
}

Cuboid::Cuboid(float x, float y, float z, float length, float height, float depth, Color color){
	float originData[4];
	originData[0] = x;
	originData[1] = y;
	originData[2] = z;
	originData[3] = 1;
	CVec4f origin(originData);
	
	init(origin, length, height, depth, color);
}

Cuboid::Cuboid(CVec4f origin, float length, float height, float depth, Color color){
	init(origin, length, height, depth, color);
}

Cuboid::~Cuboid(){
	delete [] points;
}

//public methods
void Cuboid::printPoints(){
	std::cout << "cuboid points: {" << std::endl;
	for(int i=0; i<8; i++){
		std::cout << "\t points["<<i<<"]: (" << this->points[i](0) << "/" << this->points[i](1) << "/" << this->points[i](2) << ")" << std::endl;
	}
	std::cout << "}" << std::endl;
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
void Cuboid::setColor(Color color){
	this->color = color;
}
Color Cuboid::getColor(){
	return this->color;
}

//private methods
void Cuboid::init(CVec4f origin, float length, float height, float depth, Color color){
	float tmp[4];
	this->points = new CVec4f[8];
	this->height = height;
	this->length = length;
	this->depth = depth;
	setColor(color);
	
	//front bottom left
	origin.getData(tmp);
	this->points[0] = origin;
	
	//front bottom right
	tmp[0] = increaseBy(tmp[0], length);
	this->points[1] = CVec4f(tmp);
	
	//front top left
	origin.getData(tmp);
	tmp[1] = increaseBy(tmp[1], height);
	this->points[2] = CVec4f(tmp);
	
	//front top right
	origin.getData(tmp);
	tmp[0] = increaseBy(tmp[0], length);
	tmp[1] = increaseBy(tmp[1], height);
	this->points[3] = CVec4f(tmp);
	
	//back bottom left
	origin.getData(tmp);
	tmp[2] = increaseBy(tmp[2], depth);
	this->points[4] = CVec4f(tmp);
	
	//back bottom right
	origin.getData(tmp);
	tmp[2] = increaseBy(tmp[2], depth);
	tmp[0] = increaseBy(tmp[0], length);
	this->points[5] = CVec4f(tmp);
	
	//back top left
	origin.getData(tmp);
	tmp[2] = increaseBy(tmp[2], depth);
	tmp[1] = increaseBy(tmp[1], height);
	this->points[6] = CVec4f(tmp);
	
	//back top right
	origin.getData(tmp);
	tmp[2] = increaseBy(tmp[2], depth);
	tmp[1] = increaseBy(tmp[1], height);
	tmp[0] = increaseBy(tmp[0], length);
	this->points[7] = CVec4f(tmp);
}

float Cuboid::increaseBy(float init, float incr){
	//if(init >= 0){
		return init + incr;
	//}
	//return init - incr;
}