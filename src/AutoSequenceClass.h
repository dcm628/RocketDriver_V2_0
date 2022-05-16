#ifndef AUTOSEQUENCECLASS_H
#define AUTOSEQUENCECLASS_H

#include <Arduino.h>
#include "AutoSequenceStates.h"


class AutoSequence
{

    private:
        int32_t countdownStart;        //must be set in Micros so it matches the timer
        int64_t currentCountdown;
        elapsedMicros timer;
        int32_t signedTimer;
        AutoSequenceState state;
        uint32_t hostNodeID;      // hostNodeID is for assigning the node that is the host of the autosequence, i.e. the node starting the engine should be in charge of ignition autosequence

    public:

    // constructor    
        AutoSequence(int32_t setCountdownStart, uint32_t setHostNodeID);

    // a start up method,
        void begin();

    // get functions, return the current value of that variable
        int32_t getCountdownStart(){return countdownStart;}
        int64_t getCurrentCountdown(){return currentCountdown;}
        AutoSequenceState getAutoSequenceState(){return state;}
        uint32_t getHostNodeID(){return hostNodeID;}
        uint32_t getTimer(){return timer;}
        uint32_t getSignedTimer(){return signedTimer;}
        
    // set functions, allows the setting of a variable
        //void setCountdownStart() {countdownStart;} //function to set a given autosequence countdown timer value
        
        void setCurrentCountdown(int64_t updateCountdown) {currentCountdown = updateCountdown;}

        void setSignedTimer(int32_t updateSignedTimer){signedTimer = updateSignedTimer;}

        void setState(AutoSequenceState newState) {state = newState;} //every time a state is set, the timer should reset

        void resetTimer() {timer = 0;}

        void stateOperations(); //add into this the functions for managing the countdown initialization and holds

};




#endif