#ifndef VALVEDEFINITIONSBABYSHARK_H
#define VALVEDEFINITIONSBABYSHARK_H

#include "ValveClass.h"
#include <array>

// Define number of valves here
//#define NUM_VALVES 10

// Declare all Valve Objects here using ValveClass, and add them to the valveArray
/* 
// On BabyShark Pad Node
Valve HiPress{16, 2, NormalClosed, 2, 25000, false};
Valve HiPressVent{17, 2, NormalClosed, 5, 25000, false};
Valve LoxMV{24, 2, NormalClosed, 7, 25000, false, -1, 50};
Valve FuelMV{25, 2, NormalClosed, 6, 25000, false, -1, 50};
// On BabyShark Propulsion Node
Valve LoxVent{18, 3, NormalOpen, 2, 500000, false, 166};
Valve CommonDomeReg{19, 3, NormalClosed, 5, 25000, false};
Valve CommonDomeRegVent{20, 3, NormalClosed, 6, 25000, false};
Valve FuelVent{21, 3, NormalClosed, 2, 25000, false};
Valve CommonDomeThrottle{23, 3, NormalClosed, 8, 25000, false};


// ADD VALVES TO THIS VALVE ARRAY IN THE FORM: &VALVE
std::array<Valve*, NUM_VALVES> valveArray{&HiPress, &HiPressVent, &LoxVent, &LoxDomeReg, &LoxDomeRegVent, &FuelVent, &FuelDomeReg, &FuelDomeRegVent, &FuelMV, &LoxMV};
 */
#endif