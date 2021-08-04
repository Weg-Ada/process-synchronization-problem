#include <array>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <random>
#include <iomanip>

using namespace std;
 
const int number_philosophers = 5;
 
struct table
{
   bool set {false};
};
 
struct philosopher
{
private:
   string  const name;
   table   const & dinnertable;
   thread  lifethread;
public:
   philosopher (string const & n, table const & t) :
      name(n), dinnertable(t), lifethread(&philosopher::dinner, this)
   {
   }
 
   ~philosopher()
   {
      lifethread.join();
      cout << "X" << endl;
   }
 
   void dinner()
   {
      while (!dinnertable.set);
 
      do
      {
         think();
         eat();
      } while (dinnertable.set);
   }
 
   void print_text(string const & text)
   {
      cout << name << text << endl;
   }
 
   void eat()
   {
 
      print_text(" start eat");
 
      int stime = (rand() % 6) + 1;
      chrono::milliseconds eat (stime * 150);
      this_thread::sleep_for(eat);
 
      print_text(" finish eat");
   }
 
   void think()
   {
      int stime = (rand() % 6) + 1;
      chrono::milliseconds think (stime * 150);
      this_thread::sleep_for(think);
 
      print_text(" think");
   }
};
 
void dinner()
{
   chrono::seconds ready (1);
   this_thread::sleep_for(ready);
   cout << "Dinner started!" << endl;
 
   {
      table table;
      array <philosopher, number_philosophers> philosophers
      {
         {
            { "Philosopher 1", table },
            { "Philosopher 2", table },
            { "Philosopher 3", table },
            { "Philosopher 4", table },
            { "Philosopher 5", table },
         }
      };
 
      table.set = true;
      chrono::seconds duration (10);
      this_thread::sleep_for(duration);
      table.set = false;
   }
 
   cout << "Dinner finished!" << endl;
}
 
int main()
{   
   dinner();
 
   return 0;
}