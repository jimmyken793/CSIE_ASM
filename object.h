#ifndef OBJECT_H
#define OBJECT_H
#include "map.h"
class object{
	private:
		int x,y,z;
		int type;
		map *_map;
	public:
		object(int x,int y,int z,int type,map* _map);
		int getx();
		int gety();
		int getz();
		int gettype();
		void setx(int x);
		void sety(int y);
		void setz(int y);
		void settype(int type);
		void setpos(int x,int y,int z);
};

#endif
