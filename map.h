#ifndef MAP_H
#define MAP_H

#include "setting/setting.h"

class map{
	public:
		map();
		~map();
		int getSnakeHead_Dir();
		int getSnakeSizeNow();
		int get_int_map(int z, int x, int y);
		void setSnakeHead_Dir(int Dir);
		void set_int_map(int z, int x, int y, int type);
		void setSnakeSize(int value);
		int* get_whole_int_map();
		void clear();
	private:
		//elements that construct the whole map;
		// blank = 0; apple = 1; snakeHead = 2; snakeBody = 3; barrier = 4;
		int int_map[6][M_SIZE][M_SIZE];
		//		    z	 x		 y
};

#endif
