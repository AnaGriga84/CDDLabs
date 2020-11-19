/*! \mainpage Lab 5 Barriers
    \author Ana Griga , Student Number: C00231441
    \date 19.11.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/


// Barrier.cpp ---
//
// Filename: Barrier.cpp
// Description:
// Author: Joseph
// Maintainer:
// Created: Tue Jan  8 12:14:02 2019 (+0000)
// Version:
// Package-Requires: ()
// Last-Updated: Tue Jan  8 12:15:21 2019 (+0000)
//           By: Joseph
//     Update #: 2
// URL:
// Doc URL:
// Keywords:
// Compatibility:
//
//

// Code:
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>

/*!
    \file barrier.cpp
    \brief The barrier class function
The wait() and signal() in rapid succesion is called a turnstile and it allows//
one thread to pass at a time and it can be locked to bar all other threads.
*/


/*!
    \fn Barrier Destructor
     \brief The destructor invoked when the objects are destroyed
*/
Barrier::~Barrier()
{
    
}
/*!
    \fn phaseOne function
     \brief First phase of the rendezvous between n number of threads. 
     Using semaphores and mutex to control the flow of all threads to wait at the end
     for the last thread to be ready before continuing
*/
void Barrier::phaseOne()
{
    /* Count keeps track of how many threads have arrived.//
    Mutex provides access to count so that threads can increment it safely.*/
    mutex.Wait();
    ++count;
    if (count == numThreads)
    {
        std::cout<<std::endl;
        secondTurnStile.Wait();
        firstTurnStile.Signal();
    }
    mutex.Signal();

    firstTurnStile.Wait();
    firstTurnStile.Signal();
}
/*!
    \fn phaseTwo function
     \brief Second phase of the rendezvous between n number of threads.
     Using semaphores and mutex to control the flow of all threads to wait at the end
     for the last thread to be ready before continuing
*/
void Barrier::phaseTwo()
{
    mutex.Wait();
    --count;
    if (count == 0)
    {
        firstTurnStile.Wait();
        secondTurnStile.Signal();
    }
     if (count == 0)
    {
        std::cout<<std::endl;
    }
    mutex.Signal();

    secondTurnStile.Wait();
    secondTurnStile.Signal();
}
/*!
    \fn Barrier::wait()
     \brief Wait function that calls phaseOne() and phaseTwo() functions in sequence
*/
void Barrier::wait()
{
    phaseOne();
    phaseTwo();
}

//
// Barrier.cpp ends here
