#include <cstdlib>
#include <cmath>
#include <mygba.h>
#include "setting/setting.h"
#include "display.h"
#define pi 3.14159265358

bool display_controller::refresh(){
	return true;
}
/*
function refresh
params:
	data:
		map data
*/
bool display_controller::refresh(map * data){
	if(this->data!=data){
		delete this->data;
		//this->data=new map(*data);
		this->data=data;
	}
	return true;
}
/*
        function refresh
        params:
          data:
            map data
          unlock:
            unlock function
        */
bool display_controller::refresh(map * data, game* Game,int r_direction){
	if(this->data!=data){
		delete this->data;
		//this->data=new map(*data);
		this->data=data;
	}else{
		this->data=new map(*data);
	}
	rotating=true;
	theta=0;
	this->r_direction=r_direction;
	this->Game=Game;
	return true;
}

void display_controller::print_dot(int x,int y,int type){
	for(int i=0;i<block_size;i++){
		for(int ii=0;ii<block_size;ii++){
			ham_PutPixel(left+block_size*x+i,top+block_size*y+ii,type);
		}
	}
}

void display_controller::PutLine(point* a,point* b,int c){
	ham_PutLine(left+a->getX(),top+a->getY(),left+b->getX(),top+b->getY(),c);
}

void display_controller::rotate(){
	double angle=(theta*pi*10)/180;
	if(angle>pi/2)
		angle=pi/2;
	point *p1=new point(0,(p_size+p_size*sqrt(2)*sin((pi/-4)+angle))/2,distance-(p_size*sqrt(2)*sin((pi/4)+angle))/2);
	point *p2=new point(0,(p_size-p_size*sqrt(2)*sin((pi/4)+angle))/2,distance+(p_size*sqrt(2)*cos((pi/4)+angle))/2);
	point *p3=new point(0,(p_size+p_size*sqrt(2)*sin((pi/4)+angle))/2,distance-(p_size*sqrt(2)*cos((pi/4)+angle))/2);
	double width2=p_size*p1->getZ()/p2->getZ();
	double width3=p_size*p1->getZ()/p3->getZ();
	double h=p1->getY()-p2->getY();
	if(h>0.001)
		width2=(width2*p1->getY())/h;
	h=p3->getY()-p1->getY();
	width3+=((width3-p_size)*(p_size-p1->getY()))/h;
	double y1=(p1->getY()>=0)?p1->getY():0;
	double y2=(p2->getY()>=0)?p2->getY():0;
	double y3=(p3->getY()<=p_size)?p2->getY():p_size;
	delete p1;
	delete p2;
	delete p3;
	point *pa=new point((p_size-width2)/2,y2);
	point *pb=new point((p_size+width2)/2,y2);
	point *pc=new point(0,y1);
	point *pd=new point(p_size,y1);
	point *pe=new point((p_size-width3)/2,y3);
	point *pf=new point((p_size+width3)/2,y3);
	switch(r_direction){
		case 0:
			pa->reflectXY();
			pb->reflectXY();
			pc->reflectXY();
			pd->reflectXY();
			pe->reflectXY();
			pf->reflectXY();
		case 1:
			pa->reflectXY();
			pb->reflectXY();
			pc->reflectXY();
			pd->reflectXY();
			pe->reflectXY();
			pf->reflectXY();
			pa->reflectX(p_size/2);
			pb->reflectX(p_size/2);
			pc->reflectX(p_size/2);
			pd->reflectX(p_size/2);
			pe->reflectX(p_size/2);
			pf->reflectX(p_size/2);
		break;
		case 2:
			pa->reflectY(p_size/2);
			pb->reflectY(p_size/2);
			pc->reflectY(p_size/2);
			pd->reflectY(p_size/2);
			pe->reflectY(p_size/2);
			pf->reflectY(p_size/2);
		break;
		case 3:
			pa->reflectXY();
			pb->reflectXY();
			pc->reflectXY();
			pd->reflectXY();
			pe->reflectXY();
			pf->reflectXY();
		break;
	}
	PutLine(pa,pb,1);
	PutLine(pa,pc,1);
	PutLine(pd,pb,1);
	PutLine(pc,pd,1);
	PutLine(pc,pe,1);
	PutLine(pe,pf,1);
	PutLine(pd,pf,1);
	delete pa;
	delete pb;
	delete pc;
	delete pd;
	delete pe;
	delete pf;
	if(angle<pi/2){
		theta++;
	}else{
		theta=0;
		r_direction=(r_direction+1)%4;
		rotating=false;
		to_unlock=true;
	}
}

void display_controller::int_handler(){
	if(data==0)
		return;
	static const int base[6][2]={{1,1},{2,1},{1,0},{1,2},{0,1},{1,3}};
	if(to_unlock){
		Game->unlock();
		to_unlock=false;
	}
	count++;
	if(count==1){
		ham_ClearBackBuffer(0xFF);
		for(int a=0;a<6;a++){
			for(int i=0;i<M_SIZE;i++){
				for(int ii=0;ii<M_SIZE;ii++){
					ham_PutPixel(7+base[a][0]*M_SIZE+i,30+base[a][1]*M_SIZE+ii,this->data->get_int_map(a,i,ii));
				}
			}
		}
		if(rotating){
			rotate();
		}else{
			ham_PutLine(left,top,left,top+p_size,1);
			ham_PutLine(left,top,left+p_size,top,1);
			ham_PutLine(left,top+p_size,left+p_size,top+p_size,1);
			ham_PutLine(left+p_size,top,left+p_size,top+p_size,1);
			int camera=data->get_camera();
			int initx,inity,x_inc,y_inc,x_end,y_end;
			bool transpose=false,x_r=false,y_r=false;
			switch(data->get_upside()){
				case 0:
				break;
				case 1:
					y_r=true;
					transpose=true;
				break;
				case 2:
					x_r=true;
					y_r=true;
				break;
				case 3:
					x_r=true;
					transpose=true;
				break;
			}
			for(int i=0;i<M_SIZE;i++){
				for(int ii=0;ii<M_SIZE;ii++){
					int x=x_r?M_SIZE-1-i:i;
					int y=y_r?M_SIZE-1-ii:ii;
					int type=transpose?this->data->get_int_map(camera,y,x):this->data->get_int_map(camera,x,y);
					if(type!=0)
						print_dot(i,ii,type);
				}
			}
		}
		//int basex=int(110+sin(t*pi/180)*40);
		//int basey=70;
		//ham_PutLine(basex-(40*cos(t*pi/180)),basey-(40*sin(t*pi/180)),(int)(basex+(40*cos(t*pi/180))),(int)(basey+(40*sin(t*pi/180))),(count/60)%3+2);
		//ham_VBAText("%d %d\n",(int)(50+(40*cos(5*t*pi/180))),(int)(50+(40*sin(5*t*pi/180))));*/
		ham_FlipBGBuffer();
		count=0;
	}
}
display_controller::display_controller(map* data, int fps){
	ham_SetBgMode(4);
	ham_SetBgPalColRGB(0xFF,0,0,0);
	ham_SetBgPalColRGB(0,0xEE,0x82,0xEE);
	ham_SetBgPalColRGB(1,0xff,0xff,0xff);
	ham_SetBgPalColRGB(2,0xff,0,0);
	ham_SetBgPalColRGB(3,0,0xff,0);
	ham_SetBgPalColRGB(4,0,0,0xff);
	ham_ClearBackBuffer(0xFF);
	ham_FlipBGBuffer();
	ham_ClearBackBuffer(0xFF);
	this->fps=fps;
	this->data=data;
	//this->data=new map(*data);
	this->count=0;
	block_size=10;
	p_size=block_size*M_SIZE;
	distance=2*p_size;
	top=4;
	left=60;
	rotating=false;
	r_direction=0;
	theta=0;
	to_unlock=false;
}
