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


/*! \fn updateTask
    \brief An Implementation of Mutual Exclusion using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){


  for(int i=0;i<numUpdates;i++){
    /*! thread arrives, if semaphore number is greater than 0, proceed and decrement seamphore number, 
     else if number is 0 or lower threads will wait in a queue to be signaled */
    firstSem -> Wait();
    /*! thread updates critical section */
    sharedVariable++;
    /*! thread calles signal which increments Semaphore number and wakes a random thread from the waiting queue */
    firstSem -> Signal();
  }

}

int main(void){
  std::vector<std::thread> vt(num_threads);
  /*!inizialize at 1 to make a mutex semaphore*/
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
