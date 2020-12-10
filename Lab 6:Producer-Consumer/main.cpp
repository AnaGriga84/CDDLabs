/*! \mainpage Lab 6 Producer Consumer
    \author Ana Griga , Student Number: C00231441
    \date 27.11.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/

#include "Event.h"
#include <iostream>
#include <thread>
#include <vector>
#include "SafeBuffer.h"

static const int num_threads = 10; //The number of threads to be made for the producer and the consumer
const int size=10;

/*! \fn void producer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops)
    \brief Produce events and then adds them to the buffer
    \param theBuffer
    \param numLoops
*/

void producer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops)
{
  for(int i=0;i<numLoops;++i)
  {
    //Produce event and add to buffer
    Event event ;
    theBuffer->push(event);
  } 
}

/*! \fn void consumer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops)
    \brief Takes the events created by the producer from buffer and consumes them
    \param theBuffer
    \param numLoops
*/
void consumer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops)
{

  for(int i=0;i<numLoops;++i)
  {
    //Produce event and add to buffer
    Event event ;
    event = theBuffer->pop();
    event.consume();
  }
}

int main(void)
{

  std::vector<std::thread> producers(num_threads);
  std::vector<std::thread> consumers(num_threads);
  std::shared_ptr<SafeBuffer> aBuffer( new SafeBuffer());
  /**< Launch the threads  */
  for(std::thread& prod: producers)
  {
    prod=std::thread(producer,aBuffer,10);
  }

  for(std::thread& cons: consumers)
  {
    cons=std::thread(consumer,aBuffer,10);
  }

  /**< Join the threads with the main thread */
  for (auto& p :producers)
  {
      p.join();
  }
  for (auto& c :consumers)
  {
      c.join();
  }

  std::cout  << std::endl;
  return 0;
}