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
	data:z
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

void display_controller::print_dot(int x,int y,point *origin,point *ax,point *ay,int r_direction,int mode,int type){
	if(type!=0){
		for(int iii=0;iii<block_size;iii++){
			switch(r_direction){
				case 0:
					if(ay->getY()>=3||ay->getY()<=3){
						double delta=((y*block_size+iii)*(ay->getX())/ay->getY());
						double width=p_size-delta*2;
						double size=width/M_SIZE;
						double dx=size*x+(delta);
						double dy=top+origin->getY()-((y*block_size+iii)*(ay->getY()))/p_size;
						if(dy>=top&&dy<=top+p_size&&dx>=0&&dx<=240)
							ham_PutLine(left+dx,dy,left+size+dx,dy,type);
					}
				break;
				case 1:
					if(ay->getX()>=3||ay->getX()<=3){
						double delta=(((M_SIZE-x-1)*block_size+iii)*(ay->getY())/ay->getX());
						double width=p_size+delta*2;
						double size=width/M_SIZE;
						double dx=origin->getX()+(((M_SIZE-x-1)*block_size+iii)*(ay->getX()))/p_size;
						
						if(dx>=0&&dx<=p_size)
							ham_PutLine(left+dx,top+size*y-(delta),left+dx,top+size*(y+1)-(delta),type);
					}
				break;
				case 2:
					if(ay->getY()>=3||ay->getY()<=3){
						double delta=(((M_SIZE-y-1)*block_size+iii)*(ay->getX())/ay->getY());
						double width=p_size-delta*2;
						double size=width/M_SIZE;
						double dy=top+origin->getY()+(((M_SIZE-y-1)*block_size+iii)*(ay->getY()))/p_size;
						if(dy>=top&&dy<=top+p_size)
							ham_PutLine(left+size*x+(delta),dy,left+size*(x+1)+(delta),dy,type);
					}
				break;
				case 3:
					if(ay->getX()>=3||ay->getX()<=3){
						double delta=((x*block_size+iii)*(ay->getY())/ay->getX());
						double width=p_size+delta*2;
						double size=width/M_SIZE;
						double dx=left+origin->getX()+((x*block_size+iii)*(ay->getX()))/p_size;
						if(dx>=left&&dx<=left+p_size)
							ham_PutLine(dx,top+size*y-(delta),dx,top+size*(y+1)-(delta),type);
					}
				break;
			}
		}
	}
}

void display_controller::print_dot1(int x,int y,point *origin,point *ax,point *ay,int r_direction,int mode,int type){
	if(type!=0){
		for(int iii=0;iii<block_size;iii++){
			switch(r_direction){
				case 0:
					if(ay->getY()>=3||ay->getY()<=3){
						double delta=((y*block_size+iii)*(ay->getX())/ay->getY());
						double width=p_size-delta*2;
						double size=width/M_SIZE;
						double dx=size*x+(delta);
						double dy=top+origin->getY()-((y*block_size+iii)*(ay->getY()))/p_size;
						if(dy>=top&&dy<=top+p_size&&dx>=0&&dx<=240)
							ham_PutLine(left+dx,dy,left+size+dx,dy,type);
					}
				break;
				case 1:
					if(ay->getX()>=3||ay->getX()<=3){
						double delta=(((x)*block_size+iii)*(ay->getY())/ay->getX());
						double width=p_size+delta*2;
						double size=width/M_SIZE;
						double dx=origin->getX()+(((x)*block_size+iii)*(ay->getX()))/p_size;
						if(dx>=0&&dx<=p_size)
							ham_PutLine(left+dx,top+size*y-(delta),left+dx,top+size*(y+1)-(delta),type);
					}
				break;
				case 2:
					if(ay->getY()>=3||ay->getY()<=3){
						double delta=(((y)*block_size+iii)*(ay->getX())/ay->getY());
						double width=p_size-delta*2;
						double size=width/M_SIZE;
						double dy=top+origin->getY()+(((y)*block_size+iii)*(ay->getY()))/p_size;
						if(dy>=top&&dy<=top+p_size)
							ham_PutLine(left+size*x+(delta),dy,left+size*(x+1)+(delta),dy,type);
					}
				break;
				case 3:
					if(ay->getX()>=3||ay->getX()<=3){
						double delta=((x*block_size+iii)*(ay->getY())/ay->getX());
						double width=p_size+delta*2;
						double size=width/M_SIZE;
						double dx=left+origin->getX()+((x*block_size+iii)*(ay->getX()))/p_size;
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
	double angle=(theta*pi*33)/180;
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
	switch(r_direction){
		case 0:
			va->reverseXY();
			vb->reverseXY();
			vc->reverseXY();
			vd->reverseXY();
			ve->reverseXY();
			vf->reverseXY();
		break;
		case 1:
			va->reflectXY();
			vb->reflectXY();
			vc->reflectXY();
			vd->reflectXY();
			ve->reflectXY();
			vf->reflectXY();
			va->reverseX();
			vb->reverseX();
			vc->reverseX();
			vd->reverseX();
			ve->reverseX();
			vf->reverseX();
		break;
		case 2:
			va->reverseY();
			vb->reverseY();
			vc->reverseY();
			vd->reverseY();
			ve->reverseY();
			vf->reverseY();
			va->reverseX();
			vb->reverseX();
			vc->reverseX();
			vd->reverseX();
			ve->reverseX();
			vf->reverseX();
		break;
		case 3:
			va->reflectXY();
			vb->reflectXY();
			vc->reflectXY();
			vd->reflectXY();
			ve->reflectXY();
			vf->reflectXY();
			va->reverseY();
			vb->reverseY();
			vc->reverseY();
			vd->reverseY();
			ve->reverseY();
			vf->reverseY();
		break;
	}
	double h=p1->getY()-p2->getY();
	if(h>0.001)
		width2+=(((double)p_size-width2)*(-1*p2->getY())/h);
	h=p3->getY()-p1->getY();
	width3+=((p_size-width3)*(p3->getY()-p_size))/h;
	double y1=(p1->getY()>=0)?p1->getY():0;
	y1=y1<p_size?y1:p_size;
	double y2=(p2->getY()>=0)?p2->getY():0;
	double y3=(p3->getY()<=p_size)?p3->getY():p_size;
	point *pa;
	point *pb;
	point *pc;
	point *pd;
	point *pe;
	point *pf;
	switch(r_direction%4){
		case 0:
			
			pa=new point((p_size-width2)/2,y2);
			pb=new point((p_size+width2)/2,y2);
			pc=new point(0,y1);
			pd=new point(p_size,y1);
			pe=new point((p_size-width3)/2,y3);
			pf=new point((p_size+width3)/2,y3);
		break;
		case 1:
			pa=new point(p_size-y2,(p_size-width2)/2.0);
			pb=new point(p_size-y2,(p_size+width2)/2.0);
			pc=new point(p_size-y1,0);
			pd=new point(p_size-y1,p_size);
			pe=new point(p_size-y3,(p_size-width3)/2.0);
			pf=new point(p_size-y3,(p_size+width3)/2.0);
		break;
		case 2:
			pa=new point((p_size+width2)/2.0,p_size-y2);
			pb=new point((p_size-width2)/2.0,p_size-y2);
			pc=new point(p_size,p_size-y1);
			pd=new point(0,p_size-y1);
			pe=new point((p_size+width3)/2.0,p_size-y3);
			pf=new point((p_size-width3)/2.0,p_size-y3);
		break;
		case 3:
			pa=new point(y2,(p_size+width2)/2.0);
			pb=new point(y2,(p_size-width2)/2.0);
			pc=new point(y1,p_size);
			pd=new point(y1,0);
			pe=new point(y3,(p_size+width3)/2.0);
			pf=new point(y3,(p_size-width3)/2.0);
		break;
	}
	bool transpose=false,x_r=false,y_r=false;
	bool transpose1=false,x_r1=false,y_r1=false;
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
	printf("%d, %d\n",s_relation[old_camera][(old_upside+r_direction)%4],r_direction);
	
	switch(s_relation[old_camera][(old_upside+r_direction)%4]){
		case 0:
			switch(r_direction){
				case 0://
					x_r1=true; 
				break;
				case 1://x
					transpose1=true;
					y_r1=true;
				break;
				case 2://x
				break;
				case 3://x
					transpose1=true;
				break;
			}
		break;
		case 1:
			switch(r_direction){
				case 0:
					y_r1=true;
					x_r1=true;
					transpose1=true;
				break;
				case 1://x
					y_r1=true;
					x_r1=true;
				break;
				case 2:
					transpose1=true;
					y_r1=true;
				break;
				case 3://x
					x_r1=true;
				break;
			}
		break;
		case 2:
			switch(r_direction){
				case 0://x
					y_r1=true;
				break;
				case 1://x
					x_r1=true;
					transpose1=true;
				break;
				case 2:
					x_r1=true;
					y_r1=true;
				break;
				case 3:
					x_r1=true;
					y_r1=true;
					transpose1=true;
				break;
			}
		break;
		case 3:
			switch(r_direction){
				case 0:
					transpose1=true;
				break;
				case 1://x
				break;
				case 2:
					transpose1=true;
					x_r1=true;
					y_r1=true;
				break;
				case 3:
					y_r1=true;
				break;
			}
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
				print_dot(i,ii,pc,vc,ve,r_direction,0,type);
			}
			if(transpose1){
				y=x_r1?M_SIZE-1-i:i;
				x=y_r1?M_SIZE-1-ii:ii;
			}else{
				x=x_r1?M_SIZE-1-i:i;
				y=y_r1?M_SIZE-1-ii:ii;
			}
			type=this->data->get_int_map(data->get_camera(),x,y);
			if(type!=0){
				print_dot1(i,ii,pd,vd,vb,r_direction,1,type);
			}
			//printf("%d ",type);
		}
		//printf("\n");
	}
	//printf("==========================\n");
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
	delete va;
	delete vb;
	delete vc;
	delete vd;
	delete ve;
	delete vf;
	delete p1;
	delete p2;
	delete p3;
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
	static const int base[5][2]={{1,0},{2,1},{1,2},{0,1},{1,1}};
	if(to_unlock){
		Game->unlock();
		to_unlock=false;
	}
	count++;
	if(count==14){
		ham_ClearBackBuffer(0xFF);
		int c=data->get_camera();
		int u=data->get_upside();
		bool transpose=false,x_r=false,y_r=false;
		for(int a=0;a<4;a++){
			int us=(s_relation[c][(a+u)%4]+(6-a))%4;
			switch(us){
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
					if(transpose){
						int tmp=y;
						y=x;
						x=tmp;
					}
					int d=this->data->get_int_map(f_relation[c][(a+u)%4],x,y);
					ham_PutPixel(base[a][0]*M_SIZE*2+i*2,30+base[a][1]*M_SIZE*2+ii*2,d);
					ham_PutPixel(base[a][0]*M_SIZE*2+i*2,30+base[a][1]*M_SIZE*2+ii*2+1,d);
					ham_PutPixel(base[a][0]*M_SIZE*2+i*2+1,30+base[a][1]*M_SIZE*2+ii*2,d);
					ham_PutPixel(base[a][0]*M_SIZE*2+i*2+1,30+base[a][1]*M_SIZE*2+ii*2+1,d);
				}
			}
		}
		transpose=false,x_r=false,y_r=false;
		switch(u){
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
				int d=transpose?this->data->get_int_map(c,y,x):this->data->get_int_map(c,x,y);
				ham_PutPixel(base[4][0]*M_SIZE*2+i*2,30+base[4][1]*M_SIZE*2+ii*2,d);
				ham_PutPixel(base[4][0]*M_SIZE*2+i*2,30+base[4][1]*M_SIZE*2+ii*2+1,d);
				ham_PutPixel(base[4][0]*M_SIZE*2+i*2+1,30+base[4][1]*M_SIZE*2+ii*2,d);
				ham_PutPixel(base[4][0]*M_SIZE*2+i*2+1,30+base[4][1]*M_SIZE*2+ii*2+1,d);
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
	ham_SetBgPalColRGB(1,0xff,0,0);//apple is red
	ham_SetBgPalColRGB(2,0xff,0xff,0xff);//snake head is white
	ham_SetBgPalColRGB(3,0,0xff,0);//green
	ham_SetBgPalColRGB(4,0,0,0xff);//barrier is blue
	ham_SetBgPalColRGB(5,0xcc,0x99,0);//shit is brown(204,153,0)
	ham_ClearBackBuffer(0xFF);
	ham_FlipBGBuffer();
	ham_ClearBackBuffer(0xFF);
	s_relation[0][0]=2;
	s_relation[0][1]=3;
	s_relation[0][2]=0;
	s_relation[0][3]=1;
	
	s_relation[1][0]=1;
	s_relation[1][1]=1;
	s_relation[1][2]=1;
	s_relation[1][3]=1;
	
	s_relation[2][0]=2;
	s_relation[2][1]=0;
	s_relation[2][2]=0;
	s_relation[2][3]=0;
	
	s_relation[3][0]=2;
	s_relation[3][1]=2;
	s_relation[3][2]=0;
	s_relation[3][3]=2;
	
	s_relation[4][0]=3;
	s_relation[4][1]=3;
	s_relation[4][2]=3;
	s_relation[4][3]=3;
	
	s_relation[5][0]=2;
	s_relation[5][1]=1;
	s_relation[5][2]=0;
	s_relation[5][3]=3;
	
	f_relation[0][0]=2;
	f_relation[0][1]=1;
	f_relation[0][2]=3;
	f_relation[0][3]=4;
	
	f_relation[1][0]=2;
	f_relation[1][1]=5;
	f_relation[1][2]=3;
	f_relation[1][3]=0;
	
	f_relation[2][0]=5;
	f_relation[2][1]=1;
	f_relation[2][2]=0;
	f_relation[2][3]=4;
	
	f_relation[3][0]=0;
	f_relation[3][1]=1;
	f_relation[3][2]=5;
	f_relation[3][3]=4;
	
	f_relation[4][0]=2;
	f_relation[4][1]=0;
	f_relation[4][2]=3;
	f_relation[4][3]=5;
	
	f_relation[5][0]=3;
	f_relation[5][1]=1;
	f_relation[5][2]=2;
	f_relation[5][3]=4;
	this->fps=fps;
	this->data=data;
	this->count=0;
	block_size=8;
	p_size=block_size*M_SIZE;
	distance=2*p_size;
	top=17;
	left=99;
	rotating=false;
	r_direction=0;
	theta=0;
	to_unlock=false;
}
int display_controller::get_f_r(int z,int side){
	return f_relation[z][side];
}

int display_controller::get_s_r(int z,int side){
	return s_relation[z][side];
}
