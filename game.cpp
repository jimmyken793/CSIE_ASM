#include <mygba.h>
#include<cstdlib>
#include<time.h>
#include "game.h"

// create an apple on the map;
void game::createApple(){
		srand(time(NULL));
		NextApple_x = rand()%M_SIZE;
		NextApple_y = rand()%M_SIZE;
		int tmp;
		while(1){// create apple in the adjacency side;
			tmp = rand()%6;
			if( tmp + _side_now !=5 ){
				NextApple_z = tmp;
				break;	
			}
		}
		//update the apple to int_map;
		_game_map->set_int_map(NextApple_z,NextApple_x,NextApple_y,1);
}
void game::checkApple(int pos_z, int pos_x, int pos_y){
	if(_game_map->get_int_map(pos_z,pos_x,pos_y) == 1){
		createApple();// create another apple on the map;	
		appleWalk();
	}else{
		snakeWalk();
	}
}

// extend the snake, that is, snakeSizeNow++;

void game::appleWalk(){
	snake* tmp = new snake(Next_head_z, Next_head_x, Next_head_y);
	updateAppleWalk(Next_head_z,Next_head_x,Next_head_y,tmp);
}

// be similar with the snakeWalk, but do not delete the tail,and size++;
void game::updateAppleWalk(int z, int x, int y, snake* tmpS){
	tmpS->setChild( _game_map->getSnakeHead() );
	_game_map->set_int_map(z,x,y,2);
	_game_map->getSnakeHead()->setParent(tmpS); 
	_game_map->set_int_map(_game_map->getSnakeHead()->getZ(),
	                      _game_map->getSnakeHead()->getX(),
					      _game_map->getSnakeHead()->getY(),3);
	_game_map->setSnakeHead(tmpS);
	_game_map->setSnakeSize(1);// size++;
}

void game::unlock(){
}

void game::int_handler(){
	count++;
	bool bomb_flag=false;
	if(count==20){
		update_pos(_game_map->getSnakeHead()->getZ(),
					_game_map->getSnakeHead()->getX(),
					_game_map->getSnakeHead()->getY());
		bomb_flag=bomb(Next_head_z, Next_head_x, Next_head_y);
		snakeWalk();
		count=0;
		display->refresh(this->_game_map);
	}
}

// create _game_map;
game::game(display_controller * display){
    _game_map = new map();
	_side_now = 0 ; 
	_upside = 2;
	_leftside = 4;
	_rightside = 1;
	_downside = 3;
	this->display = display;
	display->refresh(this->_game_map);
}



// check game over or not;
bool game::bomb(int pos_z,int pos_x,int pos_y){
	if(_game_map->get_int_map(pos_z,pos_x,pos_y) > 1 )
		return true;	//bomb!!
	return false;		//safe
}
// return 0 if is not at boundary;
// return the direction of the boundary encountered;
// up=1; down=2; left=3; right=4;
int game::checkBoundary(int pos_z,int pos_x,int pos_y){
	if(pos_y < 0)					//check upside;
		return 1;
	else if(pos_y > M_SIZE) 		//check downside;
		return 2;
	else if(pos_x < 0)				//check leftside;
		return 3;
	else if(pos_x > M_SIZE)		//check rightside;
		return 4;
	else							//is not at boundary;
		return 0;
}
// return the direction that user input;
int game::changeDir(int current_Dir){
	if(F_CTRLINPUT_UP_PRESSED && current_Dir != 2)
		return 1;			// up;
	else if(F_CTRLINPUT_DOWN_PRESSED && current_Dir != 1)
		return 2;			// down;
	else if(F_CTRLINPUT_LEFT_PRESSED && current_Dir != 4)
		return 3;			// left;
	else if(F_CTRLINPUT_RIGHT_PRESSED && current_Dir != 3)
		return 4;			// right;
	return current_Dir;
}

// update the next SnakeHead's position;
void game::update_pos(int z,int x, int y){
	_game_map->setSnakeHead_Dir( changeDir(_game_map->getSnakeHead_Dir() ) );
	int flag;
	int tmpDir = _game_map->getSnakeHead_Dir();
	if(tmpDir==1&&checkBoundary(z,x,y-1)==1)	flag=1;
	else if(tmpDir==2&&checkBoundary(z,x,y+1)==2) flag=2;
	else if(tmpDir==3&&checkBoundary(z,x-1,y)==3) flag=3;
	else if(tmpDir==4&&checkBoundary(z,x+1,y)==4) flag=4;
	else flag=0;
	
	if(flag==1){
		setNewSide(1);
		Next_head_y=y-1;
		Next_head_x=x;
		//rotate()
	}
	else if(flag==2){
		setNewSide(2);
		Next_head_y=y+1;
		Next_head_x=x;
		//rotate()
	}
	else if(flag==3){
		setNewSide(3);
		Next_head_x=x-1;
		Next_head_y=y;
		//rotate()
	}
	else if(flag==4){
		setNewSide(4);
		Next_head_x=x+1;
		Next_head_y=y;
		//rotate()
	}
	else{//4บุ  need not to rotate,just change the Next_head
		if(tmpDir ==1){
			setNewSide(1);
			Next_head_y=y-1;
			Next_head_x=x;
		}
		else if(tmpDir ==2){
			setNewSide(2);
			Next_head_y=y+1;
			Next_head_x=x;
		}
		else if(tmpDir ==3){
			setNewSide(3);
			Next_head_x=x-1;
			Next_head_y=y;
		}
		else if(tmpDir ==4){
			setNewSide(4);
			Next_head_x=x+1;
			Next_head_y=y;
		}
		
	}
	Next_head_z=_side_now;
}

void game::setNewSide(int a){
	if(a==1){
		_downside=_side_now;
		_side_now=_upside;
		_upside=5-_downside;
	}
	else if(a==2){
		_upside=_side_now;
		_side_now=_downside;
		_downside=5-_upside;
	}
	else if(a==3){
		_rightside=_side_now;
		_side_now=_leftside;
		_leftside=5-_rightside;
	}
	else if(a==4){
		_leftside=_side_now;
		_side_now=_rightside;
		_rightside=5-_leftside;
	}
}
// control the move of the snake;
// create a new SnakeHead, delete the Snaketail and update them;
void game::snakeWalk(){
		snake* tmp=new snake(Next_head_z,Next_head_x,Next_head_y);
		updateSnake(Next_head_z,Next_head_x,Next_head_y,tmp);
}
// update the snake's Head and Tail, and also update the map ;
void game::updateSnake(int z, int x, int y, snake* tmpS){
	tmpS->setChild( _game_map->getSnakeHead() );
	// set the block of the snakeHead to "2"
	_game_map->set_int_map(z,x,y,2);
	_game_map->getSnakeHead()->setParent(tmpS) ;
	_game_map->set_int_map(_game_map->getSnakeHead()->getZ(),
							_game_map->getSnakeHead()->getX(),
							_game_map->getSnakeHead()->getY(),3);
	_game_map->setSnakeHead(tmpS);
	//reset the block that the tail is standing to "0";
	_game_map->set_int_map(_game_map->getSnakeTail()->getZ(),
							_game_map->getSnakeTail()->getX(),
							_game_map->getSnakeTail()->getY(),0);
	_game_map->setSnakeTail(_game_map->getSnakeTail()->getParent());
	delete(_game_map->getSnakeTail()->getChild());
}
