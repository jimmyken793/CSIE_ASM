#include "map.h"

map::map(){
	//this->int_map=new int[6][M_SIZE][M_SIZE];	//create the map;
	for(int i=0;i<6;i++)	//z
	{
		for(int j=0;j<M_SIZE;j++)	//x
		{
			for(int k=0;k<M_SIZE;k++)	//y
			    int_map[i][j][k]=0;
		}
	}
}

map::~map(){
}

void map::clear(){
	for(int i=0;i<6;i++){
		for(int j=0;j<M_SIZE;j++){
			for(int k=0;k<M_SIZE;k++)	//y
			    int_map[i][j][k]=0;
		}
	}
}

int map::get_int_map(int z, int x, int y){
	return int_map[z][x][y];
}

void map::set_int_map(int z, int x, int y, int type)
{
	int_map[z][x][y] = type;
}

int* map::get_whole_int_map()
{
	return &int_map[0][0][0];
}
