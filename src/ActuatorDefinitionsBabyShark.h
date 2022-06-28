#ifndef ACTUATORDEFINITIONSBABYSHARK_H
#define ACTUATORDEFINITIONSBABYSHARK_H

#include "ActuatorClass.h"
#include <array>
#include "ALARApinDefines.h"

//Igniter outputs - setting up almost the same as valves but no PWM
#define NUM_ACTUATORS 2


Actuator Engine1TVC_Y(10, 2, LinearServo);
Actuator Engine1TVC_Z(11, 2, LinearServo);

// ADD Actuators TO THIS VALVE ARRAY IN THE FORM: &ACTUATOR
std::array<Actuator*, NUM_ACTUATORS> actuatorArray{&Engine1TVC_Y, &Engine1TVC_Z};

#endif