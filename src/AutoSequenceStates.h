#ifndef AutoSequenceStates_H
#define AutoSequenceStates_H

// defines the possible pyro states accross all Pyros


enum class AutoSequenceState
{
    Standby,                    // 0
    RunCommanded,               // 1
    Running,                    // 2
    Hold,                       // 3
    AutoSequenceState_SIZE,     // 4
};



#endif