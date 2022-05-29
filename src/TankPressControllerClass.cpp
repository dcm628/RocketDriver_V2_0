#include "TankPressControllerClass.h"
#include <Arduino.h>

TankPressController::TankPressController(uint32_t setControllerID, uint8_t setControllerNodeID, uint32_t setTargetValue, bool setNodeIDCheck) 
                                        : controllerID{setControllerID}, controllerNodeID{setControllerNodeID}, targetValue{setTargetValue}, nodeIDCheck{setNodeIDCheck}
{
    // Instantiation stuff?
}

void TankPressController::begin()
{
    if (nodeIDCheck)
    {
        // setup stuff?
    }
}

void TankPressController::resetTimer()
{
    timer = 0;
}

void TankPressController::stateOperations()
{
    switch (state)
    {
    case TankPressControllerState::Passive:
        //don't do shit
        primaryPressValveState = ValveState::CloseCommanded;
        pressLineVentState = ValveState::CloseCommanded;
        tankVentState = ValveState::CloseCommanded;
        sensorState = SensorState::Slow;
        break;
    case TankPressControllerState::DomePressActive:
        //do shit
        if (priorState != TankPressControllerState::DomePressActive)
        {
        sensorState = SensorState::Fast;
        primaryPressValveState = ValveState::OpenCommanded;
        pressLineVentState = ValveState::CloseCommanded;
        tankVentState = ValveState::CloseCommanded;
        }
        break;
    case TankPressControllerState::Armed:
        // Arming turns sensor read rates up to operational levels before opening valves
        sensorState = SensorState::Fast;
        primaryPressValveState = ValveState::CloseCommanded;
        pressLineVentState = ValveState::CloseCommanded;
        tankVentState = ValveState::CloseCommanded;
        break;
    case TankPressControllerState::Vent:
        if (priorState != TankPressControllerState::Vent)
        {
        sensorState = SensorState::Fast;
        primaryPressValveState = ValveState::CloseCommanded;
        pressLineVentState = ValveState::OpenCommanded;
        tankVentState = ValveState::OpenCommanded;
        }
        break;
    case TankPressControllerState::HiPressPassthroughVent:
        if (priorState != TankPressControllerState::HiPressPassthroughVent)
        {
        sensorState = SensorState::Fast;
        primaryPressValveState = ValveState::OpenCommanded;
        pressLineVentState = ValveState::CloseCommanded;
        tankVentState = ValveState::OpenCommanded;
        }
        break;
    case TankPressControllerState::TestPassthrough:
        sensorState = SensorState::Slow;
        // How to handle test and offnominal pass through? figure out after I've got valveArray pointers passed functioning
        break;
    case TankPressControllerState::AutosequenceCommanded:
        // If specific press routine is on autosequence, include a state switch on timer in here
        break;
    default:
        break;
    }
}
