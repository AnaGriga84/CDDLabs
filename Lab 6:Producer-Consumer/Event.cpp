/*! \mainpage Lab 6 Producer Consumer
    \author Ana Griga , Student Number: C00231441
    \date 27.11.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/
#include "Event.h"
#include <iostream>
#include <stdlib.h>


/*! \file Event.cpp
    \fn Event::Event()
    \name The implementation of the Event
    \brief The constructor and implementation of the Event class. The event creates random characters from a-z lower case
*/

Event::Event()
{
  theChar = 'a'+rand()%26;
  std::cout << theChar<< "Produced : "<< std::endl;
}

/*! \file Event.cpp
    \fn void Event::consume()
    \name The implementation of the Event
    \brief Outputs a caharacter from lower case to upper case
*/

void Event::consume()
{
    char upperChar = theChar-32;    
    std::cout << upperChar << "Consumed : "<<std::endl;
}