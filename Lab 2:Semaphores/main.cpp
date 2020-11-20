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
/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay)
    \brief This function will wait and then make print screen the message "I must print first"
    \param theSemaphore - The semaphore used for flow control. Its initial value is 0.
    \param delay - The int used for number of seconds the thread should sleep
    This function prints "I must print first".
*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay)
{
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
}
/*! Displays a message second*/
/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function will print screen the message "This will appear second"
    \param theSemaphore - The semaphore used for flow control. Its initial value is 0.
    This function has no delay parameter
    This function prints "This will appear second".
*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
{
  theSemaphore->Wait(); 
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

/*! \fn void main(void)
    \brief Main function of the program which creates and runs the 2 threads
    In the main function we create 2 threads and a semaphore
    \param int taskOneDelay - The variable used to see how long thread 2 will sleep for
*/

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
