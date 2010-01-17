#include <mygba.h>
#include "game.h"

snake::~snake(){
}
int snake::getX(){
	return snake_x;
}
int snake::getY(){
	return snake_y;
}
int snake::getZ(){
	return snake_z;
}

void snake::setChild(snake* node){
	this->child=node;
}

void snake::setParent(snake* node){
	this->parent=node;
}


map::map(){
	//this->int_map=new int[6][M_SIZE][M_SIZE];	//create the map;
	// initialize the default snake of snakeSizeNow=3;
	// the default start side is " 0 " ;
	// use linked list to implement the whole snake;
	snake* tmp=new snake(0,5,10);
	snakeSizeNow=0;
	snakeSizeNow++;
	SnakeHead=tmp;
	SnakeHead->setSpriteType(2);
	SnakeHead->setChild(SnakeHead);
	SnakeHead->setParent(SnakeHead);
	SnakeTail=SnakeHead;
	for(int i=1;i<=2;i++){
		tmp=new snake(SnakeTail->getZ(), (SnakeTail->getX())-i, SnakeTail->getY());
		tmp->setParent(SnakeTail);
		SnakeTail->setChild(tmp);
		SnakeTail=tmp;
		SnakeTail->setSpriteType(3);
		snakeSizeNow++;
	}
}

map::~map(){
}

snake* map::getSnakeHead(){
	return SnakeHead;
}

snake* map::getSnakeTail(){
	return SnakeTail;
}

int map::getSnakeHead_Dir(){
	return SnakeHead_Dir;
}

int map::getSnakeSizeNow(){
	return snakeSizeNow;
}

block map::getGmap(int z, int x, int y){
	return gmap[z][x][y];
}

void map::setSnakeHead(snake* Head){
	SnakeHead=Head;
}

void map::setSnakeTail(snake* Tail){
	SnakeTail=Tail;
}

snake::snake(int z, int x, int y){
	snake_x=x;
	snake_y=y;
	snake_z=z;
}


block::block(int type){
	sprite_type=type;
}
void block::setSpriteType(size_t type){
	sprite_type=type;
}
size_t block::getSpriteType(){
	return sprite_type;
} 

void game::unlock(){
	
}
void game::int_handler(){
	
}

// check game over or not;
bool game::bomb(int pos_z,int pos_x,int pos_y){
	if(_game_map.getGmap(pos_z,pos_x,pos_y).getSpriteType() > 1 )
		return false;
	return true;
}
// return 0 if is not at boundary;
// return the direction of the boundary encountered;
// up=1; down=2; left=3; right=4;
int game::checkBoundary(int pos_z,int pos_x,int pos_y){
	if(pos_y < 0)					//check upside;
	return 1;
	else if(pos_y > _M_SIZE) 		//check downside;
	return 2;
	else if(pos_x < 0)				//check leftside;
	return 3;
	else if(pos_x > _M_SIZE)		//check rightside;
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
// control the move of the snake;
// create a new SnakeHead, delete the Snaketail and update them;
void game::snakeWalk(){
	_game_map.setSnakeHead_Dir( changeDir(_game_map.SnakeHead_Dir) );
	if(getSnakeHead_Dir() == 1)		// walk upward;
	{
		int x=_game_map.getSnakeHead()->getX();
		int y=_game_map.getSnakeHead()->getY()-1 ;
		int z=_game_map.getSnakeHead()->getZ();
		snake* tmp=new snake(z,x,y);
		updateSnake(tmp);
	}
	else if(getSnakeHead_Dir() == 2) // walk downward;
	{
		int x=_game_map.getSnakeHead()->getX();
		int y=_game_map.getSnakeHead()->getY()+1 ;
		int z=_game_map.getSnakeHead()->getZ();
		snake* tmp=new snake(z,x,y);
		updateSnake(tmp);
	}
	else if(getSnakeHead_Dir() == 3) // walk leftward;
	{
		int x=_game_map.getSnakeHead()->getX()-1;
		int y=_game_map.getSnakeHead()->getY();
		int z=_game_map.getSnakeHead()->getZ();
		snake* tmp=new snake(z,x,y);
		updateSnake(tmp);
	}
	else if(getSnakeHead_Dir() == 4) //walk rightward;
	{
		int x=_game_map.getSnakeHead()->getX();
		int y=_game_map.getSnakeHead()->getY()+1 ;
		int z=_game_map.getSnakeHead()->getZ();
		snake* tmp=new snake(z,x,y);
		updateSnake(tmp);
	}
}
// update the snake's Head and Tail, and also update the map ;
void game::updateSnake(snake* tmpS){
	tmpS->child=_game_map.getSnakeHead();
	_game_map.getGmap(z,x,y).setSprite(2);
	_game_map.getSnakeHead()->parent=tmpS ;
	_game_map.setSnakeHead(tmpS);
	_game_map.getSnakeHead()->child.setSprite(3);
	_game_map.setSnakeTail(_game_map.getSnakeTail()->parent);
	delete(_game_map.getSnakeTail()->child);
}

