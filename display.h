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
		int f_relation[6][4];
		int s_relation[6][4];
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
        void print_dot(int x,int y,point *origin,point *ax,point *ay,int r_direction,int mode,int type);
        void print_dot1(int x,int y,point *origin,point *ax,point *ay,int r_direction,int mode,int type);
        void rotate();
		int get_f_r(int z,int side);
		int get_s_r(int z,int side);
        bool refresh(map * data, game* Game,int r_direction);
        void PutLine(point* a,point* b,int c);
        void int_handler();
        display_controller(map* data=0, int fps=26);
};


#endif
