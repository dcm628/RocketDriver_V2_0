#ifndef STATELIST_H
#define STATELIST_H

// This header defines all the tracked states the system an be in, using an enum class for protection

enum class VehicleState
{
    // These are the God States, they can be reached from any position
    setup,      // 0
    debug,      // 1   the outputs disabled for testing state?
    passive,    // 2
    test,       // 3
    abort,      // 4
    vent,       // 5
    offNominal, // 6   off nominal is for when individual valves are actuated out of sequence


    // These states can only be accessed in sequence, from passive
    HiPressArm,             // 7
    HiPressPressurized,     // 8
    TankPressArm,           // 9
    TankPressPressurized,   // 10
    fireArmed,              // 11
    fire,                   // 12

};

enum class MissionState
{
    // These are the God States, they can be reached from any position
    passive,      // 0
    prelaunch,      // 1   the outputs disabled for testing state?
    ascentRail,    // 2
    ascentFree,       // 3
};
#endif