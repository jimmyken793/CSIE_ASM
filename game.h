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
		int count;
		display_controller* display;
		snake* _snake;
};

#endif
