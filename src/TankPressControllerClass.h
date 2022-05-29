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
        const uint8_t controllerNodeID;
        bool nodeIDCheck;                           // Whether this object should operate on this node
        TankPressControllerState state;
        TankPressControllerState priorState;
        SensorState sensorState;                    // Use one sensor state inside here to toggle all sensors on controller
        elapsedMicros timer;                        // timer for the valve, used for changing duty cycles, in MICROS
        ValveState domePressState;
        ValveState domeVentState;
        ValveState tankVentState;
        const int domePressValveArrayPosition;      // For the pointers to the valves in valveArray
        const int domeVentValveArrayPosition;       // For the pointers to the valves in valveArray
        const int tankVentValveArrayPosition;       // For the pointers to the valves in valveArray
        uint32_t targetValue;
        uint32_t deadbandHighPoint;
        uint32_t deadbandLowPoint;
        uint32_t valveMinimumEnergizeTime;
        uint32_t valveMinimumDeenergizeTime;

    public:

    // constructor
        TankPressController(uint8_t setControllerNodeID, uint32_t setTargetValue, const int domePressValveArrayPosition, const int domeVentValveArrayPosition, const int tankVentValveArrayPosition, bool setNodeIDCheck = false);
    // a start up method, to set pins from within setup()
        void begin();

    // access functions defined in place

    // get functions, return the current value of that variable
        uint8_t getControllerNodeID(){return controllerNodeID;}
        bool getNodeIDCheck(){return nodeIDCheck;}
        uint32_t getTargetValue(){return targetValue;}
        TankPressControllerState getState(){return state;}
        ValveState getDomePressState(){return domePressState;}
        ValveState getDomeVentState(){return domeVentState;}
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

        //void deviceSetOperations();

};


#endif