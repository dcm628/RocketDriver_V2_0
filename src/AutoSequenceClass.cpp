#include "AutoSequenceClass.h"
//#include "AutoSequenceStates.h"
#include <Arduino.h>

//int64_t maxcountdownint = 36028797018963968; //7 byte (56 bit) signed int max value, this is to stay inside 7 CAN bytes


AutoSequence::AutoSequence(int32_t setCountdownStart, uint32_t setHostNodeID) : countdownStart{setCountdownStart}, hostNodeID{setHostNodeID}
{

}

void AutoSequence::begin()
{
    
}



void AutoSequence::stateOperations()
{
    switch (state)
    {
    case AutoSequenceState::Standby:
        
        setCurrentCountdown(countdownStart);
        //setCurrentCountdown(0);
        break;

    
    case AutoSequenceState::RunCommanded:
        
        timer = 0;
        state = AutoSequenceState::Running;
        

        break;
        
       
    case AutoSequenceState::Running:
        //if (hostNodeID = nodeID)
        //{
            countdownStart = getCountdownStart();
            //Serial.print("CountdownStart from StateOps : ");
            //Serial.print(countdownStart);
            timer = getTimer();
            signedTimer = (signed int)timer;
            //Serial.print(" timer : ");
            //Serial.print(timer);
            currentCountdown = signedTimer + countdownStart;
            //Serial.print("currentCountdown");
            //Serial.println(currentCountdown);
            //setCurrentCountdown(currentCountdown);
        //}
        break;

       
    case AutoSequenceState::Hold:
        

        
        break;
    
    // All other states require no action
    default:
        break;
    }
}



/* void AutoSequence::resetTimer()
{
    timer = 0;
} */