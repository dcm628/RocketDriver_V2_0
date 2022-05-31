#include "EngineControllerClass.h"
#include <Arduino.h>

EngineController::EngineController(uint32_t setControllerID, uint8_t setControllerNodeID, bool setNodeIDCheck) 
                                        : controllerID{setControllerID}, controllerNodeID{setControllerNodeID}, nodeIDCheck{setNodeIDCheck}
{
    // Instantiation stuff?
}

void EngineController::begin()
{
    if (nodeIDCheck)
    {
        // setup stuff?
    }
}

void EngineController::resetTimer()
{
    timer = 0;
}

void EngineController::stateOperations()
{
    switch (state)
    {
    case EngineControllerState::Passive:
        //don't do shit
        pilotMVFuelValveState = ValveState::CloseCommanded;
        pilotMVLoxValveState = ValveState::CloseCommanded;
        pneumaticVentState = ValveState::CloseCommanded;
        sensorState = SensorState::Slow;
        igniter1State = PyroState::OffCommanded;
        igniter2State = PyroState::OffCommanded;
        break;
    case EngineControllerState::Armed:
        //do shit
        if (priorState != EngineControllerState::Armed)
        {
        pilotMVFuelValveState = ValveState::CloseCommanded;
        pilotMVLoxValveState = ValveState::CloseCommanded;
        pneumaticVentState = ValveState::CloseCommanded;
        sensorState = SensorState::Fast;
        igniter1State = PyroState::OffCommanded;
        igniter2State = PyroState::OffCommanded;
        }
        break;
    case EngineControllerState::AutosequenceCommanded:
        // Arming turns sensor read rates up to operational levels before opening valves
        pilotMVFuelValveState = ValveState::FireCommanded;
        pilotMVLoxValveState = ValveState::FireCommanded;
        pneumaticVentState = ValveState::CloseCommanded;
        sensorState = SensorState::Fast;
        igniter1State = PyroState::FireCommanded;
        igniter2State = PyroState::FireCommanded;
        break;
    case EngineControllerState::Shutdown:
        if (priorState != EngineControllerState::Shutdown)
        {
        sensorState = SensorState::Fast;
        pilotMVFuelValveState = ValveState::FireCommanded;
        pilotMVLoxValveState = ValveState::FireCommanded;
        pneumaticVentState = ValveState::CloseCommanded;
        sensorState = SensorState::Fast;
        igniter1State = PyroState::FireCommanded;
        igniter2State = PyroState::FireCommanded;
        }
        break;
    case EngineControllerState::TestPassthrough:
        sensorState = SensorState::Slow;
        // How to handle test and offnominal pass through? figure out after I've got valveArray pointers passed functioning
        break;
    default:
        break;
    }
}
