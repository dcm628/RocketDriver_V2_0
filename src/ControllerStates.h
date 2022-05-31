#ifndef CONTROLLERSTATES_H
#define CONTROLLERSTATES_H

// defines the possible controller states accross propulsion controllers
// very preliminary, update as needed while developing controllers
// Current plan - setup different controller types as different state enum lists

enum class TankPressControllerState
{
    Passive,                    // 0
    Active,                     // 1
    DomePressActive,            // 2
    HiPressPassthroughVent,     // 3
    Armed,                      // 4
    Vent,                       // 5
    TestPassthrough,            // 6
    AutosequenceCommanded,      // 7
    ControllerState_SIZE,       // 8
};

// generic below, probably supercede/replace as I get to other controllers
enum class ControllerState
{
    Passive,                    // 0
    Active,                     // 1
    Armed,                      // 2
    Vent,                       // 3
    TestPassthrough,            // 4
    AutosequenceCommanded,      // 5
    ControllerState_SIZE,       // 6
};


enum class EngineControllerState
{
    Passive,                    // 0
    Active,                     // 1
    Chill,                      // 2
    Purge,                      // 3
    Shutdown,                   // 4
    Armed,                      // 5
    TestPassthrough,            // 6
    AutosequenceCommanded,      // 7
    ControllerState_SIZE,       // 8
};

enum class ALARAV2SensorControllerState
{
    Passive,                    // 0
    Active,                     // 1
    GNCOnly,                    // 2
    InternalOnly,               // 3
    ControllerState_SIZE,       // 4
};

#endif