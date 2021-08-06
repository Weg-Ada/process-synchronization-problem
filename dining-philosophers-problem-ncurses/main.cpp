    #include <array>
    #include <thread>
    #include <chrono>
    #include <iostream>
    #include <string>
    #include <string.h>
    #include <random>
    #include <iomanip>
    #include <time.h>
    #include <mutex>
    #include <ncurses.h>
    #include <stdlib.h>
    #include <ctime>
    #include <sstream>
     
    using namespace std;
    
    mutex wait;
    const int number_philosophers = 5; 

    int block(void) {
	    int signal = getch();
	    if (signal == 32)
	    {
		    ungetch(signal);
		    return 1;
	    }
	    else return 0;
    }

    struct fork
    {
	   std::mutex mutex;
    };

    class philosopher
    {
        public:
	        string name;
	        bool dinnertable;
            int position;
            int i;
	        fork& left_fork;
	        fork& right_fork;
	        thread lifethread;

	        // constructor - thread starts after an object of this class is created
	        philosopher(string  n, bool t, int p , int j, fork & l, fork & r) :
		        name(n), dinnertable(t), position(p) , i(j), left_fork(l), right_fork(r), lifethread(&philosopher::dine, this)
	        {
	        }
	        ~philosopher()
	        {
		        lifethread.join();
	        }
 
        void dine()
	    {
            int i=0;
		    while (dinnertable == true)
		    {
               i++;
			   i = think(i);
			   i = eat(i);
            };             
	    }

	    void print(string text, string progress)
	    {
		    lock_guard<std::mutex> cout_lock(wait);
            string write = text +"\n";

            attron(COLOR_PAIR(4));
            attron(A_BOLD);
            
            if (text == "think" )
            {
                attron(COLOR_PAIR(1));
            }
            else if (text == "finish eat" )
            {
                attron(COLOR_PAIR(3));
            }
            else if (text == "start eat")
            {
                attron(COLOR_PAIR(2));
            }
            
            mvprintw(position,(2), name.c_str() );
            mvprintw(position,(16), write.c_str() );

            
            if(text == "start eat")
            {

                   if (name == "Philosopher 1" )
                   {
                       mvprintw(position,(60), "no.1" );
                       mvprintw(position,(65), "no.2" );
                   }
                   else if (name == "Philosopher 2" )
                   {
                       mvprintw(position,(60), "no.2" );
                       mvprintw(position,(65), "no.3" );
                   }
                   else if (name =="Philosopher 3")
                   {
                       mvprintw(position,(60), "no.3" );
                       mvprintw(position,(65), "no.4" );
                   }         
                   else if (name =="Philosopher 4")
                   {
                       mvprintw(position,(60), "no.4" );
                       mvprintw(position,(65), "no.5" );
                   } 
                   else if (name =="Philosopher 5")
                   {
                       mvprintw(position,(60), "no.5" );
                       mvprintw(position,(65), "no.1" );
                   } 
            }
            mvprintw(position,(30), progress.c_str() );

            refresh();
	    }

	    int think(int i) // put the thread to sleep
	    {
		    string progress="|";
            for(int i=0; i<20; i++)
             {
                print("think",  progress);
                this_thread::sleep_for(chrono::milliseconds(100));
                progress=progress+"|";
             }

            progress="Waiting!";
            print("think", progress);
            progress="";
            if(i==10)
            {
               print("DEAD!!!", progress);
               lifethread.join();
            }            
            return i;
	    }

	    int eat(int i) // put the thread to sleep
	    {
		    lock(left_fork.mutex, right_fork.mutex);

            /*Left and right forks are granted to the philosopher non-deadlock with a lock. After the forks are obtained, i.e. mutexes, 
            their ownership is transferred to the lock_guard object, thanks to which the mutexes will be properly released when the function returns*/

		    lock_guard<std::mutex> left_lock(left_fork.mutex, std::adopt_lock);
		    lock_guard<std::mutex> right_lock(right_fork.mutex, std::adopt_lock);
            string progress = "|";
            
            for(int i=0; i<20; i++)
            {
                print("start eat", progress);
                this_thread::sleep_for(chrono::milliseconds(100));
                progress=progress+"|";
            }
	
		    progress="";
            for(int i=0; i<20; i++)
            {
                print("finish eat", progress);
                this_thread::sleep_for(chrono::milliseconds(40));
                progress=progress+"|";
            }
            progress="";
            return 0;     
	    }

    };

    void dinner()
    {

	    array<fork, number_philosophers> forks;

	    array<philosopher, number_philosophers> philosophers
	    {
		    {
			    { "Philosopher 1", true, 6 , 0, forks[0], forks[1] },
			    { "Philosopher 2", true, 8 , 0 ,forks[1], forks[2] },
			    { "Philosopher 3", true, 10 , 0 ,forks[2], forks[3] },
			    { "Philosopher 4", true, 12 , 0 ,forks[3], forks[4] },
			    { "Philosopher 5", true, 14 , 0 ,forks[4], forks[0] },
		    }
	    };

        if(block())
        {
            for(int i=0; i<5; i++)
            philosophers[i].dinnertable = false;
        }

        attron(COLOR_PAIR(4));
        mvprintw(18,(10), "End! \n" );

    }

    int main()
    {
        initscr();
        noecho(); 
        start_color();

        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        init_pair(4, COLOR_WHITE, COLOR_BLACK);

        mvprintw(3,(35), "Progress \n" );
        mvprintw(3,(62), "Forks \n" );

        mvprintw(6,(2), "Philosopher 1" );
        mvprintw(8,(2), "Philosopher 2" );
        mvprintw(10,(2), "Philosopher 3" );
        mvprintw(12,(2), "Philosopher 4" );
        mvprintw(14,(2), "Philosopher 5" );

        refresh();
	    dinner();
        endwin();

	    return 0;
    }