#ifndef ALARASNCONFIGURATION_H
#define ALARASNCONFIGURATION_H
#pragma once

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
    bool BNO055_present;
    bool BMI085_present;
    bool KX134_1211_present;
    bool SAM_M8Q_GPS_present;
    bool MS5607_present;
};

// map that contains board config information for all ALARAs built
// Add all new ALARAs built here - USE SEQUENTIAL SERIAL NUMBERING, REGARDLESS OF ALARA BOARD REV
// Assign board roles and use related config info
// ----- ALARA ADDRESSING ----- //
// V1, V2_0:    0-15 possible address space based on 4 addressing pins
// V2_1:        0-255 possible address space based on 8 addressing pins
std::unordered_map<uint16_t, ALARASN> ALARASNmap
{
// map key = ALARA address
{0, ALARASN {0, 3, ALARAversion::V1, true, false, true, false, true}},
{1, ALARASN {1, 3, ALARAversion::V1, true, false, true, false, true}},
{3, ALARASN {3, 2, ALARAversion::V2_0, false, true, true, true, true}},
{4, ALARASN {4, 3, ALARAversion::V2_1, false, true, true, true, true}},
};

#endif