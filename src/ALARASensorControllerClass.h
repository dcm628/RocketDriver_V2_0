#ifndef ALARASENSORCONTROLLERCLASS_H
#define ALARASENSORCONTROLLERCLASS_H

#include <Arduino.h>
#include "ControllerStates.h"
#include "ValveStates.h"
#include "SensorStates.h"
#include "PyroStates.h"

class ALARAV2SensorController
{
    private:
        const uint32_t controllerID;                          // Controller ID number 
        const uint8_t controllerNodeID;
        bool nodeIDCheck;                           // Whether this object should operate on this node
        ALARAV2SensorControllerState state;
        ALARAV2SensorControllerState priorState;
        SensorState sensorStateInternal;                    // Use one sensor state inside here to toggle all sensors on controller
        SensorState sensorStateGNC;                    // Use one sensor state inside here to toggle all sensors on controller

        bool BNO055_present;
        bool BMI085_present;
        bool KX134_1211_present;
        bool SAM_M8Q_GPS_present;
        bool MS5607_present;

    public:
    
    // constructor
        ALARAV2SensorController(uint32_t setControllerID, uint8_t setControllerNodeID, bool setBNO055_present, bool setBMI085_present, bool setKX134_1211_present, bool setSAM_M8Q_GPS_present, bool setMS5607_present, bool setNodeIDCheck = false);
    // a start up method, to set pins from within setup()
        void begin();

    // get functions, return the current value of that variable
        uint32_t getControllerID(){return controllerID;}
        uint8_t getControllerNodeID(){return controllerNodeID;}
        bool getNodeIDCheck(){return nodeIDCheck;}
        ALARAV2SensorControllerState getState(){return state;}

    // set functions, allows the setting of a variable
    // set the Node ID Check bool function
        void setNodeIDCheck(bool updatedNodeIDCheck) {nodeIDCheck = updatedNodeIDCheck;}
    // controller state set function
        void setState(ALARAV2SensorControllerState newState)
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