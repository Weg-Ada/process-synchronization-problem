# Process Synchronization Problem

The projects were created in order to learn the rules of creating multithreaded programs in ``C ++ 11``.

The project is divided into 3 sub-projects:
1. The problem of dining philosophers [dining-philosophers-problem](https://github.com/Weg-Ada/process-synchronization-problem/tree/master/dining-philosophers-problem)
2. The problem of dining philosophers with the ncurses library [dining-philosophers-problem-ncurses](https://github.com/Weg-Ada/process-synchronization-problem/tree/master/dining-philosophers-problem-ncurses)
3. Airport simulation (based on the philosophers' problem) [airport-simulation](https://github.com/Weg-Ada/process-synchronization-problem/tree/master/airport-simulation)

## Dining philosophers problem

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.

Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher at a time and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can only take the fork on their right or the one on their left as they become available and they cannot start eating before getting both forks.

Eating is not limited by the remaining amounts of spaghetti or stomach space; an infinite supply and an infinite demand are assumed.

The problem is how to design a discipline of behavior (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.

Source of [Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## Dining philosophers problem (ncurses)

ncurses (new curses) - a programming library for building GUI-style applications that runs in a terminal emulator.

You need to install ncurses library

Packages:
* ``libncurses5-dev``
* ``libncursesw5-dev``

Command to install:

```
sudo apt-get install libncurses5-dev libncursesw5-dev
```

## Airport simulation

The airport simulation project is based on the problem of dining philosophers.

Project assumptions:

* Each airplane is a separate thread. Airplanes take off and land (signaling readiness) at random times. Only one take-off / landing can take place on one runway at a time (only one airplane on one runway). There is a queue of planes at the parking stands.
* Landing is carried out according to the priority of the queue. Landing has a higher priority than take off. Unable to land if there is no space on the plate.
* The plane ready to take off checks if it can take off. If the runway is free and no aircraft is landing within this time, it may take off. Then it automatically frees up space.
* The plane ready for landing checks if there is any free space at the airport. If there is room and the runway is free, it can land. Then it automatically takes its place.
* Taxiing of planes takes place automatically, i.e. if the plane is ready, it can take off immediately, provided the runway is free.
* There is a limit to the maximum number of airplanes and the number of tarmac parking spaces.
