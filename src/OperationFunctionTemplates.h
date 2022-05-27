#ifndef OPERATIONFUNCTIONTEMPLATES_H
#define OPERATIONFUNCTIONTEMPLATES_H

#include <array>
//#include <bitset>
//#include <FlexCAN.h>
//#include <ADC.h>

// This contains some of the functions to be used during operations they are templates, and so defined in the header. BEWARE

//  CALL THIS FUNCTION EVERY LOOP 
    // This function takes the array of pointers that point to the valve objects, and then calls the .stateOperations() method for each valve
    // Make sure valveArray is an array of pointers, as defined in ValveDefinitions.h
template <typename T, std::size_t size>
void valveTasks(const std::array<T, size>& valveArray, uint8_t& nodeIDReadIn)
{
    // iterate through valve array and run the stateOperations method
    for(auto valve : valveArray)
    {
    
        if (valve->getValveNodeID() == nodeIDReadIn)
        {
            valve->stateOperations();
            //Serial.print("LoopRan");
        }

    }
}

template <typename T, std::size_t size>
void pyroTasks(const std::array<T, size>& pyroArray, uint8_t& nodeIDReadIn)
{
    // iterate through valve array and run the stateOperations method
    for(auto pyro : pyroArray)
    {
        
    if (pyro->getPyroNodeID() == nodeIDReadIn)
        {
            pyro->stateOperations();
            //Serial.print("LoopRan");
        }
    }
}

template <typename T, std::size_t size>
void tankPressControllerTasks(const std::array<T, size>& tankPressControllerArray, uint8_t& nodeIDReadIn)
{
    // iterate through valve array and run the stateOperations method
    for(auto tankPressController : tankPressControllerArray)
    {
    
        if (tankPressController->getValveNodeID() == nodeIDReadIn)
        {
            tankPressController->stateOperations();
            tankPressController->deviceSetOperations();
            //Serial.print("LoopRan");
        }
    }
}

template <typename T, std::size_t size>
void autoSequenceTasks(const std::array<T, size>& autoSequenceArray, uint8_t& nodeIDReadIn)
{
    // iterate through valve array and run the stateOperations method
    for(auto autoSequence : autoSequenceArray)
    {
        
    if (autoSequence->getHostNodeID() == nodeIDReadIn)
        {
            autoSequence->stateOperations();
            //Serial.print("LoopRan");
        }
    }
}

template <typename T, std::size_t size>
void sensorTasks(const std::array<T, size>& sensorArray, ADC*adc, uint32_t& secondsRD,uint32_t& microsecondsRD, uint8_t& nodeIDReadIn)
{
    // iterate through valve array and run the stateOperations method
    for(auto sensor : sensorArray)
    {
    
        if (sensor->getSensorNodeID() == nodeIDReadIn)
        {
            sensor->stateOperations();
            //Serial.print("LoopRan");
            sensor->read(adc);
            sensor->setSYSTimestamp(secondsRD, microsecondsRD);
            sensor->linearConversion();
        }
        else if (nodeIDReadIn == 6)
        {
            sensor->linearConversion();
        }
    }
}



// CALL THIS FUNCTION ONCE IN SETUP, THIS SETS THE VALVE PINMODES
    // make sure to pass this function valveArray, as defined in ValveDefinitions.h
template <typename T, std::size_t size>
void valveSetUp(const std::array<T, size>& valveArray)
{
    // iterate through valve array and run the stateOperations method
    for(auto valve : valveArray)
    {
        valve->begin();
        //Serial.print("LoopRan");
    }
}

template <typename T, std::size_t size>
void pyroSetUp(const std::array<T, size>& pyroArray)
{
    // iterate through valve array and run the stateOperations method
    for(auto pyro : pyroArray)
    {
        pyro->begin();
        //Serial.print("LoopRan");
    }
}

template <typename T, std::size_t size>
void autoSequenceSetUp(const std::array<T, size>& autoSequenceArray)
{
    // iterate through valve array and run the stateOperations method
    for(auto autoSequence : autoSequenceArray)
    {
        autoSequence->begin();
        //Serial.print("LoopRan");
    }
}

template <typename T, std::size_t size>
void sensorSetUp(const std::array<T, size>& sensorArray)
{
    // iterate through valve array and run the stateOperations method
    for(auto sensor : sensorArray)
    {
        sensor->begin();
        //Serial.print("LoopRan");
    }
}

void MCUADCSetup(ADC* adc)
{ 
//Ideally get some conditionals here for which MCU it is so this is compatible at least also with Teensy LC

///// ADC0 /////
  // reference can be ADC_REFERENCE::REF_3V3, ADC_REFERENCE::REF_1V2 or ADC_REFERENCE::REF_EXT.
  //adc->setReference(ADC_REFERENCE::REF_1V2, ADC_0); // change all 3.3 to 1.2 if you change the reference to 1V2

  adc->adc0->setReference(ADC_REFERENCE::REF_1V2);
  adc->adc0->setAveraging(8);                                    // set number of averages
  adc->adc0->setResolution(16);                                   // set bits of resolution
  adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED_16BITS); // change the conversion speed
  adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::HIGH_SPEED);     // change the sampling speed
  adc->adc0->recalibrate();

///// ADC1 /////
  adc->adc1->setReference(ADC_REFERENCE::REF_1V2);
  adc->adc1->setAveraging(8);                                    // set number of averages
  adc->adc1->setResolution(16);                                   // set bits of resolution
  adc->adc1->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED_16BITS); // change the conversion speed
  adc->adc1->setSamplingSpeed(ADC_SAMPLING_SPEED::HIGH_SPEED);     // change the sampling speed
  adc->adc1->recalibrate();

}

template <typename T, std::size_t size>
void autoSequenceValveUpdate(const std::array<T, size>& valveArray, int64_t& fireCurrentCountdown)
{
    // iterate through valve array and run the stateOperations method
    for (auto valve : valveArray)
    {
        if (valve->getState() != (ValveState::FireCommanded))
        {
            valve->setFireCommandBool(false);
        }        
        if (fireCurrentCountdown >= valve->getFireSequenceTime())
        {
            valve->setFireCommandBool(true);
        }    
    }
}

template <typename T, std::size_t size>
void autoSequencePyroUpdate(const std::array<T, size>& pyroArray, int64_t& fireCurrentCountdown)
{
    // iterate through pyro array and run the stateOperations method
    for(auto pyro : pyroArray)
    {
        if (pyro->getState() != (PyroState::FireCommanded))
        {
            pyro->setFireCommandBool(false);
        }
        if (fireCurrentCountdown >= pyro->getFireSequenceTime())
        {
/*         Serial.print("fireCurrentCountdown >= ");
        Serial.print(fireCurrentCountdown);
        Serial.print(", getFireSequenceTime");
        Serial.println(pyro->getFireSequenceTime()); */
        
            pyro->setFireCommandBool(true);
        }
        
    }

}

template <typename T, std::size_t size>
void ValveNodeIDCheck(const std::array<T, size>& valveArray, uint8_t nodeIDfromMain)
{
    // iterate through valve array and run the stateOperations method
    for (auto valve : valveArray)
    {
        if (valve->getValveNodeID() == nodeIDfromMain)
        {
            valve->setNodeIDCheck(true);
        }
    }
}

template <typename T, std::size_t size>
void PyroNodeIDCheck(const std::array<T, size>& pyroArray, uint8_t nodeIDfromMain)
{
    // iterate through pyro array and run the stateOperations method
    for (auto pyro : pyroArray)
    {
        if (pyro->getPyroNodeID() == nodeIDfromMain)
        {
            pyro->setNodeIDCheck(true);
        }
    }
}

template <typename T, std::size_t size>
void SensorNodeIDCheck(const std::array<T, size>& sensorArray, uint8_t nodeIDfromMain)
{
    // iterate through sensor array and run the stateOperations method
    for (auto sensor : sensorArray)
    {
        if (sensor->getSensorNodeID() == nodeIDfromMain)
        {
            sensor->setNodeIDCheck(true);
        }
        else if (nodeIDfromMain == 6)    //Logger nodeID so it generates array for all sensors
        {
            sensor->setNodeIDCheck(true);
        }
    }
}

template <typename T, std::size_t size>
void CAN2SensorArraySend(FlexCAN& CANbus, const std::array<T, size>& sensorArray, uint8_t nodeIDfromMain, bool ConvertedBool)
{
    static CAN_message_t msgOut;
    msgOut.ext = 1;                 // Turn ON Extended ID to pack timestamp in the extra bits
    msgOut.len = 2;
    uint32_t sensorValueToSend;
    
    for(auto sensor : sensorArray)
    {
        if (sensor->getNewSensorConversionCheck())
        {
            msgOut.id = (sensor->getSensorID() + (sensor->getCANTimestamp()))<<11; //packing IDA as normal CAN ID/sensorID and IDB as CAN timestamp
            if (!ConvertedBool)
            {
                sensorValueToSend = sensor->getCurrentRawValue();
            }
            else
            {
                sensorValueToSend = sensor->getCurrentConvertedValue();
            }
            
            
            msgOut.buf[0] = sensorValueToSend;
            msgOut.buf[1] = (sensorValueToSend >> 8);

            // write message to bus
            CANbus.write(msgOut);

            // For now don't reset the conversion check, let GUI repeat messages
            //sensor->setNewConversionCheck(false);
            //sensor->setNewSensorValueCheck(false);
/*             Serial.print("Sensor ID");
            Serial.print(msgOut.id);
            Serial.print("Sensor Value");
            Serial.println(sensorValueToSend); */
            {
                // add write error handling here, for now it does nothing
            }
        }
    }
}

template <typename T, std::size_t size>
void CAN2AutosequenceTimerReport(FlexCAN& CANbus, const std::array<T, size>& autoSequenceArray, bool & haltFlag, uint8_t & nodeID)
{
    elapsedMicros AutoSequenceReportTimer;
    
    if (AutoSequenceReportTimer >= 100000)
    {
    // build message
        static CAN_message_t msgOut;
        msgOut.ext = 0;
        //change ID format to be better and match my updated plan
        for(auto autoSequence : autoSequenceArray)
        if (autoSequence->getHostNodeID() == nodeID)
        {
            {
                msgOut.id = nodeID + 32;  // with 16 possible nodes in ID format this makes the CAN ID possible go up to 31, lowest sensor ID in current format is 50.
                msgOut.len = 8;
                int64_t autosequenceTimer = autoSequence->getCurrentCountdown();
                uint8_t autosequenceTimerStateEnumToInt = static_cast<uint8_t>(autoSequence->getAutoSequenceState());

/*                 Serial.print("Autosequence: State : ");
                Serial.print(autosequenceTimerStateEnumToInt);
                Serial.print(" Timer : ");
                Serial.print(autosequenceTimer);
                Serial.println(); */

                msgOut.buf[0] = autosequenceTimerStateEnumToInt;
                msgOut.buf[1] = autosequenceTimer;
                msgOut.buf[2] = (autosequenceTimer >> 8);
                msgOut.buf[3] = (autosequenceTimer >> 16);
                msgOut.buf[4] = (autosequenceTimer >> 24);
                msgOut.buf[5] = (autosequenceTimer >> 32);
                msgOut.buf[6] = (autosequenceTimer >> 40);
                msgOut.buf[7] = (autosequenceTimer >> 48);
                
                // write message to bus
                CANbus.write(msgOut);
            }    
            {
                // add write error handling here, for now it does nothing
            }
            AutoSequenceReportTimer = 0;
        }
        }
}

// General Level State Report - covers overall state of whole node
template <typename T,std::size_t sizeT, typename U,std::size_t sizeU>
void CAN2PropSystemStateReport(FlexCAN& CANbus, VehicleState& currentState, Command& currentCommand, const std::array<T, sizeT>& valveArrayIn, const std::array<U, sizeU>& pyroArrayIn, bool& haltFlag, uint8_t& nodeID)
{
elapsedMicros PropSysReportTimer;

uint8_t engineNodeValveNum = 4;
uint8_t propNodeValveNum = 6;
uint8_t engineNodePyroNum = 2;
uint8_t propNodePyroNum = 0;


uint8_t vavleArrayCount;
uint8_t pyroArrayCount;
uint8_t totalArrayCount;

if (PropSysReportTimer >= 100000)
{
    //Serial.println(now());
    //Hardcoded array iterator sizes because I'm not smart enough to fix the auto arrays yet
    if (nodeID == 2)
    {
        vavleArrayCount = engineNodeValveNum;
        pyroArrayCount = engineNodePyroNum;
    }
    else if (nodeID == 3)
    {
        vavleArrayCount = propNodeValveNum;
        pyroArrayCount = propNodePyroNum;
    }    
    else
    {
        vavleArrayCount = 7;
        pyroArrayCount = 0;
    }
    
    totalArrayCount = vavleArrayCount + pyroArrayCount;

    // build message
        static CAN_message_t msgOut1;
        static CAN_message_t msgOut2;
        msgOut1.ext = 0;
        msgOut2.ext = 0;
        msgOut1.id = nodeID;            //Make this more specific later
        msgOut2.id = nodeID + 16;       //Make this more specific later

        // CAN BYTE - System state and Valve Safety Enable States
        int8_t currentStateEnumToInt = static_cast<int8_t>(currentState);
        //Serial.print("static cast of StateEnumToInt: ");
        //Serial.println(currentStateEnumToInt);

        msgOut1.buf[0] = currentStateEnumToInt;
        //msgOut.buf[0] = 111;

        //Valve State information bytes
        uint8_t canByte = 1;    //starts the valve state bytes skipping 1 byte(s) first
            //to limit overflow of CAN2.0 max message bytes
        
        //while (canByte <=7)
        //{
            //while (canByte <=vavleArrayCount) //HARDCODING number of valves on engine node so it doesn't loop
            //{
            
    /*         // iterate through valve array - attempting to do it different way
            for (valveArray)
            {

            } */
            
            
            // iterate through valve array 
            for(auto valve : valveArrayIn)
            {
                
                    if (valve->getValveNodeID() == nodeID)
                    {
                    uint8_t valveID = static_cast<uint8_t>(valve->getValveID());    
                    uint8_t ValveStateEnumToInt = static_cast<uint8_t>(valve->getState());
                    uint8_t ShiftedValveStateEnumToInt = (ValveStateEnumToInt<<5);
                    
                    if (canByte <= 7)
                    {
                    msgOut1.buf[canByte] = valveID + ShiftedValveStateEnumToInt;
                    }
                    else if (canByte <= totalArrayCount&&canByte > 7)
                    {
                    msgOut2.buf[canByte-7] = valveID + ShiftedValveStateEnumToInt;
                    }
                    
                    //msgOut1.buf[canByte] = valveID + ShiftedValveStateEnumToInt;
                    Serial.print("ValveID: ");
                    Serial.print(valveID);
                    Serial.print( ": ValveState: ");
                    Serial.print(ValveStateEnumToInt);
                    Serial.print(": ");
                    //Serial.print(ShiftedValveStateEnumToInt);
                    //Serial.print("CANbyte: ");
                    Serial.println(canByte);
                    canByte++;
                    }
                //canByte++;
                
            }
            //}
            //while (canByte <=pyroArrayCount) //HARDCODING number of valves on engine node so it doesn't loop
            //{
            for(auto pyro : pyroArrayIn)
            {
                    if (pyro->getPyroNodeID() == nodeID)
                    {
                    uint8_t pyroID = static_cast<uint8_t>(pyro->getPyroID());    
                    uint8_t PyroStateEnumToInt = static_cast<uint8_t>(pyro->getState());
                    uint8_t ShiftedPyroStateEnumToInt = (PyroStateEnumToInt<<5);

                    if (canByte <= 7)
                    {
                    msgOut1.buf[canByte] = pyroID + ShiftedPyroStateEnumToInt;
                    }
                    else if (canByte <= totalArrayCount&&canByte > 7)
                    {
                    msgOut2.buf[canByte-7] = pyroID + ShiftedPyroStateEnumToInt;
                    }

                    //msgOut1.buf[canByte] = pyroID + ShiftedPyroStateEnumToInt;
                    Serial.print("PyroID: ");
                    Serial.print(pyroID);
                    Serial.print( ": PyroState: ");
                    Serial.print(PyroStateEnumToInt);
                    Serial.print(": ");
                    Serial.println(canByte);
                    canByte++;
                    }
            }
            //}
        //}
        
        // write message to bus
        Serial.print("ID: ");
        Serial.print(msgOut1.id);
        Serial.print(": ");
        for (size_t ii = 0; ii < 8; ii++)
        {
            Serial.print(msgOut1.buf[ii]);
            Serial.print(": ");
        }        Serial.print("ID: ");
        Serial.print(msgOut2.id);
        Serial.print(": ");
        for (size_t ii = 0; ii < 8; ii++)
        {
            Serial.print(msgOut2.buf[ii]);
            Serial.print(": ");
        }
        
        Serial.println();
        msgOut1.len = 8;
        msgOut2.len = pyroArrayCount-6;
        CANbus.write(msgOut1);
        if (totalArrayCount >= 7)
        {
        CANbus.write(msgOut2);
        }
        
        canByte = 1;
        
        PropSysReportTimer = 0;

    {
        // add write error handling here, for now it does nothing
    }
    }
//return ;
}


#endif