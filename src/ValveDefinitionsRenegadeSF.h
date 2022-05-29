#ifndef VALVEDEFINITIONSRENEGADESF_H
#define VALVEDEFINITIONSRENEGADESF_H

#include "ValveClass.h"
#include <array>
#include "pinList.h"

// Define number of valves here
#define NUM_VALVES 10

// Declare all Valve Objects here using ValveClass, and add them to the valveArray
// On Renegade SF Engine Node
Valve HiPress{16, 2, NormalClosed, 2, 24, 25000, false}; 
Valve HiPressVent{17, 2, NormalClosed, 5, 24, 25000, false};
Valve LoxMV{24, 2, NormalClosed, 7, 26, 25000, false, true, ValveState::CloseCommanded, -1, 50};
Valve FuelMV{25, 2, NormalClosed, 6, 26, 25000, false, true, ValveState::CloseCommanded, -1, 50};
// On Renegade SF Prop Node
Valve LoxVent{18, 3, NormalOpen, 2, 27, 500000, false, 166};
Valve LoxDomeReg{19, 3, NormalClosed, 5, 25, 25000, false};
Valve LoxDomeRegVent{20, 3, NormalClosed, 6, 25, 25000, false};
Valve FuelVent{21, 3, NormalClosed, 9, 27, 25000, false};
Valve FuelDomeReg{22, 3, NormalClosed, 7, 26, 25000, false};
Valve FuelDomeRegVent{23, 3, NormalClosed, 8, 26, 25000, false};

// ADD VALVES TO THIS VALVE ARRAY IN THE FORM: &VALVE
std::array<Valve*, NUM_VALVES> valveArray{&HiPress, &HiPressVent, &LoxVent, &LoxDomeReg, &LoxDomeRegVent, &FuelVent, &FuelDomeReg, &FuelDomeRegVent, &FuelMV, &LoxMV};

#endif