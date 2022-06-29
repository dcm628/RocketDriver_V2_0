#ifndef ALARASENSORCONTROLLERCLASS_H
#define ALARASENSORCONTROLLERCLASS_H

#include <Arduino.h>
#include "ControllerStates.h"
#include "ValveStates.h"
#include "SensorStates.h"
#include "PyroStates.h"
#include "ALARASNConfigurations.h"

class ALARAV2SensorController
{
    private:
        const uint32_t controllerID;                        // Controller ID number - not super useful right now? Maybe for state reporting.
        const uint8_t controllerNodeID;                     // node the controller is running on
        bool nodeIDCheck;                           // Whether this object should operate on this node
        ALARAV2SensorControllerState state;
        ALARAV2SensorControllerState priorState;
        SensorState sensorStateInternal;                    // Use one sensor state inside here to toggle all sensors on controller
        SensorState sensorStateGNC;                    // Use one sensor state inside here to toggle all sensors on controller
        
        // bools for if the possible on board sensors are active
        // set default as false and flip to true based on board configuration and use case  
        bool BNO055_active;
        bool BMI085_active;
        bool KX134_1211_active;
        bool SAM_M8Q_GPS_active;
        bool MS5607_active;
        // On board MCU ADC reads for voltage rails
        bool ALARA_VINRail_active;
        bool ALARA_5VRail_active;
        bool ALARA_3V3Rail_active;
    public:
    
    // constructor
        ALARAV2SensorController(uint32_t setControllerID, uint8_t setControllerNodeID, bool setNodeIDCheck = false,
                                bool setBNO055_active = false, bool setBMI085_active = false, bool setKX134_1211_active = false, bool setSAM_M8Q_GPS_active = false, bool setMS5607_active = false,
                                bool setALARA_VINRail_active = false, bool setALARA_5VRail_active = false, bool setALARA_3V3Rail_active = false);
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
    // sensor bool set functions
        void setBNO055_active(bool ALARAsensorSetIN) {BNO055_active = ALARAsensorSetIN;}
        void setBMI085_active(bool ALARAsensorSetIN) {BMI085_active = ALARAsensorSetIN;}
        void setKX134_1211_active(bool ALARAsensorSetIN) {KX134_1211_active = ALARAsensorSetIN;}
        void setSAM_M8Q_GPS_active(bool ALARAsensorSetIN) {SAM_M8Q_GPS_active = ALARAsensorSetIN;}
        void setMS5607_active(bool ALARAsensorSetIN) {MS5607_active = ALARAsensorSetIN;}
        void setALARA_VINRail_active(bool ALARAsensorSetIN) {ALARA_VINRail_active = ALARAsensorSetIN;}
        void setALARA_5VRail_active(bool ALARAsensorSetIN) {ALARA_5VRail_active = ALARAsensorSetIN;}
        void setALARA_3V3Rail_active(bool ALARAsensorSetIN) {ALARA_3V3Rail_active = ALARAsensorSetIN;}

        void ALARAconfigurationSensorSet(ALARASN& thisALARA);

    // functions with executables defined in ValveClasses.cpp
        void resetTimer();              // resets timer to zero, timer increments automatically in microseconds

    // ----- THIS METHOD TO BE RUN EVERY LOOP ------
    // stateOperations will check the current state of the valve and perform any actions that need to be performed
    // for example, if the valve is commanded to open, this needs to be run so that the valve can start opening
    // and it needs to be run every loop so that once enough time has pass the 
        void stateOperations();

};

#endif