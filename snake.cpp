#include "snake.h"
snake::~snake(){
}
int snake::getX(){
	return snake_x;
}
int snake::getY(){
	return snake_y;
}
int snake::getZ(){
	return snake_z;
}
snake::snake(int z, int x, int y){
	snake_x=x;
	snake_y=y;
	snake_z=z;
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
