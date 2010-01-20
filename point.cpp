#include "point.h"

double point::getX(){
	return x;
}
double point::getY(){
	return y;
}
double point::getZ(){
	return z;
}
void point::setX(double x){
	this->x=x;
}
void point::setY(double y){
	this->y=y;
}
void point::setZ(double z){
	this->z=z;
}
point::point(double x,double y,double z){
	this->x=x;
	this->y=y;
	this->z=z;
}

void point::reflectXY(){
	double tmp=x;
	x=y;
	y=tmp;
}

void point::reflectX(double ax){
	x=ax+(ax-x);
}
void point::reflectY(double ay){
	y=ay+(ay-y);
}

void point::reverseX(){
	x*=-1;
}

void point::reverseY(){
	y*=-1;
}
void point::reverseXY(){
	x*=-1;
	y*=-1;
}
