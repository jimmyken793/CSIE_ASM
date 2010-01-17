#ifndef DISPLAY_H
#define DISPLAY_H
#include "setting/setting.h"

class display_data{
    private:
		int current,target;
		int map[6][M_SIZE][M_SIZE];
    public:
        display_data();
        display_data(int (*newmap)[6][M_SIZE][M_SIZE],int current,int target);
        display_data(int (*newmap)[6][M_SIZE][M_SIZE]);
};
class display_controller{
    private:
        display_data* data;
        int fps;
        double rotation;
        int r_direction;
        int count;
        int lastbuffer;
    public:
        bool refresh();
        /*
        function refresh
        params:
          data:
            map data
        */
        bool refresh(display_data * data);
        /*
        function refresh
        params:
          data:
            map data
          unlock:
            unlock function
        */
        bool refresh(display_data * data, void (*unlock)() );
        void int_handler();
        display_controller(display_data* data=new display_data, int fps=26);
};


#endif
