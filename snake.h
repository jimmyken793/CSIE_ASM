#ifndef SNAKE_H
#define SNAKE_H
#include "setting/setting.h"
#include "object.h"
#include "map.h"
class object;
class snake{
	public:
		snake(int z, int x, int y,map* _map);
		~snake();
		void move();
		void set_direction(int dx,int dy);
		int getdx();
		int getdy();
		void add_head(int x,int y,int z);
		void add_tail(int x,int y,int z);
		void add_head(object *obj);
		object *remove_tail();
	private:
		map* _map;
		int maximum;
		int x;
		int y;
		int z;
		int dx;
		int dy;
		int direction;
		object *body[M_SIZE*M_SIZE*6];
		int head,tail;
};
#endif
