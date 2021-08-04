#ifndef SO2PROJ3V2_PICTURE_H
#define SO2PROJ3V2_PICTURE_H

#include <ncurses.h>

class Picture {
private:

    void draw_borders(WINDOW *screen);

public:
    void draw();
};

#endif //SO2PROJ3V2_PICTURE_H
