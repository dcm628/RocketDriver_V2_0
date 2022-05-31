#ifndef CONTROLFUNCTIONSBABYSHARK_H
#define CONTROLFUNCTIONSBABYSHARK_H

#include "StateList.h"
#include "ControlCommands.h"
#include "ValveClass.h"
#include "PyroClass.h"
#include "AutoSequenceClass.h"
#include "SensorClass.h"
#include "TankPressControllerClass.h"
#include "EngineControllerClass.h"
#include <array>

// BabyShark Rocket
#define NUM_VALVES 12
#define NUM_PYROS 10
#define NUM_AUTOSEQUENCES 1
#define NUM_SENSORS 17              // Total system number of external propulsion sensors
#define NUMINTERNAL_SENSORS 13      // On EACH ALARA
#define NUM_TANKPRESSCONTROLLERS 3
#define NUM_ENGINECONTROLLERS 1

// checks the state that was set at start-up and issues the appropriate command as current command
void startupStateCheck(const VehicleState& currentState, Command& currentCommand);
// state machine for operating all devices on the vehicle
void vehicleStateMachine(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, const std::array<TankPressController*, NUM_TANKPRESSCONTROLLERS>& tankPressControllerArray, bool &HaltFlag);
// state machine for the mission state (launch, ascent, apogee, descent et cetera)
void missionStateMachine(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, bool &HaltFlag);

// ----- Controller Functions -----
void propulsionControllerDeviceUpdate(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, const std::array<TankPressController*, NUM_TANKPRESSCONTROLLERS>& tankPressControllerArray, const std::array<EngineController*, NUM_ENGINECONTROLLERS>& engineControllerArray, bool &HaltFlag);

#endif