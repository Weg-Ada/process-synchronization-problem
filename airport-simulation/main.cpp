#include <iostream>
#include <thread>
#include <condition_variable>
#include "Picture.h"
#include "Plane.h"
#include "Runway.h"
#include "PlanesGroup.h"

int main() {

    Picture draw;
    PlanesGroup planes;

    Runway runway1;
    Runway runway2;
    Runway runway3;


    std::thread drawThread(&Picture::draw, draw);
    std::thread planesThread(&PlanesGroup::generateNewPlanesGroup, planes);

    std::thread runway1Thread(&Runway::init, runway1);
    std::thread runway2Thread(&Runway::init, runway2);
    std::thread runway3Thread(&Runway::init, runway3);


    drawThread.join();
    planesThread.join();
    runway1Thread.join();
    runway2Thread.join();
    runway3Thread.join();

    return 0;
}
