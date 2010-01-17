#include "setting/setting.h"
class display_data{
    private:
        int* map[6][M_SIZE][M_SIZE];
    public:
        display_data();
        display_data(int**** map);
};
class display_controller{
    private:
        display_data* data;
        int fps;
        double rotation;
        int r_direction;
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
        display_controller();
        display_controller(display_data* data);
        display_controller(display_data* data, int fps);
};
