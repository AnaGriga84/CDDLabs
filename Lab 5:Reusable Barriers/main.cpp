/*! Lab 1 - Excercise2 Mutual Exclusion using Semaphores
    Author : Ana Griga
    Student Number : C00231441
    Tutor : Joseph Kehoe
    Licence : GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/
#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;


/*! \fn barrierTask
    \brief An example of using a reusable barrier
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops){

  //for(int i=0;i<numLoops;++i){
    //Do first bit of task
    //std::cout << "A"<< i;
    //Barrier
    //theBarrier.wait();
    //Do second half of task
    //std::cout<< "B" << i;
    //std::cout <<taskNum<< std::endl;
 
  //barrier code
  aMutexSem -> Wait();
  barCount++;

  if(barCount == threadCount)
  {
    std::cout << std::endl;
    barCount--;
    firstSem -> Signal();
    aMutexSem -> Signal();
  }
  else
  {
    aMutexSem -> Signal();
    firstSem -> Wait();
    aMutexSem -> Wait();
    --barCount;
    aMutexSem -> Signal();
    firstSem -> Wait();
  }
  //barrier code end
  std::cout << "A" << std::endl;
  }
  

}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Barrier> aBarrier( new Barrier(num_threads));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aBarrier,10);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
