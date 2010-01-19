#ifndef MAP_H
#define MAP_H

#include "setting/setting.h"
#include "game.h"
class game;
class map{
	public:
		map(game* Game);
		~map();
		int get_int_map(int z, int x, int y);
		void set_int_map(int z, int x, int y, int type);
		int* get_whole_int_map();
		void clear();
		int get_f_r(int z,int side);
		int get_s_r(int z,int side);
		void set_camera(int camera);
		int get_camera();
		void set_upside(int upside);
		int get_upside();
		void rotate(int side);
	private:
		//elements that construct the whole map;
		// blank = 0; apple = 1; snakeHead = 2; snakeBody = 3; barrier = 4;
		int int_map[6][M_SIZE][M_SIZE];
		int camera;
		int upside;
		int f_relation[6][4];
		int s_relation[6][4];
		game* Game;
		//		    z	 x		 y
};

#endif
