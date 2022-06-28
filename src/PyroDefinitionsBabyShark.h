#ifndef PYRODEFINITIONSBABYSHARK_H
#define PYRODEFINITIONSBABYSHARK_H

#include "PyroClass.h"
#include <array>
#include "ALARApinDefines.h"

// Define number of pyros here
#define NUM_PYROS 10

// Declare all Pyro Objects here using PyroClass, and add them to the pyroArray

// Engine Node
Pyro EngineIgniter0{26, 2, ALARA_HIGHPOWER_DIGITALOUT4, ALARA_HIGHPOWER_PWMOUT4, 2000000, false, -1500000};     // 0
Pyro EngineIgniter1{27, 2, ALARA_HIGHPOWER_DIGITALOUT5, ALARA_HIGHPOWER_PWMOUT5, 2000000, false, -500000};      // 1
// Telemetry Node - needs some setting tweaks
Pyro PilotChute1_1{26, 7, ALARA_HIGHPOWER_DIGITALOUT1, ALARA_HIGHPOWER_PWMOUT1, 2000000, false, -1500000};      // 2
Pyro PilotChute1_2{27, 7, ALARA_HIGHPOWER_DIGITALOUT2, ALARA_HIGHPOWER_PWMOUT2, 2000000, false, -500000};       // 3
Pyro DrogueChute1_1{26, 7, ALARA_HIGHPOWER_DIGITALOUT3, ALARA_HIGHPOWER_PWMOUT3, 2000000, false, -1500000};     // 4
Pyro DrogueChute1_2{27, 7, ALARA_HIGHPOWER_DIGITALOUT4, ALARA_HIGHPOWER_PWMOUT4, 2000000, false, -500000};      // 5
Pyro DrogueChute2_1{26, 7, ALARA_HIGHPOWER_DIGITALOUT5, ALARA_HIGHPOWER_PWMOUT5, 2000000, false, -1500000};     // 6
Pyro DrogueChute2_2{27, 7, ALARA_HIGHPOWER_DIGITALOUT6, ALARA_HIGHPOWER_PWMOUT6, 2000000, false, -500000};      // 7
Pyro MainChute1_1{26, 7, ALARA_HIGHPOWER_DIGITALOUT7, ALARA_HIGHPOWER_PWMOUT7, 2000000, false, -1500000};       // 8
Pyro MainChute1_2{27, 7, ALARA_HIGHPOWER_DIGITALOUT8, ALARA_HIGHPOWER_PWMOUT8, 2000000, false, -500000};        // 9

// ADD PYROS TO THIS VALVE ARRAY IN THE FORM: &PYRO
std::array<Pyro*, NUM_PYROS> pyroArray{&EngineIgniter0, &EngineIgniter1, &PilotChute1_1, &PilotChute1_2, &DrogueChute1_1, &DrogueChute1_2, &DrogueChute2_1, &DrogueChute2_2, &MainChute1_1, &MainChute1_2};

#endif