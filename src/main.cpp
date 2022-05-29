// RocketDriver Propulsion Control and Data Acquisition - Embedded System Node Program
// Originally by Dan Morgan and Mat Arnold
// For Renegade, Pasafire, Beach Launch Team, and more
//
//
// -------------------------------------------------------------
// Use top level define conditional to determine which system the code is operating
#define RENEGADESF

//----- Renegade Static Fire Stand -----
#ifdef RENEGADESF
#include "ValveDefinitionsRenegadeSF.h"
#include "PyroDefinitionsRenegadeSF.h"
#include "AutoSequenceDefinitionsRenegadeSF.h"
#include "SensorDefinitionsRenegadeSF.h"
#include "TankPressControllerDefinitionsRenegadeSF.h"
#include "ControlFunctionsRenegadeSF.h"
#endif

//----- BabyShark -----
#ifdef BABYSHARK
#include "ValveDefinitionsRenegadeBabyShark.h"
#include "PyroDefinitionsRenegadeBabyShark.h"
#include "AutoSequenceDefinitionsRenegadeBabyShark.h"
#include "SensorDefinitionsRenegadeBabyShark.h"
#include "TankPressControllerDefinitionsBabyShark.h"
#include "ControlFunctionsRenegadeBabyShark.h"
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

#include "ToMillisTimeTracker.h"
#include "CANRead.h"
#include "CANWrite.h"
#include "TeensyInternalReset.h"
#include "OperationFunctionTemplates.h"
#include "pinList.h"

//Trying to figure out RTC stuff with these libs
#include <TimeLib.h>
#include <DS1307RTC.h>

#define NODEIDPRESET 3;     //NOT in use normally, for testing with the address IO register inactive

// Timer for setting main loop debugging print rate
elapsedMillis mainLoopTestingTimer;

//For use in doing serial inputs as CAN commands for testing
uint8_t fakeCANmsg;

bool localNodeResetFlag = false; //flag to trigger register reset from commanded reset over CAN

bool abortHaltFlag; //creates halt flag that is a backup override of state machine

///// NODE DECLARATION /////
//default sets to max nodeID intentionally to be bogus until otherwise set
uint8_t nodeID;       //engine node = 2, prop node = 3, Pasafire node = 8
uint8_t nodeIDfromEEPROM;   //nodeID read out of EEPROM
bool nodeIDdeterminefromEEPROM;   //boolean flag for if startup is to run the nodeID detect read

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

int value = 0;
int counter = 0;
//int MCUtempPIN = 70;  //?? Not sure, I was trying to figure out how to read direct from the non Teensy MCU pin
//int MCUtempraw;

int busSpeed0 = 500000; //baudrate - do not set above 500000 for full distance run bunker to pad
int busSpeed1 = 500000; //baudrate - do not set above 500000 for full distance run bunker to pad

bool startup{true}; // bool for storing if this is the first loop on startup, ESSENTIAL FOR STATE MACHINE OPERATION

uint32_t loopCount {0};// for debugging

// Set the global command, and global state
Command currentCommand{command_NOCOMMAND}; 
VehicleState currentVehicleState{VehicleState::passive};
VehicleState priorVehicleState;
MissionState currentMissionState(MissionState::passive);
MissionState priorMissionState;

//AutoSequence stuff for main
int64_t currentCountdownForMain;

// Set EEPROM address for storing states
// Change these up occasionally to reduce write cycle wear on the same bytes
// I could use EEPROM itself to store current start byte of my data and automate iterating this. Good idea for future upgrade.
uint8_t stateAddress{1};
uint8_t nodeIDAddress{2};
uint8_t nodeIDDetermineAddress{3};

///// Temp Sensor for TC Cold Junction /////
//Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
//int roundedtemp;


// -------------------------------------------------------------
// abort reset function -- NOT TESTED IN CURRENT VERSION, needs to be worked on
/* void abortReset()
{
  cli();
  EEPROM.update(stateAddress, static_cast<uint8_t>(State::abort)); // write abort code to the EEPROM to be read on restart
  sei();
  digitalWrite(pin::reset, 0);                                       // set reset pin low to restart
} */


// -------------------------------------------------------------
uint8_t NodeIDDetect(uint8_t nodeID, bool startup, bool nodeIDdetermine, uint8_t nodeIDfromEEPROM)       //Function to run the nodeID hardware addressing
{
  //if (startup)                          //only on startup assign the pins, not needed if running this in setup
    //{
    pinMode(pin::NodeAddress0, INPUT);
    pinMode(pin::NodeAddress1, INPUT);
    pinMode(pin::NodeAddress2, INPUT);
    pinMode(pin::NodeAddress3, INPUT);
    //}
  
  if (nodeIDdetermine)
    {
    //Read the four digital addressing pins
    uint8_t NodeAddressBit0 = digitalRead(pin::NodeAddress0);
    uint8_t NodeAddressBit1 = digitalRead(pin::NodeAddress1)<<1;
    uint8_t NodeAddressBit2 = digitalRead(pin::NodeAddress2)<<2;
    uint8_t NodeAddressBit3 = digitalRead(pin::NodeAddress3)<<3;
    //Use the read addresses to convert into an int for nodeID
    uint8_t NodeIDAddressRead;
    NodeIDAddressRead = NodeAddressBit0 + NodeAddressBit1 + NodeAddressBit2 + NodeAddressBit3;
    nodeID = NodeIDAddressRead;     //Setting the Global NodeID to detected NodeID
    cli(); // disables interrupts to protect write command
    EEPROM.update(nodeIDDetermineAddress, 0);                                 // Never use .write()
    sei(); // reenables interrupts after write is completed
    }
  else
    nodeID = nodeIDfromEEPROM;      //Need to ADD FEATURE where the nodeIDdetermine is variable so on a quick power cycle it doesn't reset, but a manual "shutdown" can
  return nodeID;
  
}
// -------------------------------------------------------------


//-------------------------------------------------------//
void setup() {
  startup = true;   // Necessary to set startup to true for the code loop so it does one startup loop for the state machine before entering regular loop behavior

  // -----Read Last State off eeprom and update -----
  currentVehicleState = static_cast<VehicleState>(EEPROM.read(stateAddress));
  nodeIDfromEEPROM = EEPROM.read(nodeIDAddress);
  nodeIDdeterminefromEEPROM = EEPROM.read(nodeIDDetermineAddress);
  startupStateCheck(currentVehicleState, currentCommand);

  // ----- Run the Node ID Detection Function -----
  //nodeID = NodeIDDetect(nodeID, startup, nodeIDdeterminefromEEPROM, nodeIDfromEEPROM);
  nodeID = NODEIDPRESET;       //For manually assigning NodeID isntead of the address read, make sure to comment out for operational use
  // Write 0 to byte for nodeIDDetermineAddress after reading it after a reset
  cli(); // disables interrupts to protect write command
  EEPROM.update(nodeIDDetermineAddress, 0);                                 // Never use .write()+
  sei(); // reenables interrupts after write is completed


  // ----- Hardware Abort Pin Setup ----- NOT CURRENTLY IN USE
  // This hardware abort allows us to command the Teensy to reboot itself by pulling the reset pin to ground
/*   pinMode(pin::reset, OUTPUT);
  digitalWrite(pin::reset, 1);
  pinMode(pin::abort, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(pin::abort), abortReset, RISING);  */



  // -----Initialize ADCs-----
  MCUADCSetup(adc);

  // -----Run Valve NodeID Check-----
  ValveNodeIDCheck(valveArray, nodeID);

  // -----Run Valve NodeID Check-----
  PyroNodeIDCheck(pyroArray, nodeID);

  // -----Run Sensor NodeID Check-----
  SensorNodeIDCheck(sensorArray, nodeID);

  // -----Run Valve Setup-----
  valveSetUp(valveArray);

  // -----Run Valve Setup-----
  pyroSetUp(pyroArray);

  // -----Run AutoSequence Setup-----
  autoSequenceSetUp(autoSequenceArray);
  
  // -----Run Sensor Setup -----
  sensorSetUp(sensorArray);

  // pin setup
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

///// CAN0 and CAN1 Initialize /////
  Can0.begin(busSpeed0);
  //Can1.begin(busSpeed1); //commented out for Teensy3.5, also not current in use even on 3.6
  pinMode(pin::led, OUTPUT);
}

void loop() 
{
  //Display the node number with serial print statement start of each loop
  //Serial.print("NodeID: ");
  //Serial.println(nodeID);

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
  vehicleStateMachine(currentVehicleState, priorVehicleState, currentCommand, valveArray, pyroArray, autoSequenceArray, sensorArray, tankPressControllerArray, abortHaltFlag);
  tankPressControllerTasks(tankPressControllerArray, nodeID);
  propulsionControllerDeviceUpdate(currentVehicleState, priorVehicleState, currentCommand, valveArray, pyroArray, autoSequenceArray, sensorArray, tankPressControllerArray, abortHaltFlag);
  
  ////// ABORT FUNCTIONALITY!!!///// This is what overrides main valve and igniter processes! /////
  ////// DO NOT MOVE BEFORE "commandExecute" or after "valveTasks"/"pyroTasks"!!! /////
  //haltFlagCheck(abortHaltFlag, valveArray, pyroArray);

  // -----Advance needed controller system tasks (tank press controllers, ignition autosequence, . ..) ----- //
/*   autoSequenceTasks(autoSequenceArray,nodeID);
  autoSequenceValveUpdate(valveArray, currentCountdownForMain);
  autoSequencePyroUpdate(pyroArray, currentCountdownForMain);   */
  // -----Advance needed propulsion system tasks (valve, pyro, sensors, . ..) ----- //
  valveTasks(valveArray, nodeID);
  pyroTasks(pyroArray, nodeID);
  sensorTasks(sensorArray, adc, rocketDriverSeconds, rocketDriverMicros, nodeID);
  
// For Testing to verify abort halt flag is active as intended
/*     Serial.print("abortHaltFlag: ");
    Serial.println(abortHaltFlag); */

  // -----Update State on EEPROM -----
  cli(); // disables interrupts to protect write command
  EEPROM.update(stateAddress, static_cast<uint8_t>(currentVehicleState));      // Never use .write()
  EEPROM.update(nodeIDAddress, nodeID);                                 // Never use .write()
  sei(); // reenables interrupts after write is completed

  // CAN State Report and Sensor data send Functions
  CAN2PropSystemStateReport(Can0, currentVehicleState, currentCommand, valveArray, pyroArray, abortHaltFlag, nodeID);
  CAN2AutosequenceTimerReport(Can0, autoSequenceArray, abortHaltFlag, nodeID);
  CAN2SensorArraySend(Can0, sensorArray, nodeID, CANSensorReportConverted);

  // Reset function to reboot Teensy with internal reset register
  TeensyInternalReset(localNodeResetFlag, nodeIDDetermineAddress, nodeID);

  if (mainLoopTestingTimer >= 500)
  {
  //Main Loop state and command print statements - for testing only
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
            Serial.print(static_cast<uint8_t>(tankPressController->getDomePressState()));
            Serial.println(": ");
            Serial.print(static_cast<uint8_t>(tankPressController->getDomeVentState()));
            Serial.println(": ");
            Serial.print(static_cast<uint8_t>(tankPressController->getTankVentState()));
            Serial.println(": ");

    }
    
    for(auto valve : valveArray)
    {
    
        if (valve->getValveNodeID() == nodeID)
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