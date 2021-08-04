#ifndef SO2PROJ3V2_RUNWAY_H
#define SO2PROJ3V2_RUNWAY_H

class Runway {

public:
    int planeId;
    bool busy = false;
    void init();
    void runwayWorking();
};

#endif //SO2PROJ3V2_RUNWAY_H
