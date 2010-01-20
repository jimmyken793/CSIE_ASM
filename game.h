#ifndef GAME_H
#define GAME_H
#include "setting/setting.h"
#include "display.h"
#include "snake.h"
#include "map.h"


class game{
	public:
		void unlock();
		void int_handler();		// timer;
		game(display_controller *display);
		~game();
	private:
		map* _game_map;
		
		int NextApple_x;	//record the next apple's position;
		int NextApple_y;
		int NextApple_z;
			
		int count;
		int _Dir_flag;
		display_controller* display;
		
		int _side_now;	// the index of the current side;
		int _upside;	// the index of the upside;
		int _downside;	// the index of the downside;
		int _leftside;	// the index of the leftside;
		int _rightside;	// the index of the rightside;
		int _backside;  // the index of the backside;
		int _index[6];
		int Next_head_x;//record the next snakehead;
		int Next_head_y;
		int Next_head_z;
		
	
		void game::createApple();
		void checkApple(int pos_z, int pos_x, int pos_y);	
		void appleWalk();
		void updateAppleWalk(int z, int x, int y, snake* tmpS);
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
		void update_pos(int z,int x,int y);
		void snakeWalk();
		// update the snake's Head and Tail, and also update the map ;
		void updateSnake(int z,int x,int y, snake* tmpS);
		void setNewSide(int a);
		void coordinate(int nowside,int nextside,int x,int y);
};

#endif
