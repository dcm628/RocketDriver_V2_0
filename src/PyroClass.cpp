#include "PyroClass.h"
#include <Arduino.h>



Pyro::Pyro(uint32_t setPyroID, uint32_t setPyroNodeID, uint8_t setFirePin, uint8_t setArmPin, uint32_t setLiveOutTime, bool setFireCommandBool, int32_t setFireSequenceTime,  bool setNodeIDCheck)
                : pyroID{setPyroID}, pyroNodeID{setPyroNodeID}, firePin{setFirePin}, armPin{setArmPin}, liveOutTime{setLiveOutTime}, fireCommandBool{setFireCommandBool}, fireSequenceTime{setFireSequenceTime}, nodeIDCheck{setNodeIDCheck}
{
    state = PyroState::Off;
    timer = 0;
}

void Pyro::begin()
{
    if (nodeIDCheck)
    {
        pinMode(firePin, OUTPUT);
        pinMode(armPin, OUTPUT);
        digitalWriteFast(firePin, 0);
        digitalWriteFast(armPin, 0);
    }
}

void Pyro::resetTimer()
{
    timer = 0;
}


void Pyro::stateOperations()
{
    switch (state)
    {
    // if a valve has been commanded to fire, it will start actuation after appropriate delay, normal closed actuate open, normal open actuate closed
    // every state change should reset the timer
    case PyroState::FireCommanded:
        if (fireCommandBool)
        {
            state = PyroState::OnCommanded;
            timer = 0;
            break;
  
        }
        break;

    // if a pyro is commanded on, turns on 
    case PyroState::OnCommanded:
        state = PyroState::On;
        timer = 0;
        break;

    case PyroState::On:
        digitalWriteFast(firePin, 1);
        digitalWriteFast(armPin, 1);
        if(timer >= liveOutTime)
        {
            state = PyroState::Off;
            timer = 0;
        }
        break;

    // if a pyro is commanded off, turns off immediately, not sure I need this at all the way we do on valves
    case PyroState::OffCommanded:
        state = PyroState::Off;
        timer = 0;
        break;
        
    case PyroState::Off:
        digitalWriteFast(firePin, 0);
        digitalWriteFast(armPin, 0);
        timer = 0;
        break;        
    
    // All other states require no action
    default:
        break;
    }
}