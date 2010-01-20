#ifndef DISPLAY_H
#define DISPLAY_H
#include "setting/setting.h"
#include "point.h"
#include "map.h"
#include "game.h"
class game;
class map;
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
        game* Game;
        bool to_unlock;
        int old_upside;
        int old_camera;
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
        void print_dot(int x,int y,point *origin,point *ax,point *ay,int r_direction,int type);
        void rotate();
        bool refresh(map * data, game* Game,int r_direction);
        void PutLine(point* a,point* b,int c);
        void int_handler();
        display_controller(map* data=0, int fps=26);
};


#endif
