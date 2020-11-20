/*! \mainpage Lab 4 Mutual Exclusion Using Semaphores
    \author Ana Griga , Student Number: C00231441
    \date 07.11.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;


/*! \fn void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
    \brief An Implementation of Mutual Exclusion using Semaphores
    \param firstsem - Semaphore used to achieve mutual exclusion, initalized to 1 to allow the first wait() call to continue.
    \param numUpdates - This is the variable incremented to show the use of mutual exclusion. 
    This parameter will be incremented by one thread at the time.
    \param num_threads - The number of threads that will create to do the work.
    \param sharedVariable - The shared variable that all threads will try to increment. 

    Established a mutex lock arouns sharedVariable in order to only allow one thread at a time to have access to this variable.
    In the for loop : 
    Thread arrives, if semaphore number is greater than 0, proceed and decrement seamphore number, 
    else if number is 0 or lower threads will wait in a queue to be signaled.
    Then thread updates the critical section.
    Lastly thread calles signal which increments Semaphore number and wakes a random thread from the waiting queue.
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){


  for(int i=0;i<numUpdates;i++){
    /*! Thread arrives, if semaphore number is greater than 0, proceed and decrement seamphore number, 
     else if number is 0 or lower threads will wait in a queue to be signaled */
    firstSem -> Wait();
    /*! thread updates critical section */
    sharedVariable++;
    /*! Thread calles signal which increments Semaphore number and wakes a random thread from the waiting queue */
    firstSem -> Signal();
  }

}
/*!
  \fn main(void)
  \brief This is the main method that creates a semaphore initialized to 1, so that first thread to be able to pass the first wait() of the semaphore. 
  \return The main method returns 0, for the program to exit normal.
*/

int main(void){
  std::vector<std::thread> vt(num_threads);
  /*!Inizialize at 1 to make a mutex semaphore*/
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1)); 
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
