#include "snake.h"
#include "setting/setting.h"
#include <mygba.h>
snake::~snake(){
}
snake::snake(int x,int y,int z,map* _map){
	this->_map=_map;
	this->head=0;
	this->tail=1;
	this->maximum=6*M_SIZE*M_SIZE;
	this->add_head(x,y,z);
	this->add_tail(x,y-1,z);
	this->add_tail(x,y-2,z);
	dx=1;
	dy=0;
	//ham_VBAText("%d, %d, %d\n",x,y,z);
}
void snake::move(){
	add_head(remove_tail());
	body[(tail-1)%maximum]=NULL;
	tail=tail==0?maximum-1:tail-1;
	object* h=body[(head+2)%maximum];
	int nx=h->getx()+dx;
	int ny=h->gety()+dy;
	int nz=h->getz();
	//ham_VBAText("%d, %d, %d\n",nx,ny,nz);
	body[(head+1)%maximum]->setpos(nx,ny,nz);
}
void snake::set_ditection(int dx,int dy){
	this->dx=dx;
	this->dy=dy;
}
int snake::getdx(){
	return dx;
}
int snake::getdy(){
	return dy;
}
void snake::add_head(int x,int y,int z){
	this->body[this->head]=new object(x,y,z,3,_map);
	head=head==0?maximum-1:head-1;
}

object* snake::remove_tail(){
	if(tail==0)
		tail=maximum;
	object* t=body[(tail-1)%maximum];
	body[(tail-1)%maximum]=NULL;
	tail=tail==0?maximum-1:tail-1;
	return t;
}
void snake::add_head(object *obj){
	this->body[this->head]=obj;
	head=head==0?maximum-1:head-1;
}
void snake::add_tail(int x,int y,int z){
	_map->set_int_map(z,x,y,3);
	this->body[this->tail]=new object(x,y,z,3,_map);
	tail=tail==maximum-1?0:tail+1;
}
