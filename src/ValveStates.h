#ifndef VALVESTATES_H
#define VALVESTATES_H

// defines the possible valve states accross all valves


enum class ValveState
{
    Closed,             // 0
    Open,               // 1
    ToBangBang,         // 2
    FireCommanded,      // 3
    OpenCommanded,      // 4
    CloseCommanded,     // 5
    OpenProcess,        // 6
    CloseProcess,       // 7
    ThrottleCommanded,  // 8    
    ThrottleProcess,    // 9    //Current State report format can't fit more than 8 states and this would overflow
    ValveState_SIZE,    // 10
};

#endif