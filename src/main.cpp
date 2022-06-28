// RocketDriver V2.0 Propulsion Control and Data Acquisition - Embedded System Node Program
// Originally by Dan Morgan and Mat Arnold
// For Renegade, Beach Launch Team, Brandon Summers' personal machinations and more
//
//
// -------------------------------------------------------------
// Use top level define conditional to determine which system the code is operating
// Maintain definition header sets for a given propulsion system and update here accordingly
#define RENEGADESF

//----- Renegade Static Fire Stand -----
#ifdef RENEGADESF
#include "ValveDefinitionsRenegadeSF.h"
#include "PyroDefinitionsRenegadeSF.h"
#include "AutoSequenceDefinitionsRenegadeSF.h"
#include "SensorDefinitionsRenegadeSF.h"
#include "TankPressControllerDefinitionsRenegadeSF.h"
#include "EngineControllerDefinitionsRenegadeSF.h"
#include "ControlFunctionsRenegadeSF.h"
#include "ALARASensorControllerDefinitionsRenegadeSF.h"
#endif

//----- BabyShark -----
#ifdef BABYSHARK
#include "ValveDefinitionsRenegadeBabyShark.h"
#include "PyroDefinitionsRenegadeBabyShark.h"
#include "AutoSequenceDefinitionsRenegadeBabyShark.h"
#include "SensorDefinitionsRenegadeBabyShark.h"
#include "TankPressControllerDefinitionsBabyShark.h"
#include "EngineControllerDefinitionsBabyShark.h"
#include "ControlFunctionsRenegadeBabyShark.h"
#include "ALARASensorControllerDefinitionsBabyShark.h"
#endif
// -------------------------------------------------------------

#include <Arduino.h>
#include <EEPROM.h>
#include <ADC.h>
#include <ADC_util.h>
#include <FlexCAN.h>
#include <kinetis_flexcan.h>
#include <WireKinetis.h>
#include <Wire.h>
#include "Adafruit_MCP9808.h"
#include <InternalTemperature.h>
#include <array>
#include <string>
#include <list>
using std::string;

#include "ALARAUtilityFunctions.h"
#include "ToMillisTimeTracker.h"
#include "CANRead.h"
#include "CANWrite.h"
#include "OperationFunctionTemplates.h"
#include "ALARApinDefines.h"

//Trying to figure out RTC stuff with these libs
#include <TimeLib.h>
#include <DS1307RTC.h>

#define PROPULSIONSYSNODEIDPRESET 3;     //NOT in use normally, for testing with the address IO register inactive

// Timer for setting main loop debugging print rate
elapsedMillis mainLoopTestingTimer;

//For use in doing serial inputs as CAN commands for testing
uint8_t fakeCANmsg;

bool localNodeResetFlag = false; //flag to trigger register reset from commanded reset over CAN
bool abortHaltFlag; //creates halt flag that is a backup override of state machine

///// NODE DECLARATION /////
//default sets to max nodeID intentionally to be bogus until otherwise set
uint8_t ALARAnodeID;                      // ALARA hardware node address
uint8_t ALARAnodeIDfromEEPROM;            //nodeID read out of EEPROM
bool nodeIDdeterminefromEEPROM;           //boolean flag for if startup is to run the nodeID detect read
uint32_t nodeIDdeterminefromEEPROM_errorFlag;
uint8_t PropulsionSysNodeID;              //engine node = 2, prop node = 3, Pasafire node = 8
uint8_t PropulsionSysNodeIDfromEEPROM;    //PropulsionSysNodeID read out of EEPROM
uint32_t PropulsionSysNodeIDfromEEPROM_errorFlag;    //PropulsionSysNodeID read out of EEPROM

///// WATCHDOG SYSTEM /////
elapsedMillis propulsionControlWatchdog;                  // Watchdog timer that must be reset by ground control over bus to prevent an autovent
uint32_t propulsionControlWatchdogVentTime = 120000;   // 120 seconds in millis gives two minutes to reestablish control before autovent, DISABLE IN FLIGHT

///// ADC /////
ADC* adc = new ADC();

///// LED /////
elapsedMillis sinceLED;

///// CAN /////
CAN_message_t message;
CAN_message_t rxmsg;
CAN_message_t extended;
bool CANSensorReportConverted = false;

const int CAN2busSpeed = 500000; // CAN2.0 baudrate - do not set above 500000 for full distance run bunker to pad

bool startup{true}; // bool for storing if this is the first loop on startup, ESSENTIAL FOR STATE MACHINE OPERATION (maybe not anymore?)

uint32_t loopCount {0};// for debugging

// Set the global command, and global state
Command currentCommand{command_NOCOMMAND}; 
VehicleState currentVehicleState{VehicleState::passive};
VehicleState priorVehicleState;
MissionState currentMissionState(MissionState::passive);
MissionState priorMissionState;

uint32_t vehicleStateAddressfromEEPROM_errorFlag;
uint32_t missionStateAddressfromEEPROM_errorFlag;

//AutoSequence stuff for main
int64_t currentCountdownForMain;

////// Set EEPROM addresses
// Change these up occasionally to reduce write cycle wear on the same bytes
// I could use EEPROM itself to store current start byte of my data and automate iterating this. Good idea for future upgrade.
uint16_t vehicleStateAddress1{4};
uint16_t vehicleStateAddress2{5};
uint16_t vehicleStateAddress3{6};
uint16_t missionStateAddress1{7};
uint16_t missionStateAddress2{8};
uint16_t missionStateAddress3{9};
uint16_t PropulsionSysNodeIDAddress1{16};
uint16_t PropulsionSysNodeIDAddress2{17};
uint16_t PropulsionSysNodeIDAddress3{18};
uint16_t nodeIDDetermineAddress1{19};
uint16_t nodeIDDetermineAddress2{20};
uint16_t nodeIDDetermineAddress3{21};

///// Temp Sensor for TC Cold Junction /////        ----- Move into sensor classes (if this is even retained)
//Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
//int roundedtemp;

//-------------------------------------------------------//
void setup() {
  startup = true;   // Necessary to set startup to true for the code loop so it does one startup loop for the state machine before entering regular loop behavior

  // ----- MUX Setups for ALARA -----
  // Board Addressing MUX
  MUXSetup(true, ALARA_DIGITAL_ADDRESS_1, ALARA_DIGITAL_ADDRESS_2, ALARA_DIGITAL_ADDRESS_3, ALARA_DIGITAL_ADDRESS_4);
  // NOR Flash CS pin MUX
  MUXSetup(false, ALARA_NOR_S0, ALARA_NOR_S1, ALARA_NOR_S2);

  // -----Read Last State off eeprom and update -----
  currentVehicleState = static_cast<VehicleState>(tripleEEPROMread(vehicleStateAddress1, vehicleStateAddress2, vehicleStateAddress3, vehicleStateAddressfromEEPROM_errorFlag));
  currentMissionState = static_cast<MissionState>(tripleEEPROMread(missionStateAddress1, missionStateAddress2, missionStateAddress3, missionStateAddressfromEEPROM_errorFlag));
  
  PropulsionSysNodeIDfromEEPROM = tripleEEPROMread(PropulsionSysNodeIDAddress1, PropulsionSysNodeIDAddress2, PropulsionSysNodeIDAddress3, PropulsionSysNodeIDfromEEPROM_errorFlag);
  nodeIDdeterminefromEEPROM = tripleEEPROMread(nodeIDDetermineAddress1, nodeIDDetermineAddress2, nodeIDDetermineAddress3, nodeIDdeterminefromEEPROM_errorFlag);
  startupStateCheck(currentVehicleState, currentCommand);

  // ----- Run the Node ID Detection Function -----
  //nodeID = NodeIDDetect(nodeID, nodeIDdeterminefromEEPROM, nodeIDfromEEPROM); // - OVERHAUL WITH NEW FUNCTION AND SYSTEM
  PropulsionSysNodeID = PROPULSIONSYSNODEIDPRESET;       //For manually assigning NodeID isntead of the address read, make sure to comment out for operational use
  // Write 0 to byte for nodeIDDetermineAddress after reading it after a reset
  tripleEEPROMwrite(0, nodeIDDetermineAddress1, nodeIDDetermineAddress2, nodeIDDetermineAddress3);

  // ----- Hardware Abort Pin Setup ----- NOT CURRENTLY IN USE
  // This hardware abort allows us to command the Teensy to reboot itself by pulling the reset pin to ground
/*   pinMode(pin::reset, OUTPUT);
  digitalWrite(pin::reset, 1);
  pinMode(pin::abort, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(pin::abort), abortReset, RISING);  */



  // -----Initialize ADCs-----
  MCUADCSetup(adc);

  // -----Run Valve PropulsionSysNodeID Check-----
  ValveNodeIDCheck(valveArray, PropulsionSysNodeID);

  // -----Run Valve PropulsionSysNodeID Check-----
  PyroNodeIDCheck(pyroArray, PropulsionSysNodeID);

  // -----Run Sensor PropulsionSysNodeID Check-----
  SensorNodeIDCheck(sensorArray, PropulsionSysNodeID);

  // -----Run Valve Setup-----
  valveSetUp(valveArray);

  // -----Run Valve Setup-----
  pyroSetUp(pyroArray);

  // -----Run AutoSequence Setup-----
  autoSequenceSetUp(autoSequenceArray);
  
  // -----Run Sensor Setup -----
  sensorSetUp(sensorArray);

  // pin setup
  // NEEDS LOTS OF UPDATES FOR ALARA V2
  pinMode(LED_BUILTIN, OUTPUT);
  

  Serial.begin(9600); // Value is arbitrary on Teensy, it will initialize at the MCU dictate baud rate regardless what you feed this

///// CAN0 and CAN1 Initialize /////
  Can0.begin(CAN2busSpeed);
}

void loop() 
{
  //Display the node number with serial print statement start of each loop
  //Serial.print("PropulsionSysNodeID: ");
  //Serial.println(PropulsionSysNodeID);

///// Custom function for tracking miliseconds and seconds level system time for timestamping /////
myTimeTrackingFunction();
/* Serial.print(second());
Serial.print(" : ");
Serial.println(timeSubSecondsMicros); */

  // --- Read CAN bus and update current command ---
  if(CANread(Can0, currentCommand) && !startup) // do not execute on the first loop
  {
    Serial.print("Command Recieved: ");
    Serial.println(currentCommand);
  }

  while (Serial.available()) 
    {
    fakeCANmsg = Serial.read();
      if(fakeCANmsg  < command_SIZE) //enter 0 inter serial to trigger command read
      {
          //add in code here to prompt for command code and update current command from this
          //Serial.println("Enter Command Byte");
          //CurrentCommand = Serial.read();
              
              //if(fakeCANmsg < command_SIZE)                                           // this checks if the message at that location in the buffer could be a valid command
              //{
                  currentCommand = static_cast<Command>(fakeCANmsg);
              //}
          Serial.println("Command Entered");
        }
    }


  // -----Process Commands Here-----
  vehicleStateMachine(currentVehicleState, priorVehicleState, currentCommand, valveArray, pyroArray, autoSequenceArray, sensorArray, tankPressControllerArray, engineControllerArray, abortHaltFlag);
  tankPressControllerTasks(tankPressControllerArray, PropulsionSysNodeID);
  engineControllerTasks(engineControllerArray, PropulsionSysNodeID);
  controllerDeviceSync(currentVehicleState, priorVehicleState, currentCommand, valveArray, pyroArray, autoSequenceArray, sensorArray, tankPressControllerArray, engineControllerArray, abortHaltFlag);
  
  ////// ABORT FUNCTIONALITY!!!///// This is what overrides main valve and igniter processes! /////
  ////// DO NOT MOVE BEFORE "commandExecute" or after "valveTasks"/"pyroTasks"!!! /////
  //haltFlagCheck(abortHaltFlag, valveArray, pyroArray);

  // -----Advance needed controller system tasks (tank press controllers, ignition autosequence, . ..) ----- //
/*   autoSequenceTasks(autoSequenceArray,nodeID);
  autoSequenceValveUpdate(valveArray, currentCountdownForMain);
  autoSequencePyroUpdate(pyroArray, currentCountdownForMain);   */
  // -----Advance needed propulsion system tasks (valve, pyro, sensors, . ..) ----- //
  cli(); // disables interrupts to ensure complete propulsion output state is driven
  valveTasks(valveArray, PropulsionSysNodeID);
  pyroTasks(pyroArray, PropulsionSysNodeID);
  sei(); // reenables interrupts after propulsion output state set is completed
  sensorTasks(sensorArray, adc, rocketDriverSeconds, rocketDriverMicros, PropulsionSysNodeID);
  
// For Testing to verify abort halt flag is active as intended
/*     Serial.print("abortHaltFlag: ");
    Serial.println(abortHaltFlag); */

  // -----Update States on EEPROM -----
  tripleEEPROMwrite(static_cast<uint8_t>(currentVehicleState), vehicleStateAddress1, vehicleStateAddress2, vehicleStateAddress3);

  // CAN State Report and Sensor data send Functions
  CAN2PropSystemStateReport(Can0, currentVehicleState, currentCommand, valveArray, pyroArray, abortHaltFlag, PropulsionSysNodeID);
  CAN2AutosequenceTimerReport(Can0, autoSequenceArray, abortHaltFlag, PropulsionSysNodeID);
  CAN2SensorArraySend(Can0, sensorArray, PropulsionSysNodeID, CANSensorReportConverted);

  // Reset function to reboot Teensy with internal reset register
  // Need to figure out how to rework using this feature with reworked ID system
  TeensyInternalReset(localNodeResetFlag, nodeIDDetermineAddress1, nodeIDDetermineAddress2, nodeIDDetermineAddress3);

  if (mainLoopTestingTimer >= 500)
  {
  //Main Loop state and command print statements - for testing only - TEMPORARY BULLSHIT
  Serial.print("currentVehicleState :");
  Serial.println(static_cast<uint8_t>(currentVehicleState));
  Serial.print("currentCommand :");
  Serial.println(currentCommand);

    for(auto tankPressController : tankPressControllerArray)
    {
            Serial.print( ": TankControllerState: ");
            Serial.print(static_cast<uint8_t>(tankPressController->getState()));
            Serial.println(": ");
            Serial.println(": ");
            Serial.print(static_cast<uint8_t>(tankPressController->getPrimaryPressValveState()));
            Serial.println(": ");
            Serial.print(static_cast<uint8_t>(tankPressController->getPressLineVentState()));
            Serial.println(": ");
            Serial.print(static_cast<uint8_t>(tankPressController->getTankVentState()));
            Serial.println(": ");

    }
    
    for(auto valve : valveArray)
    {
    
        if (valve->getValveNodeID() == PropulsionSysNodeID)
        {
            Serial.print("ValveID: ");
            Serial.print(static_cast<uint8_t>(valve->getValveID()));
            Serial.print( ": ValveState: ");
            Serial.print(static_cast<uint8_t>(valve->getState()));
            Serial.println(": ");

        }

    }

  mainLoopTestingTimer = 0; //resets timer to zero each time the loop prints
  //Serial.print("EEPROM Node ID Read :");
  //Serial.println(EEPROM.read(nodeIDAddress));
  }

// Resets the startup bool, DO NOT REMOVE
startup = false;
  
  //Serial.println("main loop ran");
}