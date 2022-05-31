#include "ALARASensorControllerClass.h"
#include <Arduino.h>

ALARAV2SensorController::ALARAV2SensorController(uint32_t controllerID, uint8_t setControllerNodeID, bool setBNO055_present, bool BMI085_present, bool KX134_1211_present, bool SAM_M8Q_GPS_present, bool MS5607_present, bool setNodeIDCheck)
                         : controllerID{setControllerID}, controllerNodeID{setControllerNodeID}, BNO055_present{setBNO055_present}, BMI085_present{setBMI085_present}, KX134_1211_present{setKX134_1211_present}, SAM_M8Q_GPS_present{setSAM_M8Q_GPS_present}, MS5607_present{setMS5607_present}, nodeIDCheck{setNodeIDCheck}
{
    // Instantiation stuff?
}

void ALARAV2SensorController::begin()
{
    if (nodeIDCheck)
    {
        // setup stuff?
    }
}

void ALARAV2SensorController::resetTimer()
{
    //timer = 0;
}

void ALARAV2SensorController::stateOperations()
{
    
}