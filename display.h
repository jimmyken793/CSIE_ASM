#ifndef DISPLAY_H
#define DISPLAY_H
#include "setting/setting.h"
#include "map.h"

class display_controller{
    private:
        map *data;
        int fps;
        double rotation;
        int r_direction;
        int count;
        int lastbuffer;
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
        bool refresh(map * data, void (*unlock)() );
        void int_handler();
        display_controller(map* data=new map, int fps=26);
};


#endif
