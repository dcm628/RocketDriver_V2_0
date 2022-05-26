#ifndef PYRODEFINITIONSRENEGADESF_H
#define PYRODEFINITIONSRENEGADESF_H

#include "PyroClass.h"
#include <array>
#include "pinList.h"

// Define number of pyros here
#define NUM_PYROS 2

// Declare all Pyro Objects here using PyroClass, and add them to the pyroArray

// NEED TO FIX PIN MAPPING FOR THE SECOND OUTPUT TO NEW REAL STAND WIRING
// Engine Node
Pyro EngineIgniter0{26, 2, 31, 31, 2000000, false, -1500000};   // 0
Pyro EngineIgniter1{27, 2, 32, 32, 2000000, false, -500000};    // 1

// ADD PYROS TO THIS VALVE ARRAY IN THE FORM: &PYRO
std::array<Pyro*, NUM_PYROS> pyroArray{&EngineIgniter0, &EngineIgniter1};

#endif