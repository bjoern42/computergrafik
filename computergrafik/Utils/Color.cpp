#include "Color.hpp"

Color::Color(float r, float g, float b) {
	this->set(r, g, b);
}

void Color::set(float r, float g, float b){
	validate(&r);
	validate(&g);
	validate(&b);
	this->r = r;
	this->g = g;
	this->b = b;
}

void Color::validate(float *x){
	if(*x > 255){
		*x = 255;
	}
	if(*x < 0){
		*x = 0;
	}
}

void Color::lighten(float f){
	float r = this->r + this->r * f;
	float g = this->g + this->g * f;
	float b = this->b + this->b * f;
	
	set(r, g, b);
}

void Color::darken(float f){
	float r = this->r * f;
	float g = this->g * f;
	float b = this->b * f;
	
	set(r, g, b);
}