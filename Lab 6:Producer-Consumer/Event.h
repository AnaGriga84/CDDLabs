/*! \mainpage Lab 6 Producer Consumer
    \author Ana Griga , Student Number: C00231441
    \date 19.11.2020
    \version GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007
*/

/*! The event object*/

#pragma once
class Event
{
    private:
        char theChar;
    public:
        Event();
        void consume();
};


