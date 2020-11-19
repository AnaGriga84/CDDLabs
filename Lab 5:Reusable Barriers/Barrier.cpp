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


Barrier::~Barrier()
{
    
}

void Barrier::phaseOne()
{
    mutex->Wait();
    ++count;
    if (count == nThreads)
    {
        std::cout<<std::endl;
        secondTurnStile->Wait();
        firstTurnStile->Signal();
    }
    mutex->Signal();

    firstTurnStile->Wait();
    firstTurnStile->Signal();
}
void Barrier::phaseTwo()
{
    mutex->Wait();
    --count;
    if (count == 0)
    {
        firstTurnStile->Wait();
        secondTurnStile->Signal();
    }
     if (count == 0)
    {
        std::cout<<std::endl;
    }
    mutex->Signal();

    secondTurnStile->Wait();
    secondTurnStile->Signal();
}
void Barrier::wait()
{
    phaseOne();
    phaseTwo();
}

//
// Barrier.cpp ends here
