#ifndef ALARASENSORCONTROLLERDEFINITIONSBABYSHARK_H
#define ALARASENSORCONTROLLERDEFINITIONSBABYSHARK_H

#include "AutoSequenceClass.h"
#include <array>

// Define the number of autosequences here
#define NUM_ALARAV2S 4


AutoSequence IgnitionAutoSequence{-15000000, 2}; // X seconds in micros to set the countdownStart

std::array<AutoSequence*, NUM_ALARAV2S> autoSequenceArray{&IgnitionAutoSequence};



#endif