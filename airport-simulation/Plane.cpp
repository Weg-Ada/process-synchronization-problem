#include <thread>
#include "Plane.h"
#include "variables.h"
#include "utils.h"

std::queue<int> waitQueue;

void Plane::run() {
    waitOrLeave();

    while (true){
        if(planes[this->Id].getLocation() == 3){
            std::this_thread::sleep_for(std::chrono::milliseconds(utils::generateRandomInt(4000,10000)));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            planes[this->Id].setLocation(1,1);
            waitInQueue();
        }
    }
}

void Plane::waitOrLeave() {
    if (waitQueue.size() >= LANDING_QUEUE_LIMIT) {
        leave();
    } else {
        waitInQueue();
    }
}

void Plane::leave() {
}

void Plane::waitInQueue() {
      waitQueue.push(this->getId()); //push plane in wait list
}

int Plane::getLocation() const {
    return location;
}

void Plane::setLocation(int location_current, int location_destination) {
    Plane::location = location_current;
}

int Plane::getId() const {
    return Id;
}

void Plane::setId(int Id) {
    Plane::Id = Id;
}

void Plane::setPriority(int priority) {
    Plane::priority = priority;
}

int Plane::getPriority() const {
    return priority;
}

Plane::~Plane() {
}

int Plane::getFuel() const {
    return fuel;
}

void Plane::setFuel(int fuel) {
    Plane::fuel = fuel;
}
