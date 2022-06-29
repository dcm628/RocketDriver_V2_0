#ifndef ALARASENSORCONTROLLERDEFINITIONSBABYSHARK_H
#define ALARASENSORCONTROLLERDEFINITIONSBABYSHARK_H

#include "ALARASensorControllerClass.h"
#include <array>

// Define the number of autosequences here
#define NUM_ALARAV2S 4


ALARAV2SensorController ALARAV2node2{1, 2}; // 
ALARAV2SensorController ALARAV2node3{2, 3}; // 
ALARAV2SensorController ALARAV2node4{3, 4}; // 
ALARAV2SensorController ALARAV2node7{4, 7}; // 

std::array<ALARAV2SensorController*, NUM_ALARAV2S> ALARAV2Array{&ALARAV2node2, &ALARAV2node3, &ALARAV2node4, &ALARAV2node7};



#endif