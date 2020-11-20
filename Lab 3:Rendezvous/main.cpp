/*! \mainpage Lab 3 Rendezvous
    \author Ana Griga , Student Number: C00231441
    \date 30.10.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! \class Signal
    \brief An Implementation of a Rendezvous using Semaphores
    Two threads rendezvous at a point of execution, and neither is allowed to proceed until both have arrived.
   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads
*/
/*! Displays a message that is split in to 2 sections to show how a rendezvous works
If Task One arrives first, it waits for Task Two. When Task two arrives, it wakes Task One and might proceed 
immediately to its waitin which case it blocks, allowing Task One to reach its signal, after which both threads can proceed*/

/*! \fn void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay)
    \brief This function will sleep and then will print "Task One has arrived! ", then a rendezvous will point to taskTwo and then will print "Task One has left!"
    \param firstSem - The first semaphore used for flow control, initialized at 0.
    \param secondSem - The second Semaphore used for flow control, initialized at 0.
    \param delay - The int used for number of seconds the thread should sleep. 

    The function will print "Task One has arrived! " before the rendezvous point.
    The function will print "Task One has left!" after the rendezvous point.
    There are several ways to handle the rendezvous. In this case firstSem is signeled and then put secondSem to wait
    and will do the opposite in taskTwo (wait firstSem and signal secondSem)  
*/

void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  firstSem->Signal();
  secondSem->Wait();
  //THIS IS THE RENDEZVOUS POINT!
  std::cout << "Task One has left!"<<std::endl;

}

/*! Displays a message that is split in to 2 sections to show how a rendezvous works*/
/*! \fn taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay)
    \brief This function will sleep and then will print  "Task Two has arrived ", then a rendezvous will point to taskOne and then will print "Task Two has left "
    \param firstSem - The first semaphore used for flow control, initialized to 0.
    \param secondSem - The second Semaphore used for flow control, inizialized to 0.
    \param delay - The int used for number of seconds for the thread to sleep
   
    The function prints "Task One has arrived! " before the rendezvous point.
    The function prints "Task One has left!" after the rendezvous point.
    There are a several ways to handle the rendezvous. In this case firstSem is waited and secondSem is signeled
    and will do the opposite in taskOne (signal firstSem and wait secondSem)  
*/
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  secondSem->Signal();
  firstSem->Wait();
  //THIS IS THE RENDEZVOUS POINT!
  std::cout << "Task Two has left "<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=5;
  int taskTwoDelay=1;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
