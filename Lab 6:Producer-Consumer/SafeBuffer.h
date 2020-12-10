/*! \mainpage Lab 6 Producer Consumer
    \author Ana Griga , Student Number: C00231441
    \date 27.11.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/
#pragma once
#include "Event.h"
#include "Semaphore.h"
#include <vector>

/*! \page SafeBuffer.h
    \file SafeBuffer.h
    \name SafeBuffer.h
    SafeBuffer object declaration
*/

class SafeBuffer
{
    private:
        std::vector<Event> theData;
        std::shared_ptr<Semaphore> theMutex;
        std::shared_ptr<Semaphore> theSemaphore;

    public:
        SafeBuffer();
        int push(Event);
        Event pop();
};

