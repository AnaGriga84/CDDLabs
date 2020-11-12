/*! \mainpage Lab 2 Semaphores
    \author Ana Griga , Student Number: C00231441
    \date 27.10.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>
/*! \class Signal
    \brief An Implementation of Threads Using Semaphores 
   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
*/
/*! Displays a message first*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  /*! Added Signal method for task one after print.
  Signal operation is used to control the exit of a task from a critical section 
  Signal is incrementing the value and carry on when the value is 0. 
  If the value is negative it is incrementing the value and a waiting thread is started*/
  theSemaphore->Signal();
}
/*! Displays a message second*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  /*! Added Wait method before the last print.
  Wait operation is used to control the entry of a task into the critical section
  If the semaphore value is currently zero, then the calling thread will not return from 
  the call to sem_wait() until it either locks the semaphore or the call is interrupted by a signal.*/
  theSemaphore->Wait(); 
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;
}
