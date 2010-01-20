#ifndef SNAKE_H
#define SNAKE_H

#include "setting/setting.h"
class snake{
	public:
		snake(int z, int x, int y);
		~snake();
		int getX();
		int getY();
		int getZ();
		snake* getChild();
		snake* getParent();
		void setChild(snake* node);
		void setParent(snake* node);
		void setSnakeSize(int value);
	private:
		int snake_x;
		int snake_y;
		int snake_z;
		snake* child;
		snake* parent;
};
#endif
