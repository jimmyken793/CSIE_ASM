#include <cstdlib>
#include <mygba.h>
#include "setting/setting.h"
#include "display.h"


display_data::display_data(){
	for(int i=0;i<M_SIZE;i++){
		for(int ii=0;ii<M_SIZE;ii++){
			this->map[0][i][ii]=0;
			this->map[1][i][ii]=0;
			this->map[2][i][ii]=0;
			this->map[3][i][ii]=0;
			this->map[4][i][ii]=0;
			this->map[5][i][ii]=0;
		}
	}
}
display_data::display_data(int (*newmap)[6][M_SIZE][M_SIZE]){
	for(int i=0;i<M_SIZE;i++){
		for(int ii=0;ii<M_SIZE;ii++){
			this->map[0][i][ii]=(*newmap)[1][i][ii];
			this->map[1][i][ii]=(*newmap)[1][i][ii];
			this->map[2][i][ii]=(*newmap)[1][i][ii];
			this->map[3][i][ii]=(*newmap)[1][i][ii];
			this->map[4][i][ii]=(*newmap)[1][i][ii];
			this->map[5][i][ii]=(*newmap)[1][i][ii];
		}
	}
}
bool display_controller::refresh(){
	return true;
}
/*
function refresh
params:
	data:
		map data
*/
bool display_controller::refresh(display_data * data){
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
bool display_controller::refresh(display_data * data, void (*unlock)() ){
	return true;
}
void display_controller::int_handler(){
	count++;
	ham_PutLine(1,1,(50+count/3<240)?50+count/3:240,50,1);
	ham_PutLine(1,1,50,(50+count/3<160)?50+count/3:160,1);
	ham_FlipBGBuffer();
	
}
display_controller::display_controller(display_data* data, int fps){
	ham_SetBgMode(4);
	ham_SetBgPalColRGB(0,0,0,0);
	ham_SetBgPalColRGB(1,0xff,0xff,0xff);
	ham_ClearBackBuffer(0);
	ham_FlipBGBuffer();
	ham_ClearBackBuffer(0);
	this->fps=fps;
	this->data=data;
	this->count=0;
	lastbuffer=ham_GetBGBuffer();
}
