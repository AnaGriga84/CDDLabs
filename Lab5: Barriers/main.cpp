/*! \mainpage Lab 5 Barriers
    \author Ana Griga , Student Number: C00231441
    \date 19.11.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/

#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>

static const int num_threads = 10;
int sharedVariable = 0;

/*! \fn barrierTask
		\brief An example of using a reusable barrier. Displays a message that is split in to 2 sections to show how a rendezvous and work
*/

void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops)
{
	for (int i = 0; i < numLoops; ++i)
	{
		//Do first bit of task
		std::cout << "A";
		//Barrier
		theBarrier->wait();
		//Do second half of task
		std::cout << "B";
		theBarrier->wait();
	}
}

int main(void)
{
	std::vector<std::thread> vt(num_threads);
	std::shared_ptr<Barrier> aBarrier(new Barrier(num_threads));
	/**< Launch the threads  */
	int i = 0;
	for (std::thread &t : vt)
	{
		t = std::thread(barrierTask, aBarrier, 10);
	}
	/**< Join the threads with the main thread */
	for (auto &v : vt)
	{
		v.join();
	}
	std::cout << sharedVariable << std::endl;
	return 0;
}