#include "map.h"
#include <mygba.h>
map::map(game* Game){
	this->Game=Game;
	clear();
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
	upside=0;
	camera=0;
}

map::~map(){
}

void map::clear(){
	for(int i=0;i<6;i++){
		for(int j=0;j<M_SIZE;j++){
			for(int k=0;k<M_SIZE;k++){
				int_map[i][j][k]=0;
			}
		}
	}
}

int map::get_f_r(int z,int side){
	return f_relation[z][side];
}

int map::get_s_r(int z,int side){
	return s_relation[z][side];
}

int map::get_int_map(int z, int x, int y){
	return int_map[z][x][y];
}
void map::set_camera(int camera){
	this->camera=camera;
}

int map::get_camera(){
	return camera;
}

void map::set_upside(int upside){
	this->upside=upside;
}

int map::get_upside(){
	return upside;
}

void map::set_int_map(int z, int x, int y, int type){
	int_map[z][x][y] = type;
}

int* map::get_whole_int_map(){
	return &int_map[0][0][0];
}

void map::rotate(int side){
	Game->lock();
	Game->get_display()->refresh(this,Game,(side-upside+4)%4);
	int nu=0;
	switch((side-upside+4)%4){
		case 0:
			nu=(s_relation[camera][side]+2)%4;
		break;
		case 1:
			nu=(s_relation[camera][side]+1)%4;
		break;
		case 2:
			nu=s_relation[camera][side];
		break;
		case 3:
			nu=(s_relation[camera][side]+3)%4;
		break;
	}
	//ham_VBAText("===spin===\nup:%d\tcamera:%d\tside:%d\n",upside,camera,side);
	//ham_VBAText("rotate:%d\n",(side-upside+4)%4);
	//ham_VBAText("s_relation[camera][side]:%d\n",s_relation[camera][side]);
	//ham_VBAText("f_relation[camera][side]:%d\n",f_relation[camera][side]);
	upside=nu;
	camera=f_relation[camera][side];
	//ham_VBAText("up:%d\tcamera:%d\n",upside,camera);
}
