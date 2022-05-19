#ifndef ACTUATORCLASS_H
#define ACTUATORCLASS_H

enum ActuatorType
{
    LinearServo,
    RotaryServo,
    LinearStepper,
    RotaryStepper,
    Pneumatic,
};

class Actuator
{
    private:
        const uint32_t actuatorID;                          // Valve ID number 
        const uint8_t actuatorNodeID;                      // NodeID the valve is controlled by
        const ActuatorType actuatorType;
        uint16_t controlSensor1Value;               // For use in control schemes, really a template placement pending needed number and type of samples
    
    public:

    // constructor
        Actuator(uint32_t setActuatorID, uint8_t setActuatorNodeID, ActuatorType setActuatorType);
    // a start up method, to set pins from within setup()
        void begin();

    // get functions, return the current value of that variable

    // set functions, allows the setting of a variable

    // functions with executables defined in ValveClasses.cpp
        void resetTimer();              // resets timer to zero, timer increments automatically in microseconds

    // ----- THIS METHOD TO BE RUN EVERY LOOP ------
    // stateOperations will check the current state of the valve and perform any actions that need to be performed
    // for example, if the valve is commanded to open, this needs to be run so that the valve can start opening
    // and it needs to be run every loop so that once enough time has pass the 
        void stateOperations();

    // Sensor pull in function for control
        void controlSensorFetch(uint16_t updateControlSensor1Value){controlSensor1Value = updateControlSensor1Value;}


};

#endif