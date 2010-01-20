#include "map.h"

map::map(){
	//this->int_map = new int[6][M_SIZE][M_SIZE];	//create the map;
	for(int i=0;i<6;i++)	//z
	{
		for(int j=0;j<M_SIZE;j++)	//x
		{
			for(int k=0;k<M_SIZE;k++)	//y
			    int_map[i][j][k]=0;
		}	
		
	}
	init_snake();
	
	SnakeHead_Dir = 4 ;  // default rightward;
}

map::~map(){
}

void map::setSnakeSize(int value)
{
	snakeSizeNow += value;	
}

void map::init_snake()
{
	// initialize the default snake of snakeSizeNow=3;
	// the default start side is " 0 " ;
	// use linked list to implement the whole snake;
	snake* tmp=new snake(0,5 ,10);
	snakeSizeNow=1;
	SnakeHead=tmp;
	set_int_map(SnakeHead->getZ(),SnakeHead->getX(),SnakeHead->getY(),2);
	SnakeHead->setChild(SnakeHead);
	SnakeHead->setParent(SnakeHead);
	SnakeTail=SnakeHead;

	for(int i=1;i<=2;i++){
		tmp=new snake(SnakeTail->getZ(), (SnakeTail->getX())-1, SnakeTail->getY());
		tmp->setParent(SnakeTail);
		SnakeTail->setChild(tmp);
		SnakeTail=tmp;
		set_int_map(SnakeTail->getZ(),SnakeTail->getX(),SnakeTail->getY(),3);
		snakeSizeNow++;
	}
	
}

int map::get_int_map(int z, int x, int y){
	return int_map[z][x][y];
}

void map::set_int_map(int z, int x, int y, int type)
{

	int_map[z][x][y] = type;
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

void map::setSnakeHead_Dir(int Dir)
{
	SnakeHead_Dir = Dir ;
}

void map::setSnakeHead(snake* Head){
	SnakeHead=Head;
}

void map::setSnakeTail(snake* Tail){
	SnakeTail=Tail;
}

int* map::get_whole_int_map()
{
	return &int_map[0][0][0];
}

int map::get_camera(){
	return getSnakeHead()->getZ();
}

void map::set_upside(int upside){
	this->upside=upside;
}

int map::get_upside(){
	return upside;
}
