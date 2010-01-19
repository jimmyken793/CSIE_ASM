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
bool display_controller::refresh(map * data, void (*unlock)() ){
	if(this->data!=data){
		delete this->data;
		this->data=data;
	}
	this->unlock_fp=unlock;
	return true;
}
void display_controller::int_handler(){
	static const int base[6][2]={{1,1},{2,1},{1,0},{1,2},{0,1},{1,3}};
	count++;
	if(count==2){
		int t=count;
		ham_ClearBackBuffer(0xFF);
		for(int a=0;a<6;a++){
			for(int i=0;i<M_SIZE;i++){
				for(int ii=0;ii<M_SIZE;ii++){
					ham_PutPixel(7+base[a][0]*M_SIZE+i,30+base[a][1]*M_SIZE+ii,this->data->get_int_map(a,i,ii));
				}
			}
		}
		if(rotate){
			double angle=(theta*pi)/180;
			double y1=(p_size+p_size*sqrt(2)*sin((pi/-4)+angle))/2;
			double y2=(p_size-p_size*sqrt(2)*sin((pi/4)+angle))/2;
			double y3=(p_size+p_size*sqrt(2)*sin((pi/4)+angle))/2;
			double z1=distance-(p_size*sqrt(2)*sin((pi/4)+angle))/2;
			double z2=distance+(p_size*sqrt(2)*cos((pi/4)+angle))/2;
			double z3=distance-(p_size*sqrt(2)*cos((pi/4)+angle))/2;
			int width2=p_size*z1/z2;
			int width3=p_size*z1/z3;
			int h=y1-y2;
			width2=(width2*y1)/h;
			h=y3-y1;
			//width3=(width3*y1)/h;
			y1=(y1>=0)?y1:0;
			y2=(y2>=0)?y2:0;
			y3=(y3<=p_size)?y3:p_size;
			ham_PutLine(left,top+y1,left+p_size,top+y1,1);
			
			ham_PutLine(left+(p_size-width2)/2,top+y2,left+(p_size+width2)/2,top+y2,1);
			ham_PutLine(left+(p_size-width2)/2,top+y2,left,top+y1,1);
			ham_PutLine(left+(p_size+width2)/2,top+y2,left+p_size,top+y1,1);
			
			ham_PutLine(left+(p_size-width3)/2,top+y3,left+(p_size+width3)/2,top+y3,1);
			ham_PutLine(left+(p_size-width3)/2,top+y3,left,top+y1,1);
			ham_PutLine(left+(p_size+width3)/2,top+y3,left+p_size,top+y1,1);
			if(theta<90)
				theta++;
			//	else theta=0;
		}else{
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
	this->count=0;
    block_size=10;
	p_size=block_size*M_SIZE;
	distance=2*p_size;
    top=5;
    left=60;
	rotate=true;
	theta=0;
}
