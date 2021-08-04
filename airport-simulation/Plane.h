#ifndef SO2PROJ3V2_PLANE_H
#define SO2PROJ3V2_PLANE_H

class Plane {
private:
    int location; //0 - nothing, 1 - airspace, 2 - airport, 3 - started
    int Id;
    int priority = 0; //0 - default, 1 - low, 2 - high
    int fuel = 100; // from 0 to 100

public:

    int getPriority() const;
    void setPriority(int priority);

    int getFuel() const;
    void setFuel(int fuel);

    int getLocation() const;

    void setLocation(int location_current, int location_destination);

    int getId() const;

    void setId(int Id);

    void waitOrLeave(); // plane can decide
    void leave();
    void waitInQueue();
    void run();

    Plane() = default;
    ~Plane();
};

#endif //SO2PROJ3V2_PLANE_H
