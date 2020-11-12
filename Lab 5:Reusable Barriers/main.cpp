/*! \mainpage Lab 5 Reusable barriers with semaphore and mutex
    \author Ana Griga , Student Number: C00231441
    \date 07.11.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;
int barCount;

/*! \fn barrierTask
    \brief An example of using a reusable barrier
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void barrierTask(std::shared_ptr<Semaphore> mutexSem, std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int taskNum, int threadCount)
{
for (int i = 0; i<2; i++)
{
  //the rendezvous
  std::cout << "A";
  mutexSem -> Wait();
  barCount++;
  if(barCount == num_threads)
  {
    std::cout << std::endl;
    secondSem -> Wait();
    firstSem -> Signal();
  }
  mutexSem -> Signal();
  firstSem -> Wait();
  firstSem -> Signal();
  mutexSem -> Wait();
  --barCount;
  
  if (barCount == 0)
  {
    firstSem -> Wait();
    secondSem -> Signal();
  }
  std::cout<< "B";
  mutexSem -> Signal();
  secondSem -> Wait();
  secondSem -> Signal();
}
}

int main(void)
{
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> firstSem(new Semaphore);
  std::shared_ptr<Semaphore> secondSem(new Semaphore(1));
  std::shared_ptr<Semaphore> mutexSem(new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  barCount = 0;
  for(std::thread& t: vt)
  {
    t=std::thread(barrierTask, mutexSem, firstSem, secondSem, i++, num_threads);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << std::endl;
  return 0;
}
