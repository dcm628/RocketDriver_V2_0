#ifndef SENSORDEFINITIONSRENEGADESF_H
#define SENSORDEFINITIONSRENEGADESF_H

#include "SensorClass.h"
#include <array>

// define number of sensors here
// Renegade SF
#define NUM_SENSORS 20

// initialize all sensor objects here
// Renegade SF Stand
MCU_SENSOR ThrustMountLoadCell1pos{50, 2, A0, 2, 10, 100, false};                       // 0
MCU_SENSOR ThrustMountLoadCell1neg{50, 5, A0, 2, 10, 100, false};                       // 1
MCU_SENSOR ThrustMountLoadCell2pos{51, 2, A1, 2, 10, 100, false};                       // 2
MCU_SENSOR ThrustMountLoadCell2neg{51, 5, A1, 2, 10, 100, false};                       // 3
MCU_SENSOR ThrustMountLoadCell3pos{52, 2, A2, 2, 10, 100, false};                       // 4
MCU_SENSOR ThrustMountLoadCell3neg{52, 5, A2, 2, 10, 100, false};                       // 5
MCU_SENSOR ChamberPT2{55, 2, A5, 10, 100, 800, false, 0.0186, -102.94};                 // 6
MCU_SENSOR ChamberPT1{56, 2, A6, 10, 100, 800, false, 0.0185, -128.88};                 // 7
MCU_SENSOR FuelInletPropSidePT{57, 2, A7, 2, 10, 100, false, 0.0185, -125.74};          // 8
MCU_SENSOR FuelInjectorPT{58, 2, A8, 10, 100, 500, false, 0.0186, -123.27};             // 9
MCU_SENSOR LoxInletPropSidePT{59, 2, A9, 2, 10, 100, false, 0.0186, -128.58};           // 10
MCU_SENSOR MVPneumaticsPT{78, 3, A3, 2, 10, 50, false, 0.0186, -126.56};                // 11
MCU_SENSOR DomeRegFuelPT{79, 3, A4, 2, 50, 100, false, 0.0186, -126.67};                // 12
MCU_SENSOR DomeRegLoxPT{80, 3, A5, 2, 50, 100, false, 0.0185, -133.36};                 // 13
MCU_SENSOR FuelTankPT{81, 3, A6, 2, 10, 100, false, 0.0186, -129.3};                    // 14
MCU_SENSOR LoxTankPT{82, 3, A7, 2, 10, 100, false, 0.0187, -125.36};                    // 15
MCU_SENSOR HiPressFuelPT{83, 3, A8, 2, 10, 50, false, 0.0933, -638.38};                 // 16
MCU_SENSOR HiPressLoxPT{84, 3, A9, 2, 10, 50, false, 0.093, -629.72};                   // 17
MCU_SENSOR MCUtempNode2{200, 2, 70, 2, 5, 10, true};                                    // 18
MCU_SENSOR MCUtempNode3{300, 3, 70, 2, 5, 10, true};                                    // 19

// Sensor Array including Renegade SF only
std::array<MCU_SENSOR*, NUM_SENSORS> sensorArray{&ThrustMountLoadCell1pos, &ThrustMountLoadCell1neg, &ThrustMountLoadCell2pos, &ThrustMountLoadCell2neg,&ThrustMountLoadCell3pos, &ThrustMountLoadCell3neg, &ChamberPT2, &ChamberPT1, &FuelInletPropSidePT, &FuelInjectorPT, &LoxInletPropSidePT, &MVPneumaticsPT, &DomeRegFuelPT, &DomeRegLoxPT, &FuelTankPT, &LoxTankPT, &HiPressFuelPT};

#endif