#ifndef ALARASNCONFIGURATION_H
#define ALARASNCONFIGURATION_H

#include <iostream>
#include <unordered_map>

// Add any board revisions this enum list
enum class ALARAversion
{
V1,
V2_0,
V2_1,
};

// Add any board characteristics or configuration parameters to the following struct
// Update the map for all SNs whenever adding a parameter
struct ALARASN
{
    uint16_t ALARAaddress;
    uint8_t propulsionSysNodeID;
    ALARAversion boardRev;
};

// map that contains board config information for all ALARAs built
// Add all new ALARAs built here
// Assign board roles and use related config info
// ----- ALARA ADDRESSING ----- //
// V1: 256+
// V2_0: 0-15
// V2_1: 16-255 (255 maximum, cutoff range when board rev changes)
std::unordered_map<uint16_t, ALARASN> ALARASNmap
{
// map key = ALARA address
{0, ALARASN {0, 2, ALARAversion::V2_0}},
{16, ALARASN {16, 3, ALARAversion::V2_1}},
{256, ALARASN {256, 3, ALARAversion::V1}},
};

#endif