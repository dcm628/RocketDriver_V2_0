#ifndef VALVEDEFINITIONSBABYSHARK_H
#define VALVEDEFINITIONSBABYSHARK_H

#include "ValveClass.h"
#include <array>
#include "ALARApinDefines.h"

// Define number of valves here
#define NUM_VALVES 12

// Declare all Valve Objects here using ValveClass, and add them to the valveArray

// BabyShark Engine Node
Valve MVPneumaticsVent{17, 2, NormalClosed, ALARA_HIGHPOWER_PWMOUT1, ALARA_HIGHPOWER_DIGITALOUT1, 25000, false};                                               // 0
Valve LoxMV{24, 2, NormalClosed, ALARA_HIGHPOWER_PWMOUT2, ALARA_HIGHPOWER_DIGITALOUT2, 25000, false, true, ValveState::CloseCommanded, false, -1, 50};         // 1
Valve FuelMV{25, 2, NormalClosed, ALARA_HIGHPOWER_PWMOUT3, ALARA_HIGHPOWER_DIGITALOUT3, 25000, false, true, ValveState::CloseCommanded, false, -1, 50};
// BabyShark Propulsion Node
Valve LoxTankVent{18, 3, NormalOpen, ALARA_HIGHPOWER_PWMOUT1, ALARA_HIGHPOWER_DIGITALOUT1, 500000, false, 166};
Valve FuelTankVent{21, 3, NormalOpen, ALARA_HIGHPOWER_PWMOUT2, ALARA_HIGHPOWER_DIGITALOUT2, 25000, false};
Valve LoxDomeReg{19, 3, NormalClosed, ALARA_HIGHPOWER_PWMOUT3, ALARA_HIGHPOWER_DIGITALOUT3, 25000, false};
Valve LoxDomeRegVent{20, 3, NormalClosed, ALARA_HIGHPOWER_PWMOUT4, ALARA_HIGHPOWER_DIGITALOUT4, 25000, false};
Valve FuelDomeReg{22, 3, NormalClosed, ALARA_HIGHPOWER_PWMOUT5, ALARA_HIGHPOWER_DIGITALOUT5, 25000, false};
Valve FuelDomeRegVent{23, 3, NormalClosed, ALARA_HIGHPOWER_PWMOUT6, ALARA_HIGHPOWER_DIGITALOUT6, 25000, false};
// BabyShark Pad Node
Valve HiPress{16, 4, NormalClosed, ALARA_HIGHPOWER_PWMOUT1, ALARA_HIGHPOWER_DIGITALOUT1, 25000, false}; 
Valve HiPressVent{17, 4, NormalClosed, ALARA_HIGHPOWER_PWMOUT2, ALARA_HIGHPOWER_DIGITALOUT2, 25000, false};
Valve HiPressQD{16, 4, NormalClosed, ALARA_HIGHPOWER_PWMOUT3, ALARA_HIGHPOWER_DIGITALOUT3, 25000, false}; 

// ADD VALVES TO THIS VALVE ARRAY IN THE FORM: &VALVE
std::array<Valve*, NUM_VALVES> valveArray{&MVPneumaticsVent, &LoxMV, &FuelMV, &LoxTankVent, &FuelTankVent, &LoxDomeReg, &LoxDomeRegVent, &FuelDomeReg, &FuelDomeRegVent, &HiPress, &HiPressVent, &HiPressQD};

#endif