#include "setting/setting.h"

class block{
	public:
		block(int type=0);
		void setSpriteType(size_t type);
		size_t getSpriteType();
	private:
		size_t sprite_type;	// blank = 0; apple = 1; snakehead = 2; snakebody = 3;
		// barrier = 4;
};

class snake : public block{
	public:
		snake(int z, int x, int y);
		~snake();
		int getX();
		int getY();
		int getZ();
		void setChild(snake* node);
		void setParent(snake* node);
	private:
		int snake_x;
		int snake_y;
		int snake_z;
		snake* child;
		snake* parent;
};
class map{
	public:
		map();
		~map();
		snake* getSnakeHead();
		snake* getSnakeTail();
		int getSnakeHead_Dir();
		int getSnakeSizeNow();
		block getGmap(int z, int x, int y);
		void setSnakeHead(snake* Head);
		void setSnakeTail(snake* Tail);
	private:
		int NextApple_x;	//record the next apple's position;
		int NextApple_y;
		int NextApple_Z;
		snake* SnakeHead;
		snake* SnakeTail;
		int SnakeHead_Dir;	// record the direction of the snake's head now;
		// up = 1; down = 2; left = 3; right = 4 ;
		block gmap[6][M_SIZE][M_SIZE];//elements that construct the whole map;
		//		 z	x		y
		int snakeSizeNow;
		int int_map[6][M_SIZE][M_SIZE];
};
class game{
	public:
		void unlock();
		void int_handler();		// timer;
	private:
		map _game_map;
		int _side_now;	// the index of the current side;
		int _upside;	// the index of the upside;
		int _downside;	// the index of the downside;
		int _leftside;	// the index of the leftside;
		int _rightside;	// the index of the rightside;
		int _M_SIZE;
		// check game over or not;
		bool bomb(int pos_z,int pos_x,int pos_y);
		// return 0 if is not at boundary;
		// return the direction of the boundary encountered;
		// up = 1; down = 2; left = 3; right = 4;
		int checkBoundary(int pos_z,int pos_x,int pos_y) 	;
		// return the direction that user input;
		int changeDir(int current_Dir);
		// control the move of the snake;
		// create a new SnakeHead, delete the Snaketail and update them;
		void snakeWalk();
		// update the snake's Head and Tail, and also update the map ;
		void updateSnake(snake* tmpS);
};

