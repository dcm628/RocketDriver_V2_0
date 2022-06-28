#ifndef SENSORDEFINITIONSBABYSHARK_H
#define SENSORDEFINITIONSBABYSHARK_H

#include "SensorClass.h"
#include <array>
#include "ALARApinDefines.h"

// define number of sensors here
// BabyShark Rocket Config
#define NUM_SENSORS 17              // Total system number of external propulsion sensors
#define NUMINTERNAL_SENSORS 13      // On EACH ALARA


// initialize all sensor objects here
// BabyShark2
// Engine Node
MCU_SENSOR ChamberPT1{55, 2, ALARA_ANALOG_IN1, 10, 100, 800, false, 0.0186, -102.94};                 // 0
MCU_SENSOR ChamberPT2{56, 2, ALARA_ANALOG_IN2, 10, 100, 800, false, 0.0185, -128.88};                 // 1
MCU_SENSOR ChamberPT3{56, 2, ALARA_ANALOG_IN3, 10, 100, 800, false, 0.0185, -128.88};                 // 2
MCU_SENSOR FuelInletPropSidePT{57, 2, ALARA_ANALOG_IN4, 2, 10, 100, false, 0.0185, -125.74};          // 3
MCU_SENSOR LoxInletPropSidePT{59, 2, ALARA_ANALOG_IN5, 2, 10, 100, false, 0.0186, -128.58};           // 4
// Prop Node
MCU_SENSOR MVPneumaticsPT{78, 3, ALARA_ANALOG_IN1, 2, 10, 50, false, 0.0186, -126.56};                // 5
MCU_SENSOR DomeRegFuelPT{79, 3, ALARA_ANALOG_IN2, 2, 50, 100, false, 0.0186, -126.67};                // 6
MCU_SENSOR DomeRegLoxPT{80, 3, ALARA_ANALOG_IN3, 2, 50, 100, false, 0.0185, -133.36};                 // 7
MCU_SENSOR FuelTankPT{81, 3, ALARA_ANALOG_IN4, 2, 10, 100, false, 0.0186, -129.3};                    // 8
MCU_SENSOR LoxTankPT{82, 3, ALARA_ANALOG_IN5, 2, 10, 100, false, 0.0187, -125.36};                    // 9
MCU_SENSOR HiPressTankPT{83, 3, ALARA_ANALOG_IN6, 2, 10, 50, false, 0.0933, -638.38};                 // 10
// Pad Node
MCU_SENSOR ThrustMountLoadCell1pos{50, 4, ALARA_ANALOG_IN1, 2, 10, 100, false};                       // 11
MCU_SENSOR ThrustMountLoadCell1neg{50, 4, ALARA_ANALOG_IN2, 2, 10, 100, false};                       // 12
MCU_SENSOR ThrustMountLoadCell2pos{51, 4, ALARA_ANALOG_IN3, 2, 10, 100, false};                       // 13
MCU_SENSOR ThrustMountLoadCell2neg{51, 4, ALARA_ANALOG_IN4, 2, 10, 100, false};                       // 14
MCU_SENSOR HiPress6kPT{83, 4, ALARA_ANALOG_IN5, 2, 10, 50, false, 0.0933, -638.38};                   // 15
MCU_SENSOR HiPress1kPT{83, 4, ALARA_ANALOG_IN6, 2, 10, 50, false, 0.0933, -638.38};                   // 16
// Telemetry Node
// -- no external sensors currently --


// ALARA internal sensor reads
// Node 2 - Engine Node
MCU_SENSOR ALARA_HighPowerOut1_Node2{203, 2, ALARA_HIGHPOWER_ANALOGREAD1, 2, 5, 10, true};                          // 0
MCU_SENSOR ALARA_HighPowerOut2_Node2{201, 2, ALARA_HIGHPOWER_ANALOGREAD2, 2, 5, 10, true};                          // 1
MCU_SENSOR ALARA_HighPowerOut3_Node2{209, 2, ALARA_HIGHPOWER_ANALOGREAD3, 2, 5, 10, true};                          // 2
MCU_SENSOR ALARA_HighPowerOut4_Node2{216, 2, ALARA_HIGHPOWER_ANALOGREAD4, 2, 5, 10, true};                          // 3
MCU_SENSOR ALARA_HighPowerOut5_Node2{217, 2, ALARA_HIGHPOWER_ANALOGREAD5, 2, 5, 10, true};                          // 4
MCU_SENSOR ALARA_HighPowerOut6_Node2{218, 2, ALARA_HIGHPOWER_ANALOGREAD6, 2, 5, 10, true};                          // 5
MCU_SENSOR ALARA_HighPowerOut7_Node2{219, 2, ALARA_HIGHPOWER_ANALOGREAD7, 2, 5, 10, true};                          // 6
MCU_SENSOR ALARA_HighPowerOut8_Node2{200, 2, ALARA_HIGHPOWER_ANALOGREAD8, 2, 5, 10, true};                          // 7
MCU_SENSOR ALARA_HighPowerOut9_Node2{206, 2, ALARA_HIGHPOWER_ANALOGREAD9, 2, 5, 10, true};                          // 8
MCU_SENSOR ALARA_HighPowerOut10_Node2{207, 2, ALARA_HIGHPOWER_ANALOGREAD10, 2, 5, 10, true};                        // 9
MCU_SENSOR ALARA_3V3_Node2{223, 2, ALARA_ANALOG_3_3RAIL, 2, 5, 10, true};                                           // 10
MCU_SENSOR ALARA_5V_Node2{224, 2, ALARA_ANALOG_5RAIL, 2, 5, 10, true};                                              // 11
MCU_SENSOR MCUtempNode2{270, 2, 70, 2, 5, 10, true};                                                                // 12
// Node 3 - Prop Node
MCU_SENSOR ALARA_HighPowerOut1_Node3{303, 3, ALARA_HIGHPOWER_ANALOGREAD1, 2, 5, 10, true};                          // 0
MCU_SENSOR ALARA_HighPowerOut2_Node3{301, 3, ALARA_HIGHPOWER_ANALOGREAD2, 2, 5, 10, true};                          // 1
MCU_SENSOR ALARA_HighPowerOut3_Node3{309, 3, ALARA_HIGHPOWER_ANALOGREAD3, 2, 5, 10, true};                          // 2
MCU_SENSOR ALARA_HighPowerOut4_Node3{316, 3, ALARA_HIGHPOWER_ANALOGREAD4, 2, 5, 10, true};                          // 3
MCU_SENSOR ALARA_HighPowerOut5_Node3{317, 3, ALARA_HIGHPOWER_ANALOGREAD5, 2, 5, 10, true};                          // 4
MCU_SENSOR ALARA_HighPowerOut6_Node3{318, 3, ALARA_HIGHPOWER_ANALOGREAD6, 2, 5, 10, true};                          // 5
MCU_SENSOR ALARA_HighPowerOut7_Node3{319, 3, ALARA_HIGHPOWER_ANALOGREAD7, 2, 5, 10, true};                          // 6
MCU_SENSOR ALARA_HighPowerOut8_Node3{300, 3, ALARA_HIGHPOWER_ANALOGREAD8, 2, 5, 10, true};                          // 7
MCU_SENSOR ALARA_HighPowerOut9_Node3{306, 3, ALARA_HIGHPOWER_ANALOGREAD9, 2, 5, 10, true};                          // 8
MCU_SENSOR ALARA_HighPowerOut10_Node3{307, 3, ALARA_HIGHPOWER_ANALOGREAD10, 2, 5, 10, true};                        // 9
MCU_SENSOR ALARA_3V3_Node3{323, 3, ALARA_ANALOG_3_3RAIL, 2, 5, 10, true};                                           // 10
MCU_SENSOR ALARA_5V_Node3{324, 3, ALARA_ANALOG_5RAIL, 2, 5, 10, true};                                              // 11
MCU_SENSOR MCUtempNode3{370, 3, 70, 2, 5, 10, true};                                                                // 12
// Node 4 - Pad Node
MCU_SENSOR ALARA_HighPowerOut1_Node4{403, 4, ALARA_HIGHPOWER_ANALOGREAD1, 2, 5, 10, true};                          // 0
MCU_SENSOR ALARA_HighPowerOut2_Node4{401, 4, ALARA_HIGHPOWER_ANALOGREAD2, 2, 5, 10, true};                          // 1
MCU_SENSOR ALARA_HighPowerOut3_Node4{409, 4, ALARA_HIGHPOWER_ANALOGREAD3, 2, 5, 10, true};                          // 2
MCU_SENSOR ALARA_HighPowerOut4_Node4{416, 4, ALARA_HIGHPOWER_ANALOGREAD4, 2, 5, 10, true};                          // 3
MCU_SENSOR ALARA_HighPowerOut5_Node4{417, 4, ALARA_HIGHPOWER_ANALOGREAD5, 2, 5, 10, true};                          // 4
MCU_SENSOR ALARA_HighPowerOut6_Node4{418, 4, ALARA_HIGHPOWER_ANALOGREAD6, 2, 5, 10, true};                          // 5
MCU_SENSOR ALARA_HighPowerOut7_Node4{419, 4, ALARA_HIGHPOWER_ANALOGREAD7, 2, 5, 10, true};                          // 6
MCU_SENSOR ALARA_HighPowerOut8_Node4{400, 4, ALARA_HIGHPOWER_ANALOGREAD8, 2, 5, 10, true};                          // 7
MCU_SENSOR ALARA_HighPowerOut9_Node4{406, 4, ALARA_HIGHPOWER_ANALOGREAD9, 2, 5, 10, true};                          // 8
MCU_SENSOR ALARA_HighPowerOut10_Node4{407, 4, ALARA_HIGHPOWER_ANALOGREAD10, 2, 5, 10, true};                        // 9
MCU_SENSOR ALARA_3V3_Node4{423, 4, ALARA_ANALOG_3_3RAIL, 2, 5, 10, true};                                           // 10
MCU_SENSOR ALARA_5V_Node4{424, 4, ALARA_ANALOG_5RAIL, 2, 5, 10, true};                                              // 11
MCU_SENSOR MCUtempNode4{470, 4, 70, 2, 5, 10, true};                                                                // 12
// Node 7 - Telemetry Node
MCU_SENSOR ALARA_HighPowerOut1_Node7{703, 7, ALARA_HIGHPOWER_ANALOGREAD1, 2, 5, 10, true};                          // 0
MCU_SENSOR ALARA_HighPowerOut2_Node7{701, 7, ALARA_HIGHPOWER_ANALOGREAD2, 2, 5, 10, true};                          // 1
MCU_SENSOR ALARA_HighPowerOut3_Node7{709, 7, ALARA_HIGHPOWER_ANALOGREAD3, 2, 5, 10, true};                          // 2
MCU_SENSOR ALARA_HighPowerOut4_Node7{716, 7, ALARA_HIGHPOWER_ANALOGREAD4, 2, 5, 10, true};                          // 3
MCU_SENSOR ALARA_HighPowerOut5_Node7{717, 7, ALARA_HIGHPOWER_ANALOGREAD5, 2, 5, 10, true};                          // 4
MCU_SENSOR ALARA_HighPowerOut6_Node7{718, 7, ALARA_HIGHPOWER_ANALOGREAD6, 2, 5, 10, true};                          // 5
MCU_SENSOR ALARA_HighPowerOut7_Node7{719, 7, ALARA_HIGHPOWER_ANALOGREAD7, 2, 5, 10, true};                          // 6
MCU_SENSOR ALARA_HighPowerOut8_Node7{700, 7, ALARA_HIGHPOWER_ANALOGREAD8, 2, 5, 10, true};                          // 7
MCU_SENSOR ALARA_HighPowerOut9_Node7{706, 7, ALARA_HIGHPOWER_ANALOGREAD9, 2, 5, 10, true};                          // 8
MCU_SENSOR ALARA_HighPowerOut10_Node7{707, 7, ALARA_HIGHPOWER_ANALOGREAD10, 2, 5, 10, true};                        // 9
MCU_SENSOR MCUtempNode7{770, 7, 70, 2, 5, 10, true};                                                                // 10
MCU_SENSOR ALARA_3V3_Node7{423, 7, ALARA_ANALOG_3_3RAIL, 2, 5, 10, true};                                           // 11
MCU_SENSOR ALARA_5V_Node7{424, 7, ALARA_ANALOG_5RAIL, 2, 5, 10, true};                                              // 12

// Sensor Array
std::array<MCU_SENSOR*, NUM_SENSORS> sensorArray{&ThrustMountLoadCell1pos, &ThrustMountLoadCell1neg, &ThrustMountLoadCell2pos, &ThrustMountLoadCell2neg, &ChamberPT1, &ChamberPT2, &ChamberPT3, &FuelInletPropSidePT, &LoxInletPropSidePT, &MVPneumaticsPT, &DomeRegFuelPT, &DomeRegLoxPT, &FuelTankPT, &LoxTankPT, &HiPressTankPT, &HiPress6kPT, &HiPress1kPT};

// Internal Sensor Arrays
std::array<MCU_SENSOR*, NUM_SENSORS> internalSensorArray2{&ALARA_HighPowerOut1_Node2, &ALARA_HighPowerOut2_Node2, &ALARA_HighPowerOut3_Node2, &ALARA_HighPowerOut4_Node2, &ALARA_HighPowerOut5_Node2, &ALARA_HighPowerOut6_Node2, &ALARA_HighPowerOut7_Node2, &ALARA_HighPowerOut8_Node2, &ALARA_HighPowerOut9_Node2, &ALARA_HighPowerOut10_Node2, &MCUtempNode2, &ALARA_3V3_Node2, &ALARA_5V_Node2};
std::array<MCU_SENSOR*, NUM_SENSORS> internalSensorArray3{&ALARA_HighPowerOut1_Node3, &ALARA_HighPowerOut2_Node3, &ALARA_HighPowerOut3_Node3, &ALARA_HighPowerOut4_Node3, &ALARA_HighPowerOut5_Node3, &ALARA_HighPowerOut6_Node3, &ALARA_HighPowerOut7_Node3, &ALARA_HighPowerOut8_Node3, &ALARA_HighPowerOut9_Node3, &ALARA_HighPowerOut10_Node3, &MCUtempNode3, &ALARA_3V3_Node3, &ALARA_5V_Node3};
std::array<MCU_SENSOR*, NUM_SENSORS> internalSensorArray4{&ALARA_HighPowerOut1_Node4, &ALARA_HighPowerOut2_Node4, &ALARA_HighPowerOut3_Node4, &ALARA_HighPowerOut4_Node4, &ALARA_HighPowerOut5_Node4, &ALARA_HighPowerOut6_Node4, &ALARA_HighPowerOut7_Node4, &ALARA_HighPowerOut8_Node4, &ALARA_HighPowerOut9_Node4, &ALARA_HighPowerOut10_Node4, &MCUtempNode4, &ALARA_3V3_Node4, &ALARA_5V_Node4};
std::array<MCU_SENSOR*, NUM_SENSORS> internalSensorArray7{&ALARA_HighPowerOut1_Node7, &ALARA_HighPowerOut2_Node7, &ALARA_HighPowerOut3_Node7, &ALARA_HighPowerOut4_Node7, &ALARA_HighPowerOut5_Node7, &ALARA_HighPowerOut6_Node7, &ALARA_HighPowerOut7_Node7, &ALARA_HighPowerOut8_Node7, &ALARA_HighPowerOut9_Node7, &ALARA_HighPowerOut10_Node7, &MCUtempNode7, &ALARA_3V3_Node7, &ALARA_5V_Node7};

#endif