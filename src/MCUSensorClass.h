#ifndef MCUSENSORCLASS_H
#define MCUSENSORCLASS_H

#include <Arduino.h>
#include <string>
#include <bitset>
#include <ADC.h>


//using std::string;

///// MOVE THIS STUFF FOR NEW POLYMORPHISM SENSOR STRUCTURE /////
// enum for holding sensor types
enum SensorType
{
  pt,
  loadcellOneWireRead,
  KtypeTC,
  TtypeTC,
  rtd,
};

// enum for holding ADC input types
enum ADCType
{
  TeensyMCUADC,
  ADS1258,  //not in use yet
  ADS1263,  //not in use yet
  I2Cext, //currently used for RTD
};
/////

enum SensorState
{
  Off,
  Slow,
  Medium,
  Fast,
  Calibration, //doesn't currently work - new partially implemented feature
};

class MCU_SENSOR
{
  private:
    const uint32_t sensorID;
    const uint32_t sensorNodeID;                      // NodeID the valve is controlled by
    //const string sens_name;           //your own name for sensor to reference it
    SensorState sensorState;
    const uint8_t ADCinput;               //the input that will be read for this sensor that will get used in the ADC read main loop
    const uint32_t sampleRateSlowMode;        //the sample rate this given sensor will be read at
    const uint32_t sampleRateMedMode;         //the sample rate this given sensor will be read at
    const uint32_t sampleRateFastMode;        //the sample rate this given sensor will be read at
    const uint32_t sampleRateCalibrationMode = 10;        //the sample rate this given sensor will be read at
    uint32_t currentSampleRate;
    elapsedMicros timer;                      // timer for sensor timing operations
    uint32_t currentRawValue{};               // holds the current value for the sensor
    bool newSensorValueCheck;                      // Is the current raw value a new read that hasn't been sent yet?
    uint16_t currentCANtimestamp = 0;
    uint32_t currentTimestampSeconds = 0;
    uint32_t currentTimestampMicros = 0;
    //const uint8_t bitDepth;                   // bit depth of the sample, for output chopping?
    bool nodeIDCheck;                           // Whether this object should operate on this node
    bool internalMCUTemp;                       // Is this sensor the MCU internal temp
    
    uint32_t currentConvertedValue{};
    bool newConversionCheck;                      // Is the current raw value a new read that hasn't been sent yet?
    
    float linConvCoef1_m;                     // Base calibration coefficients
    float linConvCoef1_b;                     // Base calibration coefficients
    float linConvCoef2_m;                     // adjustment calibration coefficients (intended for application specifics like angle load cell mounting)
    float linConvCoef2_b;                     // adjustment calibration coefficients (intended for application specifics like angle load cell mounting)
    uint16_t rollingSensorArrayRaw[10];       // Array for doing averages of readings
    uint8_t currentRollingArrayPosition = 0;
    uint32_t currentCalibrationValue{};               // holds the current value for the sensor
    uint32_t currentRunningSUM = 0;

  public:
    // constructor 1,
    //MCU_SENSOR(uint32_t setSensorID, uint32_t setSensorNodeID, uint8_t setADCinput, uint32_t setSampleRateSlowMode, uint32_t setSampleRateMedMode, uint32_t setSampleRateFastMode, bool internalMCUTemp, uint32_t setCurrentSampleRate = 0, SensorState setSensorState = Off, bool setNodeIDCheck = false, bool setNewSensorValueCheck = false);
    // constructor 2, define attributes for conversions, gui updates, et cetera
    MCU_SENSOR(uint32_t setSensorID, uint32_t setSensorNodeID, uint8_t setADCinput, uint32_t setSampleRateSlowMode, uint32_t setSampleRateMedMode, uint32_t setSampleRateFastMode, bool internalMCUTemp, float setLinConvCoef1_m = 1, float setLinConvCoef1_b = 0, float setLinConvCoef2_m = 1, float setLinConvCoef2_b = 0, uint32_t setCurrentSampleRate = 0, SensorState setSensorState = Off, bool setNodeIDCheck = false, bool setNewSensorValueCheck = false, bool setNewConversionCheck = false);

    // Access functions defined in place
    uint32_t getSensorID(){return sensorID;}
    uint32_t getSensorNodeID(){return sensorNodeID;}
    uint32_t getADCinput(){return ADCinput;}
    uint32_t getCurrentSampleRate(){return currentSampleRate;}
    uint32_t getCurrentRawValue(){return currentRawValue;}
    uint32_t getCurrentConvertedValue(){return currentConvertedValue;}
    uint16_t getCANTimestamp(){return currentCANtimestamp;}
    uint32_t getTimestampSeconds(){return currentTimestampSeconds;}
    uint32_t getTimestampMicros(){return currentTimestampMicros;}
    uint8_t getCurrentRollingArrayPosition(){return currentRollingArrayPosition;}
    uint32_t getCurrentRollingAverage(){return currentCalibrationValue;}
    bool getNodeIDCheck(){return nodeIDCheck;}
    bool getNewSensorValueCheck(){return newSensorValueCheck;}
    bool getNewSensorConversionCheck(){return newConversionCheck;}


    // further fuctions defined in SensorClass.cpp
    void begin();                     // run in setup to get pins going
    
    // set functions, allows the setting of a variable
    void setState(SensorState newState) {sensorState = newState;} //every time a state is set, the timer should reset

    // set the Node ID Check bool function
    void setNodeIDCheck(bool updatedNodeIDCheck) {nodeIDCheck = updatedNodeIDCheck;}

    void setCurrentRawValue(uint32_t updateCurrentRawValue){currentRawValue = updateCurrentRawValue;}

    void setNewSensorValueCheck(bool updateNewSensorValueCheck){newSensorValueCheck = updateNewSensorValueCheck;}

    void setNewConversionCheck(bool updateNewConversionCheck){newConversionCheck = updateNewConversionCheck;}

    void setCANTimestamp(uint16_t CANTimestamp){currentCANtimestamp = CANTimestamp;}
    
    void setSYSTimestamp(uint32_t timestampSeconds, uint32_t timestampMicros){currentTimestampSeconds = timestampSeconds; currentTimestampMicros = timestampMicros;}

    //void setCurrentSampleRate(uint32_t updateCurrentSampleRate) {currentSampleRate = updateCurrentSampleRate; newSensorValueCheck = true; newConversionCheck = false;}
    void setCurrentSampleRate(uint32_t updateCurrentSampleRate) {currentSampleRate = updateCurrentSampleRate;}

    void resetTimer();                // resets timer to zero

    void read(ADC* adc);              // updates currentRawValue with current reading, using an activated ADC object

    void stateOperations();

    void linearConversion();          //Runs a linear sensor conversion 

    //void setRollingSensorArrayRaw(uint8_t arrayPosition, uint16_t sensorValueToArray)
    void setRollingSensorArrayRaw(uint8_t arrayPosition, uint16_t sensorValueToArray)
      {
        rollingSensorArrayRaw[arrayPosition] = sensorValueToArray;
        arrayPosition++;
      }

    void setCurrentCalibrationValue()
    {
    for (size_t i = 0; i < 10; i++)
    {
      currentRunningSUM = currentRunningSUM + rollingSensorArrayRaw[i];
    }
    currentCalibrationValue = currentRunningSUM / 10;
    }

};

// need to add differential read toggle somehow 
// - differential boolean variable that allows second input to be chosen or defaulted to correct option
// need to add a way to set other SENSOR types like the RTD sensors over I2C (we'd probably want multiple classes. ADCsensors, I2C sensors, SPI sensors etc - Mat)
// - maybe not the right call to roll into this? Hmm. Need to establish use of SENSOR class with sample rates and real read/sends to see what is better
// That will set me up for incorporating the external ADCs later



#endif