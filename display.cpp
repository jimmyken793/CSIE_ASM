#include <cstdlib>
#include <cmath>
#include <mygba.h>
#include "setting/setting.h"
#include "display.h"
#define pi 3.1415926

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
	count++;
	if(count%10==0){
		int base[6][2]={
			{2,2},
			{3,2},
			{2,1},
			{2,3},
			{1,2},
			{2,4}
			};
		int t=count;
		ham_ClearBackBuffer(0xFF);
		//ham_VBAText("==============================\n");
		for(int a=0;a<6;a++){
			for(int i=0;i<M_SIZE;i++){
				for(int ii=0;ii<M_SIZE;ii++){
					ham_PutPixel(base[a][0]*2*M_SIZE+i*2,base[a][1]*2*M_SIZE+ii*2,this->data->get_int_map(a,i,ii));
					ham_PutPixel(base[a][0]*2*M_SIZE+i*2+1,base[a][1]*2*M_SIZE+ii*2,this->data->get_int_map(a,i,ii));
					ham_PutPixel(base[a][0]*2*M_SIZE+i*2,base[a][1]*2*M_SIZE+ii*2+1,this->data->get_int_map(a,i,ii));
					ham_PutPixel(base[a][0]*2*M_SIZE+i*2+1,base[a][1]*2*M_SIZE+ii*2+1,this->data->get_int_map(a,i,ii));
					//ham_VBAText("%d ",this->data->get(i,ii,0));
				}
				//ham_VBAText("\n");
			}
		}
		//int basex=int(110+sin(t*pi/180)*40);
		//int basey=70;
		//ham_PutLine(basex-(40*cos(t*pi/180)),basey-(40*sin(t*pi/180)),(int)(basex+(40*cos(t*pi/180))),(int)(basey+(40*sin(t*pi/180))),(count/60)%3+2);
		//ham_VBAText("%d %d\n",(int)(50+(40*cos(5*t*pi/180))),(int)(50+(40*sin(5*t*pi/180))));*/
		ham_FlipBGBuffer();
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
	lastbuffer=ham_GetBGBuffer();
}
