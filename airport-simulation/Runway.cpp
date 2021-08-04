#include <thread>
#include "Runway.h"
#include "variables.h"
#include "utils.h"

std::atomic<int> runway1Plane;
std::atomic<int> runway2Plane;
std::atomic<int> runway3Plane;

std::mutex runway1Working;
std::mutex runway2Working;
std::mutex runway3Working;

std::queue<int> landedList;
std::queue<int> startedList;

//std::condition_variable cv;

void Runway::init() {
    //busy= true;
    runway1Plane=-1;
    runway2Plane=-1;
    runway3Plane=-1;
    runwayWorking();
}

void Runway::runwayWorking() {
    while(true){
            std::unique_lock<std::mutex> lock1 (runway1Working);
            if((!landedList.empty() && utils::generateRandomInt(1,10) > 7 )|| landedList.size()>=AIRPORT_PLACES_LIMIT){
                int tmpPlaneId = landedList.front();
                landedList.pop();
                runway1Plane = tmpPlaneId;
                startedList.push(tmpPlaneId);
                std::this_thread::sleep_for(std::chrono::milliseconds(utils::generateRandomInt(2000,4000)));
                planes[tmpPlaneId].setLocation(3, 3);
                }

              else if (!waitQueue.empty()) {
                int tmpPlaneId = waitQueue.front();
                waitQueue.pop();
                runway1Plane = tmpPlaneId;
                std::this_thread::sleep_for(std::chrono::milliseconds(utils::generateRandomInt(3700, 4200)));
                planes[tmpPlaneId].setLocation(2, 2);
                landedList.push(tmpPlaneId);
            }

            runway1Plane = -1;
            lock1.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(150));

            std::unique_lock<std::mutex> lock2 (runway2Working);

            if((!landedList.empty() && utils::generateRandomInt(1,10) > 7) || landedList.size()>=AIRPORT_PLACES_LIMIT){
                int tmpPlaneId = landedList.front();
                landedList.pop();
                runway2Plane = tmpPlaneId;
                startedList.push(tmpPlaneId);
                std::this_thread::sleep_for(std::chrono::milliseconds(utils::generateRandomInt(2000,4000)));
                planes[tmpPlaneId].setLocation(3, 3);
                }

              else if (!waitQueue.empty()) {
                int tmpPlaneId = waitQueue.front();

                waitQueue.pop();
                runway2Plane = tmpPlaneId;
                std::this_thread::sleep_for(std::chrono::milliseconds(utils::generateRandomInt(4200, 4500)));
                planes[tmpPlaneId].setLocation(2, 2);
                landedList.push(tmpPlaneId);
            }

            runway2Plane = -1;
            lock2.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(150));

            std::unique_lock<std::mutex> lock3 (runway3Working);

            if((!landedList.empty() && utils::generateRandomInt(1,10) > 7)|| landedList.size()>=AIRPORT_PLACES_LIMIT) {
                int tmpPlaneId = landedList.front();
                landedList.pop();
                runway3Plane = tmpPlaneId;
                startedList.push(tmpPlaneId);
                std::this_thread::sleep_for(std::chrono::milliseconds(utils::generateRandomInt(2000, 4000)));
                planes[tmpPlaneId].setLocation(3, 3);
                }

              else if (!waitQueue.empty()) {
                int tmpPlaneId = waitQueue.front();
                waitQueue.pop();
                runway3Plane = tmpPlaneId;
                std::this_thread::sleep_for(std::chrono::milliseconds(utils::generateRandomInt(4500, 4800)));

                planes[tmpPlaneId].setLocation(2, 2);
                landedList.push(tmpPlaneId);
            }
            runway3Plane = -1;
            lock3.unlock();
    }
}
