#include "object.h"

object::object(int x,int y,int z,int type,map *_map){
	this->x=x;
	this->y=y;
	this->z=z;
	this->type=type;
	this->_map=_map;
}

int object::getx(){
	return x;
}
int object::gety(){
	return y;
}
int object::getz(){
	return z;
}
int object::gettype(){
	return type;
}
void object::setx(int x){
	_map->set_int_map(this->z,this->x,this->y,0);
	_map->set_int_map(z,x,y,type);
	this->x=x;
}
void object::sety(int y){
	_map->set_int_map(this->z,this->x,this->y,0);
	_map->set_int_map(z,x,y,type);
	this->y=y;
}
void object::setz(int z){
	_map->set_int_map(this->z,this->x,this->y,0);
	_map->set_int_map(z,x,y,type);
	this->z=z;
}
void object::settype(int type){
	_map->set_int_map(z,x,y,type);
	this->type=type;
}
void object::setpos(int x,int y,int z){
	_map->set_int_map(this->z,this->x,this->y,0);
	_map->set_int_map(z,x,y,type);
	this->x=x;
	this->y=y;
	this->z=z;
}
