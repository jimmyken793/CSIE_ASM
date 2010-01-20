#include <mygba.h>
#include<cstdlib>
#include<time.h>
#include "game.h"

void game::unlock(){
	//ham_VBAText("unlock!\n");
	locked=false;
}
void game::lock(){
	locked=true;
}

//fires every screen refresh
void game::int_handler(){
	count++;
	if(count==10){
		if(!locked){
			this->_snake->move();
			display->refresh(this->_game_map);
		}
		count=0;
	}
}
// create _game_map;
game::game(display_controller * display){
    _game_map = new map(this);
    locked=false;
	this->display = display;
	this->_snake=new snake(7,7,0,_game_map);
	display->refresh(this->_game_map);
	prev_key=-1;
}

display_controller* game::get_display(){
	return display;
}

void game::key(){
	if(!locked){
		int key=-1;
		if(F_CTRLINPUT_UP_PRESSED){
			key=0;
		}else 
		if(F_CTRLINPUT_DOWN_PRESSED){
			key=2;
		}else 
		if(F_CTRLINPUT_LEFT_PRESSED){
			key=3;
		}else 
		if(F_CTRLINPUT_RIGHT_PRESSED){
			key=1;
		}
		switch(key>=0?(key+_game_map->get_upside())%4:-1){
			case 0:
			if(this->_snake->getdy()==0)
				this->_snake->set_direction(0,-1);
			break;
			case 1:
			if(this->_snake->getdx()==0)
				this->_snake->set_direction(1,0);
			break;
			case 2:
			if(this->_snake->getdy()==0)
				this->_snake->set_direction(0,1);
			break;
			case 3:
			if(this->_snake->getdx()==0)
				this->_snake->set_direction(-1,0);
			break;
		}
	}
}
