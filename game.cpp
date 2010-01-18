#include <mygba.h>
#include<cstdlib>
#include<time.h>
#include "game.h"
void game::unlock(){
}

void game::int_handler(){
	count++;
	if(count==20){
		this->_snake->move();
		display->refresh(this->_game_map);
		count=0;
	}
}
// create _game_map;
game::game(display_controller * display){
    _game_map = new map();
	this->display = display;
	this->_snake=new snake(7,7,0,_game_map);
	display->refresh(this->_game_map);
}
