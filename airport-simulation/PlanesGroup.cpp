#include <chrono>
#include <thread>
#include "PlanesGroup.h"
#include "variables.h"
#include "utils.h"

std::thread planeThreads[NUMBER_OF_PLANES];
Plane * planes = new Plane[NUMBER_OF_PLANES];

void PlanesGroup::generateNewPlanesGroup() {
    for(int i = 0;i<NUMBER_OF_PLANES;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        Plane plane;

        planeThreads[i] = std::thread(&Plane::run, plane); //generates thread i

        plane.setId(i+1);
        plane.setLocation(1,1);
        int tmpF = utils::generateRandomInt(1,100);
        plane.setFuel(tmpF);
        if(tmpF<30){
            plane.setPriority(2);
        } else {
            plane.setPriority(1);
        }

        planes[i] = plane;
    }
}
