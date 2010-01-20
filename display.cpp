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
	old_camera=data->get_camera();
	old_upside=data->get_upside();
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

void display_controller::print_dot(int x,int y,point *origin,point *ax,point *ay,int r_direction,int type){
	if(type!=0){
		for(int iii=0;iii<block_size;iii++){
			switch(r_direction){
				case 0:{
					double dy=top+origin->getY()-((y*block_size+iii)*(ay->getY()))/p_size;
					double delta=-1*((y*block_size+iii)*(ay->getX())/ay->getY());
					double width=p_size-delta*2;
					double size=width/M_SIZE;
					if(dy>=top&&dy<=top+p_size)
						ham_PutLine(left+size*x+(delta),dy,left+size*(x+1)+(delta),dy,type);
				}
				break;
				case 2:{
					double delta=(((M_SIZE-y-1)*block_size+iii)*(ay->getX())/ay->getY());
					double width=p_size-delta*2;
					double size=width/M_SIZE;
					int dy=top+origin->getY()+(((M_SIZE-y-1)*block_size+iii)*(ay->getY()))/p_size;
					if(dy>=top&&dy<=top+p_size)
						ham_PutLine(left+size*x+(delta),dy,left+size*(x+1)+(delta),dy,type);
				}
				break;
				case 1:{
					double delta=(((M_SIZE-x-1)*block_size+iii)*(ay->getY())/ay->getX());
					double width=p_size+delta*2;
					double size=width/M_SIZE;
					int dx=left+origin->getX()+(((M_SIZE-x-1)*block_size+iii)*(ay->getX()))/p_size;
					if(dx>=left&&dx<=left+p_size)
						ham_PutLine(dx,top+size*y-(delta),dx,top+size*(y+1)-(delta),type);
				}
				break;
				case 3:{
					double delta=((x*block_size+iii)*(ay->getY())/ay->getX());
					double width=p_size+delta*2;
					double size=width/M_SIZE;
					int dx=left+origin->getX()+((x*block_size+iii)*(ay->getX()))/p_size;
					if(dx>=left&&dx<=left+p_size)
						ham_PutLine(dx,top+size*y-(delta),dx,top+size*(y+1)-(delta),type);
				}
				break;
			}
		}
	}
}

void display_controller::PutLine(point* a,point* b,int c){
	ham_PutLine(left+a->getX(),top+a->getY(),left+b->getX(),top+b->getY(),c);
}

void display_controller::rotate(){
	double angle=(theta*pi*25)/180;
	if(angle>pi/2)
		angle=pi/2;
	point *p1=new point(0,(p_size+p_size*sqrt(2)*sin((pi/-4)+angle))/2,distance-(p_size*sqrt(2)*sin((pi/4)+angle))/2);
	point *p2=new point(0,(p_size-p_size*sqrt(2)*sin((pi/4)+angle))/2,distance+(p_size*sqrt(2)*cos((pi/4)+angle))/2);
	point *p3=new point(0,(p_size+p_size*sqrt(2)*sin((pi/4)+angle))/2,distance-(p_size*sqrt(2)*cos((pi/4)+angle))/2);
	double width2=p_size*p1->getZ()/p2->getZ();
	double width3=p_size*p1->getZ()/p3->getZ();
	
	
	point *va=new point((p_size-width2)/(2),(p2->getY()-p1->getY()));
	point *vb=new point((width2-p_size)/(2),(p2->getY()-p1->getY()));
	point *vc=new point(p_size,0.0);
	point *vd=new point(p_size*-1,0.0);
	point *ve=new point((p_size-width3)/(2),(p3->getY()-p1->getY()));
	point *vf=new point((width3-p_size)/(2),(p3->getY()-p1->getY()));
	
	double h=p1->getY()-p2->getY();
	if(h>0.001)
		width2+=(((double)p_size-width2)*(-1*p2->getY())/h);
	h=p3->getY()-p1->getY();
	width3+=((p_size-width3)*(p3->getY()-p_size))/h;
	double y1=(p1->getY()>=0)?p1->getY():0;
	double y2=(p2->getY()>=0)?p2->getY():0;
	double y3=(p3->getY()<=p_size)?p3->getY():p_size;
	delete p1;
	delete p2;
	delete p3;
	point *pa=new point((p_size-width2)/2.0,y2);
	point *pb=new point((p_size+width2)/2.0,y2);
	point *pc=new point(0,y1);
	point *pd=new point(p_size,y1);
	point *pe=new point((p_size-width3)/2.0,y3);
	point *pf=new point((p_size+width3)/2.0,y3);
	switch(r_direction){
		case 0:
			pa->reflectXY();
			pb->reflectXY();
			pc->reflectXY();
			pd->reflectXY();
			pe->reflectXY();
			pf->reflectXY();
			va->reflectXY();
			vb->reflectXY();
			vc->reflectXY();
			vd->reflectXY();
			ve->reflectXY();
			vf->reflectXY();
			pa->reflectY(p_size/2);
			pb->reflectY(p_size/2);
			pc->reflectY(p_size/2);
			pd->reflectY(p_size/2);
			pe->reflectY(p_size/2);
			pf->reflectY(p_size/2);
			va->reverseXY();
			vb->reverseXY();
			vc->reverseXY();
			vd->reverseXY();
			ve->reverseXY();
			vf->reverseXY();
		case 1:
			pa->reflectXY();
			pb->reflectXY();
			pc->reflectXY();
			pd->reflectXY();
			pe->reflectXY();
			pf->reflectXY();
			va->reflectXY();
			vb->reflectXY();
			vc->reflectXY();
			vd->reflectXY();
			ve->reflectXY();
			vf->reflectXY();
			pa->reflectX(p_size/2);
			pb->reflectX(p_size/2);
			pc->reflectX(p_size/2);
			pd->reflectX(p_size/2);
			pe->reflectX(p_size/2);
			pf->reflectX(p_size/2);
			va->reverseX();
			vb->reverseX();
			vc->reverseX();
			vd->reverseX();
			ve->reverseX();
			vf->reverseX();
		break;
		case 2:
			pa->reflectY(p_size/2);
			pb->reflectY(p_size/2);
			pc->reflectY(p_size/2);
			pd->reflectY(p_size/2);
			pe->reflectY(p_size/2);
			pf->reflectY(p_size/2);
			va->reverseY();
			vb->reverseY();
			vc->reverseY();
			vd->reverseY();
			ve->reverseY();
			vf->reverseY();
			pa->reflectX(p_size/2);
			pb->reflectX(p_size/2);
			pc->reflectX(p_size/2);
			pd->reflectX(p_size/2);
			pe->reflectX(p_size/2);
			pf->reflectX(p_size/2);
			va->reverseX();
			vb->reverseX();
			vc->reverseX();
			vd->reverseX();
			ve->reverseX();
			vf->reverseX();
		break;
		case 3:
			pa->reflectXY();
			pb->reflectXY();
			pc->reflectXY();
			pd->reflectXY();
			pe->reflectXY();
			pf->reflectXY();
			va->reflectXY();
			vb->reflectXY();
			vc->reflectXY();
			vd->reflectXY();
			ve->reflectXY();
			vf->reflectXY();
			pa->reflectY(p_size/2);
			pb->reflectY(p_size/2);
			pc->reflectY(p_size/2);
			pd->reflectY(p_size/2);
			pe->reflectY(p_size/2);
			pf->reflectY(p_size/2);
			va->reverseY();
			vb->reverseY();
			vc->reverseY();
			vd->reverseY();
			ve->reverseY();
			vf->reverseY();
		break;
	}
	bool transpose=false,x_r=false,y_r=false;
	switch(old_upside){
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
			int x,y;
			if(transpose){
				y=x_r?M_SIZE-1-i:i;
				x=y_r?M_SIZE-1-ii:ii;
			}else{
				x=x_r?M_SIZE-1-i:i;
				y=y_r?M_SIZE-1-ii:ii;
			}
			int type=this->data->get_int_map(old_camera,x,y);
			if(type!=0){
				print_dot(i,ii,pc,vc,ve,r_direction,type);
			}
		}
	}
	PutLine(pa,pb,1);
	PutLine(pa,pc,1);
	PutLine(pd,pb,1);
	PutLine(pc,pd,3);
	PutLine(pc,pe,2);
	PutLine(pe,pf,1);
	PutLine(pd,pf,1);
	delete pa;
	delete pb;
	delete pc;
	delete pd;
	delete pe;
	delete pf;
	delete va;
	delete vb;
	delete vc;
	delete vd;
	delete ve;
	delete vf;
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
	if(count==3){
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
	ham_SetBgPalColRGB(5,0xff,0,0xff);
	ham_ClearBackBuffer(0xFF);
	ham_FlipBGBuffer();
	ham_ClearBackBuffer(0xFF);
	this->fps=fps;
	this->data=data;
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
