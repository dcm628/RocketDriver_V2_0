#ifndef PYRODEFINITIONSRENEGADESF_H
#define PYRODEFINITIONSRENEGADESF_H

#include "PyroClass.h"
#include <array>

//Igniter outputs - setting up almost the same as valves but no PWM
#define NUM_PYROS 2

Pyro EngineIgniter0{26, 2, Solo, 31, 2000000, false, -1500000}; // was firepin 11
Pyro EngineIgniter1{27, 2, Solo, 32, 2000000, false, -500000}; // was firepin 12

// ADD PYROS TO THIS VALVE ARRAY IN THE FORM: &PYRO
std::array<Pyro*, NUM_PYROS> pyroArray{&EngineIgniter0, &EngineIgniter1};

#endif