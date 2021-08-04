#include <sstream>
#include "Picture.h"
#include "variables.h"
#include "PlanesGroup.h"


std::mutex mutexPrint;

void Picture::draw() {
    int win_size_x;
    int win_size_y;
    int runway_window_size = 3;

    initscr();
    noecho();
    curs_set(FALSE);
    getmaxyx(stdscr, win_size_y, win_size_x);


    WINDOW *airspace = newwin(win_size_y - (runway_window_size*3), win_size_x / 3, 0, 0);
    WINDOW *airport = newwin(win_size_y - (runway_window_size*3), (win_size_x / 3), 0, win_size_x / 3);
    WINDOW *airspaceStarted = newwin(win_size_y - (runway_window_size*3), win_size_x / 3, 0, (win_size_x / 3 * 2));

    WINDOW *runway = newwin(runway_window_size, win_size_x, win_size_y - (runway_window_size*3), 0);
    WINDOW *runway2 = newwin(runway_window_size, win_size_x, win_size_y - (runway_window_size*2), 0);
    WINDOW *runway3 = newwin(runway_window_size, win_size_x, win_size_y - (runway_window_size), 0);

    draw_borders(airspace);
    draw_borders(airport);
    draw_borders(airspaceStarted);

    draw_borders(runway);
    draw_borders(runway2);
    draw_borders(runway3);

    int airspace_x = 1, airspace_y = 1;
    int airport_x = 1, airport_y = 1;
    int runway_x = 1, runway_y = 1;
    int airspaceStarted_x = 1, airspaceStarted_y = 1;

    std::stringstream ss;
    ss << "Airspace (landing queue)"; //(LIMIT: " << LANDING_QUEUE_LIMIT << "): ";
    const std::string tmp = ss.str();
    const char *airspaceStatus = tmp.c_str();
    mvwprintw(airspace, airspace_y, airspace_x, airspaceStatus);


    std::stringstream ss2;
    ss2 << "Airport (LIMIT: " << AIRPORT_PLACES_LIMIT << "): ";
    const std::string tmp2 = ss2.str();
    const char *airportStatus = tmp2.c_str();
    mvwprintw(airport, airport_y, airport_x, airportStatus);
    airport_y++;

    std::stringstream ss3;
    ss3 << "Started"; //(LIMIT: " << NUMBER_OF_PLANES << "): ";
    const std::string tmp3 = ss3.str();
    const char *airspaceStartedStatus = tmp3.c_str();
    mvwprintw(airspaceStarted, airspaceStarted_y, airspaceStarted_x, airspaceStartedStatus);
    airspaceStarted_y++;

    mvwprintw(runway, runway_y, runway_x, "                                                                      ");
    mvwprintw(runway, runway_y, runway_x, "Runway1: Current plane:");

    mvwprintw(runway2, runway_y, runway_x, "                                                                     ");
    mvwprintw(runway2, runway_y, runway_x, "Runway2: Current plane:");

    mvwprintw(runway3, runway_y, runway_x, "                                                                     ");
    mvwprintw(runway3, runway_y, runway_x, "Runway3: Current plane:");

    while(true) {
        wrefresh(airspace);
        wrefresh(airport);
        wrefresh(airspaceStarted);
        wrefresh(runway);
        wrefresh(runway2);
        wrefresh(runway3);
        std::stringstream ss1;
        if(runway1Plane == -1){
            ss1 << " Runway1: Waiting";
        } else {
            ss1 << " Runway1: Plane No. " << runway1Plane << " ";
            if (planes[runway1Plane].getLocation() == 1) {
                ss1 << "landing";
            } else if (planes[runway1Plane].getLocation() == 2) {          //2->3 starting
                ss1 << "starting";
            }
        }
        const std::string tmp1 = ss1.str();
        const char *runwaysAndPlanes0 = tmp1.c_str();

        std::stringstream ss2;
        if(runway2Plane == -1){
            ss2 << " Runway2: Waiting";
        } else {
            ss2 << " Runway2: Plane No. " << runway2Plane << " ";
            if (planes[runway2Plane].getLocation() == 1) {
                ss2 << "landing";
            } else if (planes[runway2Plane].getLocation() == 2) {          //2->3 starting
                ss2 << "starting";
            }
        }
        const std::string tmp2 = ss2.str();
        const char *runwaysAndPlanes1 = tmp2.c_str();

        std::stringstream ss3;
        if(runway3Plane == -1){
            ss3 << " Runway3: Waiting";
        } else {
            ss3 << " Runway3: Plane No. " << runway3Plane << " ";
            if (planes[runway3Plane].getLocation() == 1) {
                ss3 << "landing";
            } else if (planes[runway3Plane].getLocation() == 2) {          //2->3 starting
                ss3 << "starting";
            }
        }
        const std::string tmp3 = ss3.str();
        const char *runwaysAndPlanes2 = tmp3.c_str();

        mvwprintw(runway, runway_y, runway_x, "                                                                      ");
        mvwprintw(runway, runway_y, runway_x, runwaysAndPlanes0);

        mvwprintw(runway2, runway_y, runway_x, "                                                                     ");
        mvwprintw(runway2, runway_y, runway_x, runwaysAndPlanes1);

        mvwprintw(runway3, runway_y, runway_x, "                                                                     ");
        mvwprintw(runway3, runway_y, runway_x, runwaysAndPlanes2);

        //WaitList print

        std::unique_lock<std::mutex> lock(mutexPrint);
        //std::priority_queue<int, std::queue<int>, decltype(cmp) > tmpWaitList = waitQueue;
        std::queue<int> tmpWaitList = waitQueue;

        //int siz = waitQueue.size();
        //for(int i =0;i<siz;i++){
            //tmpWaitList.push(waitQueue.top());
            //waitQueue.pop();
        //}

        for(int i =0;i<waitQueue.size();i++){
            std::stringstream ssWait;
            int tmpC = tmpWaitList.front();
            //int tmpC = tmpWaitList.top();

            if(tmpC == 1){

                ssWait << "Plane No. " << planes[tmpWaitList.front()-1].getId();// << " (P: X)";// << planes[0].getPriority();// << ", F: " << planes[0].getFuel() <<")";
//                ssWait << "Plane No. " << planes[tmpWaitList.top()-1].getId() << " (P: X)";// << planes[0].getPriority();// << ", F: " << planes[0].getFuel() <<")";
            } else {
                ssWait << "Plane No. " << planes[tmpWaitList.front()-1].getId();// << " (P: " << planes[tmpC-1].getPriority() << ") ";// << ", F: " << planes[tmpC-1].getFuel() <<")";
//                ssWait << "Plane No. " << planes[tmpWaitList.top()-1].getId() << " (P: " << planes[tmpC-1].getPriority() << ") ";// << ", F: " << planes[tmpC-1].getFuel() <<")";
            }

            const std::string tmpWait = ssWait.str();
            const char *tmpWaitStatus = tmpWait.c_str();
            airspace_y++;
            mvwprintw(airspace, airspace_y, airspace_x, "                       ");
            mvwprintw(airspace, airspace_y, airspace_x, tmpWaitStatus);

            tmpWaitList.pop();
        }
        mvwprintw(airspace, airspace_y+1, airspace_x, "                           ");
        mvwprintw(airspace, airspace_y+2, airspace_x, "                           ");
        mvwprintw(airspace, airspace_y+3, airspace_x, "                           ");
        mvwprintw(airspace, airspace_y+4, airspace_x, "                           ");
        airspace_y = 1;
        lock.unlock();

        //LandedList print

        std::queue<int>tmpLandedList = landedList;
        for(int i =0;i<landedList.size();i++){
            std::stringstream ssWait;
            ssWait << "Plane No. " << tmpLandedList.front();// << " (P: " << planes[tmpLandedList.front()-1].getPriority() << ")";
            const std::string tmpWait = ssWait.str();
            const char *tmpLandedStatus = tmpWait.c_str();
            airport_y++;
            mvwprintw(airport, airport_y, airport_x, "                                         ");
            mvwprintw(airport, airport_y, airport_x, tmpLandedStatus);


            tmpLandedList.pop();

        }
        mvwprintw(airport, airport_y+1, airport_x, "                           ");
        mvwprintw(airport, airport_y+2, airport_x, "                           ");
        mvwprintw(airport, airport_y+3, airport_x, "                           ");
        mvwprintw(airport, airport_y+4, airport_x, "                           ");
        airport_y = 1;

        //StartedList print
        int tmpCounter = 0;
        std::queue<int>tmpStartedQ;
        for(int i =0;i<NUMBER_OF_PLANES;i++){
            if(planes[i].getLocation() == 3){

                tmpCounter++;
                tmpStartedQ.push(planes[i].getId());
            }
        }

//        tmpStartedQ = startedList;

        for(int i =0;i<tmpCounter;i++){
            std::stringstream ssWait;
            ssWait << "Plane No. " << tmpStartedQ.front()-1;// << " (P: " << planes[tmpStartedQ.front()-1].getPriority() << ")";
            const std::string tmpWait = ssWait.str();
            const char *tmpStartedStatus = tmpWait.c_str();
            airspaceStarted_y++;
            mvwprintw(airspaceStarted, airspaceStarted_y, airspaceStarted_x, "                                         ");
            mvwprintw(airspaceStarted, airspaceStarted_y, airspaceStarted_x, tmpStartedStatus);

            tmpStartedQ.pop();
        }
        mvwprintw(airspaceStarted, airspaceStarted_y+1, airspaceStarted_x, "                           ");
        mvwprintw(airspaceStarted, airspaceStarted_y+2, airspaceStarted_x, "                           ");
        mvwprintw(airspaceStarted, airspaceStarted_y+3, airspaceStarted_x, "                           ");
        mvwprintw(airspaceStarted, airspaceStarted_y+4, airspaceStarted_x, "                           ");
        airspaceStarted_y = 1;

    }

    delwin(airspace);
    delwin(airport);
    delwin(airspaceStarted);
    delwin(runway);
    delwin(runway2);
    delwin(runway3);

    clear();
    endwin();

}

void Picture::draw_borders(WINDOW *screen) {
    int x, y, i;
    getmaxyx(screen, y, x);
    // 4 corners
    mvwprintw(screen, 0, 0, "+");
    mvwprintw(screen, y - 1 , 0, "+");
    mvwprintw(screen, 0, x - 1, "+");
    mvwprintw(screen, y - 1 , x - 1, "+");
    // sides
    //for (i = 1; i < (y - 1); i++) {
        //mvwprintw(screen, i, 0, "|");
        //mvwprintw(screen, i, x - 1, "|");
    //}
    //}
    // top and bottom
    for (i = 1; i < (x - 1); i++) {
        mvwprintw(screen, 0, i, "-");
        mvwprintw(screen, y - 1, i, "-");
    }
    clear();
    endwin();
}
