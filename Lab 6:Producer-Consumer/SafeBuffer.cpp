/*! \mainpage Lab 6 Producer Consumer
    \author Ana Griga , Student Number: C00231441
    \date 27.11.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/
#include "SafeBuffer.h"
#include <iostream>
#include <stdlib.h>
#include "Event.h"

/*! \page SafeBuffer
    \file SafeBuffer.cpp
    \name The implementation and constructor of SafeBuffer 
     \brief The safe buffer which implements mutual exclusion on the access to it using
    waits and signals used to organise the flow
    A Buffer of Events which has a mutex used for mutual exclusion 
    and a semaphore to control the flow between producers and consumers
*/
   
SafeBuffer::SafeBuffer()
{
    theMutex = std::make_shared<Semaphore>(1);
    theSemaphore = std::make_shared<Semaphore>(0);
}

/*!
    \fn SafeBuffer::push(Event newChar)
    \brief Function push() to add event into the buffer
    \param newChar The lower case character event created 
    Capture a mutex lock, adds an event object to the buffer, releases the mutex lock 
    and then signals the consumers to let it consume the produced object
*/

int SafeBuffer::push(Event newChar)
{
    theMutex->Wait();
    theData.push_back(newChar);
    int size = theData.size();
    theMutex->Signal();
    theSemaphore->Signal();
    return size;
}

/*!
    \fn SafeBuffer::pop()
    \brief Function pop() that consumes an event from the buffer
    It contains a wait() to forbide moving forward while there is nothing to consume
    Contains a mutex lock, takes the Event from the buffer and cahnges the lower case character produced into an uppercase character 
    When the operation is complete, the mutex is released
*/

Event SafeBuffer::pop()
{
    theSemaphore->Wait();
    theMutex->Wait();
    Event e = theData.back();
    theData.pop_back();
    theMutex->Signal();
    return e;
}