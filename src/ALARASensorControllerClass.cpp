#include "ALARASensorControllerClass.h"
#include <Arduino.h>

ALARAV2SensorController::ALARAV2SensorController(uint32_t setControllerID, uint8_t setControllerNodeID, bool setNodeIDCheck, bool setBNO055_active, bool setBMI085_active, bool setKX134_1211_active, bool setSAM_M8Q_GPS_active, bool setMS5607_active, bool setALARA_VINRail_active, bool setALARA_5VRail_active, bool setALARA_3V3Rail_active)
                         : controllerID{setControllerID}, controllerNodeID{setControllerNodeID}, nodeIDCheck{setNodeIDCheck}, BNO055_active{setBNO055_active}, BMI085_active{setBMI085_active}, KX134_1211_active{setKX134_1211_active}, SAM_M8Q_GPS_active{setSAM_M8Q_GPS_active}, MS5607_active{setMS5607_active}, ALARA_VINRail_active{setALARA_VINRail_active}, ALARA_5VRail_active{setALARA_5VRail_active}, ALARA_3V3Rail_active{setALARA_3V3Rail_active}
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

void ALARAV2SensorController::ALARAconfigurationSensorSet(ALARASN& thisALARA)
{
    setBNO055_active(thisALARA.BNO055_present);
    setBMI085_active(thisALARA.BMI085_present);
    setKX134_1211_active(thisALARA.KX134_1211_present);
    setSAM_M8Q_GPS_active(thisALARA.SAM_M8Q_GPS_present);
    setMS5607_active(thisALARA.SAM_M8Q_GPS_present);

    // This section is for board rev dependant sensors NOT listed explicitly in configurations
    if (static_cast<uint8_t>(thisALARA.boardRev) == 1)          // ALARA V2_0
    {
        ALARA_5VRail_active = true;
        ALARA_3V3Rail_active = true;
    }
    if (static_cast<uint8_t>(thisALARA.boardRev) == 2)          // ALARA V2_1
    {
        ALARA_VINRail_active = true;
        ALARA_5VRail_active = true;
        ALARA_3V3Rail_active = true;
    }
}