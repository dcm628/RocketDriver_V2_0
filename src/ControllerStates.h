#ifndef CONTROLLERSTATES_H
#define CONTROLLERSTATES_H

// defines the possible controller states accross propulsion controllers
// very preliminary, update as needed while developing controllers

enum class ControllerState
{
    Passive,                    // 0
    Active,                     // 1
    TestPassthrough,            // 2
    AutosequenceCommanded,      // 3
    ControllerState_SIZE,       // 4
};

#endif