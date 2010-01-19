#ifndef DISPLAY_H
#define DISPLAY_H
#include "setting/setting.h"
#include "point.h"
#include "map.h"
void ham_PutLine(point* a,point* b,int c);
class display_controller{
    private:
		double theta;
		bool rotating;
        map *data;
        int fps;
        int r_direction;
        int count;
        int lastbuffer;
        int block_size;
        int p_size;
        int distance;
        int top;
        int left;
        void (*unlock_fp)(void);
    public:
        bool refresh();
        /*
        function refresh
        params:
          data:
            map data
        */
        bool refresh(map * data);
        /*
        function refresh
        params:
          data:
            map data
          unlock:
            unlock function
        */
        void print_dot(int x,int y,int type);
        void rotate();
        bool refresh(map * data, void (*unlock)() );
        void PutLine(point* a,point* b,int c);
        void int_handler();
        display_controller(map* data=new map, int fps=26);
};


#endif
