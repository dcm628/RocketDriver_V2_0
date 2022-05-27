#include "TankPressControllerClass.h"
#include <Arduino.h>

TankPressController::TankPressController(uint8_t setControllerNodeID, uint32_t setTargetValue, const int setDomePressValveArrayPosition, const int setDomeVentValveArrayPosition, const int setTankVentValveArrayPosition, bool setNodeIDCheck) 
                                        : controllerNodeID{setControllerNodeID}, targetValue{setTargetValue}, domePressValveArrayPosition{setDomePressValveArrayPosition}, domeVentValveArrayPosition{setDomeVentValveArrayPosition}, tankVentValveArrayPosition{setTankVentValveArrayPosition}, nodeIDCheck{setNodeIDCheck}
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
        sensorState = SensorState::Slow;
        break;
    case TankPressControllerState::DomePressActive:
        //do shit
        sensorState = SensorState::Fast;
        domePressState = ValveState::OpenCommanded;
        domeVentState = ValveState::CloseCommanded;
        tankVentState = ValveState::CloseCommanded;
        break;
    case TankPressControllerState::Armed:
        // Arming turns sensor read rates up to operational levels before opening valves
        sensorState = SensorState::Fast;
        domePressState = ValveState::CloseCommanded;
        domeVentState = ValveState::CloseCommanded;
        tankVentState = ValveState::CloseCommanded;
        break;
    case TankPressControllerState::Vent:
        sensorState = SensorState::Fast;
        domePressState = ValveState::CloseCommanded;
        domeVentState = ValveState::OpenCommanded;
        tankVentState = ValveState::OpenCommanded;
        break;
    case TankPressControllerState::HiPressPassthroughVent:
        sensorState = SensorState::Fast;
        domePressState = ValveState::OpenCommanded;
        domeVentState = ValveState::CloseCommanded;
        tankVentState = ValveState::OpenCommanded;
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

// This function is how we pass the controller valve and other device states out to the device object states
void TankPressController::deviceSetOperations()
{

}