#ifndef SO2PROJ3V2_VARIABLES_H
#define SO2PROJ3V2_VARIABLES_H

#include <condition_variable>
#include <list>
#include <atomic>
#include <queue>
#include "Plane.h"

extern std::atomic<int> runway1Plane;
extern std::atomic<int> runway2Plane;
extern std::atomic<int> runway3Plane;

extern Plane *planes;
extern std::queue<int> waitQueue;
//auto cmp = [](int left, int right) { return (planes[left].getPriority() ^ 1) < (planes[right].getPriority() ^ 1);};
//extern std::priority_queue<int, std::queue<int>, decltype(cmp) > waitQueue(cmp);
extern std::queue<int> landedList;
extern std::queue<int> startedList;

//mutex declaration
extern std::mutex runway1Working;
extern std::mutex runway2Working;
extern std::mutex runway3Working;
extern std::mutex mutexPrint;

//const
const int NUMBER_OF_PLANES = 20;
const int LANDING_QUEUE_LIMIT = 20;
const int AIRPORT_PLACES_LIMIT = 6;

#endif //SO2PROJ3V2_VARIABLES_H
