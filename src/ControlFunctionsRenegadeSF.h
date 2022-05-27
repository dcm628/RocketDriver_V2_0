#ifndef CONTROLFUNCTIONSRENEGADESF_H
#define CONTROLFUNCTIONSRENEGADESF_H

#include "StateList.h"
#include "ControlCommands.h"
#include "ValveClass.h"
#include "PyroClass.h"
#include "AutoSequenceClass.h"
#include "SensorClass.h"
#include "TankPressControllerClass.h"
#include <array>

// Renegade SF Stand - somewhat clumsy to define again, not sure a cleaner way to integrate
#define NUM_VALVES 10
#define NUM_PYROS 2
#define NUM_AUTOSEQUENCES 1
#define NUM_SENSORS 20
#define NUM_TANKPRESSCONTROLLERS 3

// checks the state that was set at start-up and issues the appropriate command as current command
void startupStateCheck(const VehicleState& currentState, Command& currentCommand);
// state machine for operating all devices on the vehicle
void vehicleStateMachine(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, const std::array<TankPressController*, NUM_TANKPRESSCONTROLLERS>& tankPressControllerArray, bool &HaltFlag);
// state machine for the mission state (launch, ascent, apogee, descent et cetera)
void missionStateMachine(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, bool &HaltFlag);

// ----- Controller Functions -----
// Controls any devices from vehicleStateMachine that are on the fireing autosequence
void fireSequenceExecute(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, bool &HaltFlag);
// Controls any devices from vehicleStateMachine that are on the bang on/off tank pressurization
void tankPress(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray);
// Controls any devices from vehicleStateMachine that are on roll control RCS
void rollRCS(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray);
// Controls any devices from vehicleStateMachine that are on TVC system
void thrustVectorControl(VehicleState& currentState, VehicleState& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray);

#endif
