	#ifndef MAP_H
#define MAP_H

#include "setting/setting.h"
#include "snake.h"

class map{
	public:
		map();
		~map();
		snake* getSnakeHead();
		snake* getSnakeTail();
		int getSnakeHead_Dir();
		int getSnakeSizeNow();
		int get_int_map(int z, int x, int y);
		void setSnakeHead(snake* Head);
		void setSnakeTail(snake* Tail);
		void setSnakeHead_Dir(int Dir);
		void set_int_map(int z, int x, int y, int type);
		void setSnakeSize(int value);
		int* get_whole_int_map();
		
	private:
		
		snake* SnakeHead;
		snake* SnakeTail;
		int SnakeHead_Dir;	// record the direction of the snake's head now;
		// up = 1; down = 2; left = 3; right = 4 ;
		
		//elements that construct the whole map;
		// blank = 0; apple = 1; snakeHead = 2; snakeBody = 3; barrier = 4;
		int int_map[6][M_SIZE][M_SIZE];
		//		    z	 x		 y
		int snakeSizeNow;
		void init_snake();
};

#endif
