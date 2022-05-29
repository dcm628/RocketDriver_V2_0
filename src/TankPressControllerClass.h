#ifndef TANKPRESSCONTROLLERCLASS_H
#define TANKPRESSCONTROLLERCLASS_H

#include <Arduino.h>
#include "ControllerStates.h"
//#include <array>
#include "ValveStates.h"    // this is included also in ValveClass.h, hopefully it doesn't get me in trouble
#include "SensorStates.h"

class TankPressController
{
    private:
        const uint32_t controllerID;                          // Controller ID number 
        const uint8_t controllerNodeID;
        bool nodeIDCheck;                           // Whether this object should operate on this node
        TankPressControllerState state;
        TankPressControllerState priorState;
        SensorState sensorState;                    // Use one sensor state inside here to toggle all sensors on controller
        elapsedMicros timer;                        // timer for the valve, used for changing duty cycles, in MICROS
        ValveState primaryPressValveState;
        ValveState pressLineVentState;
        ValveState tankVentState;
        uint32_t targetValue;
        uint32_t deadbandHighPoint;
        uint32_t deadbandLowPoint;
        uint32_t valveMinimumEnergizeTime;
        uint32_t valveMinimumDeenergizeTime;

    public:

    // constructor
        TankPressController(uint32_t controllerID, uint8_t setControllerNodeID, uint32_t setTargetValue, bool setNodeIDCheck = false);
    // a start up method, to set pins from within setup()
        void begin();

    // access functions defined in place

    // get functions, return the current value of that variable
        uint32_t getControllerID(){return controllerID;}
        uint8_t getControllerNodeID(){return controllerNodeID;}
        bool getNodeIDCheck(){return nodeIDCheck;}
        uint32_t getTargetValue(){return targetValue;}
        TankPressControllerState getState(){return state;}
        ValveState getPrimaryPressValveState(){return primaryPressValveState;}
        ValveState getPressLineVentState(){return pressLineVentState;}
        ValveState getTankVentState(){return tankVentState;}
    
    // set functions, allows the setting of a variable
    // set the Node ID Check bool function
        void setNodeIDCheck(bool updatedNodeIDCheck) {nodeIDCheck = updatedNodeIDCheck;}
    // controller state set function
        void setState(TankPressControllerState newState)
            {
                if (newState != state)
                {
                    priorState = state;
                }
                state = newState;
            }
    // functions with executables defined in ValveClasses.cpp
        void resetTimer();              // resets timer to zero, timer increments automatically in microseconds

    // ----- THIS METHOD TO BE RUN EVERY LOOP ------
    // stateOperations will check the current state of the valve and perform any actions that need to be performed
    // for example, if the valve is commanded to open, this needs to be run so that the valve can start opening
    // and it needs to be run every loop so that once enough time has pass the 
        void stateOperations();

};


#endif