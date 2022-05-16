#ifndef TOMILLISTIMETRACKER_H
#define TOMILLISTIMETRACKER_H

#include <Arduino.h>
#include <TimeLib.h>

//This is horseshit that I have to write this myself

// It IS CONRIFMED possible to get over 1000000 microseconds as the value for the second, but maybe by only 1 or so due to the clock cycle turn over inside this function
// Use a round up function that adds a second to the polled time and subtracts 1000? I guess it depends on the order, seconds would be ticked over if they were called after this and then just subtract 1000


time_t inProgramTime;
//time_t updateProgramTime;

int32_t inProgramSECS;
int32_t updateProgramSECS;

elapsedMicros timerSubSecondsMicros;
uint8_t calibrationLoopIterator = 0;        //when for loop condition is true, sets timer to 0 at system clock rollover, make sure to reset this if I ever set system time

uint32_t rocketDriverSeconds;
uint32_t rocketDriverMicros;

void myTimeTrackingFunction()
{
    //updateProgramSECS = second();
    if (calibrationLoopIterator < 10)       //each time the seconds roll over this adjusts the ellapsedMicros timer to sync up to it
    {
        if (second() != inProgramSECS)
        {
            timerSubSecondsMicros = 0;
            inProgramSECS = second();
            calibrationLoopIterator++;
        }
    }
    inProgramSECS = second();
    timerSubSecondsMicros = (timerSubSecondsMicros % 1000000);
    
    rocketDriverSeconds = second();
    rocketDriverMicros = timerSubSecondsMicros;
}

#endif