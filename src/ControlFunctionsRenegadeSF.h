#ifndef CONTROLFUNCTIONSRENEGADESF_H
#define CONTROLFUNCTIONSRENEGADESF_H

#include "StateList.h"
#include "ControlCommands.h"
#include "ValveClass.h"
#include "PyroClass.h"
#include "AutoSequenceClass.h"
#include "SensorClass.h"
#include <array>

// Renegade SF Stand - somewhat clumsy to define again, not sure a cleaner way to integrate
#define NUM_VALVES 10
#define NUM_PYROS 2
#define NUM_AUTOSEQUENCES 1
#define NUM_SENSORS 20

// checks the state that was set at start-up and issues the appropriate command as current command
void startupStateCheck(const State& currentState, Command& currentCommand);
// state machine for operating all devices on the vehicle

void vehicleStateMachine(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, bool &HaltFlag);
// state machine for the mission state (launch, ascent, apogee, descent et cetera)
void missionStateMachine(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, bool &HaltFlag);

// Controls any devices from vehicleStateMachine that are on the fireing autosequence
void fireSequenceExecute(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray, const std::array<AutoSequence*, NUM_AUTOSEQUENCES>& autoSequenceArray, const std::array<MCU_SENSOR*, NUM_SENSORS>& sensorArray, bool &HaltFlag);
// Controls any devices from vehicleStateMachine that are on the bang on/off tank pressurization
void bangerPress(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray);
// Controls any devices from vehicleStateMachine that are on roll control RCS
void rollRCS(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray);
// Controls any devices from vehicleStateMachine that are on TVC system
void thrustVectorControl(State& currentState, State& priorState, Command& currentCommand, const std::array<Valve*, NUM_VALVES>& valveArray);

/* // Used with Abort to override control of main valves and engine igniters
void haltFlagCheck(bool &haltFlag, const std::array<Valve*, NUM_VALVES>& valveArray, const std::array<Pyro*, NUM_PYROS>& pyroArray);
 */
#endif