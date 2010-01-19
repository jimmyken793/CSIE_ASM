#ifndef GAME_H
#define GAME_H
#include "setting/setting.h"
#include "display.h"
#include "snake.h"
#include "map.h"
#include "display.h"
class map;
class display_controller;
class snake;
class game{
	public:
		void unlock();
		void int_handler();		// timer;
		game(display_controller *display);
		~game();
		void key();
		display_controller* get_display();
		void lock();
	private:
		map* _game_map;
		int prev_key;
		int count;
		bool locked;
		display_controller* display;
		snake* _snake;
};

#endif
