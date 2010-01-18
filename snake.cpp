#include "snake.h"
snake::~snake(){
}
int snake::getX(){
	return x;
}
int snake::getY(){
	return y;
}
int snake::getZ(){
	return z;
}

snake* snake::getChild()
{
	return child;
}

snake* snake::getParent()
{
	return parent;
}
void snake::setChild(snake* node){
	this->child=node;
}

void snake::setParent(snake* node){
	this->parent=node;
}

snake::snake(int z, int x, int y){
	x=x;
	y=y;
	z=z;
}



