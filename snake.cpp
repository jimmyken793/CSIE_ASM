#include "snake.h"
#include "setting/setting.h"
#include "point.h"
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
	this->add_tail(x,y-3,z);
	this->add_tail(x,y-4,z);
	dx=1;
	dy=0;
}
void snake::move(){
	add_head(remove_tail());
	object* h=body[(head+2)%maximum];
	int nx=h->getx()+dx;
	int ny=h->gety()+dy;
	int nz=h->getz();
	int side=0;
	//int pos=0;
	if(nx<0){
		side=3;
		switch(_map->get_s_r(nz,side)){
			case 0:
				set_direction(0,1);
				nx=ny;
				ny=0;
			break;
			case 1:
				set_direction(-1,0);
				ny=ny;
				nx=M_SIZE-1;
			break;
			case 2:
				set_direction(0,-1);
				nx=M_SIZE-1-ny;
				ny=M_SIZE-1;
			break;
			case 3:
				set_direction(1,0);
				ny=M_SIZE-1-ny;
				nx=0;
			break;
		}
		nz=_map->get_f_r(nz,side);
		_map->rotate(side);
	}else if(ny<0){
		side=0;
		switch(_map->get_s_r(nz,side)){
			case 0:
				set_direction(0,1);
				nx=M_SIZE-1-nx;
				ny=0;
			break;
			case 1:
				set_direction(-1,0);
				ny=M_SIZE-1-nx;
				nx=M_SIZE-1;
			break;
			case 2:
				ny=M_SIZE-1;
			break;
			case 3:
				set_direction(1,0);
				ny=nx;
				nx=0;
			break;
		}
		nz=_map->get_f_r(nz,side);
		_map->rotate(side);
	}else if(nx==M_SIZE){
		side=1;
		switch(_map->get_s_r(nz,side)){
			case 0:
				set_direction(0,1);
				nx=M_SIZE-1-ny;
				ny=0;
			break;
			case 1:
				set_direction(-1,0);
				ny=M_SIZE-1-ny;
				nx=M_SIZE-1;
			break;
			case 2:
				set_direction(0,-1);
				nx=ny;
				ny=M_SIZE-1;
			break;
			case 3:
				set_direction(1,0);
				ny=ny;
				nx=0;
			break;
		}
		nz=_map->get_f_r(nz,side);
		_map->rotate(side);
	}else if(ny==M_SIZE){
		side=2;
		switch(_map->get_s_r(nz,side)){
			case 0:
				set_direction(0,1);
				nx=nx;
				ny=0;
			break;
			case 1:
				set_direction(-1,0);
				ny=nx;
				nx=M_SIZE-1;
			break;
			case 2:
				set_direction(0,-1);
				nx=M_SIZE-1-nx;
				ny=M_SIZE-1;
			break;
			case 3:
				set_direction(1,0);
				ny=M_SIZE-1-nx;
				nx=0;
			break;
		}
		nz=_map->get_f_r(nz,side);
		_map->rotate(side);
	}else{
	}
	
	//ham_VBAText("%d %d %d\n",nx,ny,nz);
	body[head==maximum-1?0:(head+1)]->setpos(nx,ny,nz);
}

void snake::set_direction(int dx,int dy){
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
