#ifndef ALARAUTILITYFUNCTIONS_H
#define ALARAUTILITYFUNCTIONS_H

#include <Arduino.h>
#include <EEPROM.h>

bool readOnlyMUX(uint8_t pinToReadMUX, uint8_t pinMUX_S0, uint8_t pinMUX_S1, uint8_t pinMUX_S2, uint8_t pinMUX_A) // SN74CB3Q3251 MUX pin read operation for use only when MUX has OE tied to GND
{
  digitalWrite(pinMUX_S0, (pinToReadMUX >> 0) & 1L);
  digitalWrite(pinMUX_S1, (pinToReadMUX >> 1) & 1L);
  digitalWrite(pinMUX_S2, (pinToReadMUX >> 2) & 1L);
  return digitalRead(pinMUX_A);
}

void SPI_CS_MUX(uint8_t pinToWriteMUX, uint8_t pinMUX_S0, uint8_t pinMUX_S1, uint8_t pinMUX_S2) // SN74CB3Q3251 MUX pin output operation for use as multiplexed CS pins
{
  digitalWrite(pinMUX_S0, (pinToWriteMUX >> 0) & 1L);
  digitalWrite(pinMUX_S1, (pinToWriteMUX >> 1) & 1L);
  digitalWrite(pinMUX_S2, (pinToWriteMUX >> 2) & 1L);
}

void MUXSetup(bool MUX_Input, uint8_t pinMUX_S0, uint8_t pinMUX_S1, uint8_t pinMUX_S2, uint8_t pinMUX_A = 0)       // SN74CB3Q3251 MUX pin output setup function, set MUX_Input = false and leave pinMUX_A empty for output MUX
{
    pinMode(pinMUX_S0, OUTPUT);
    pinMode(pinMUX_S1, OUTPUT);
    pinMode(pinMUX_S2, OUTPUT);
    if (MUX_Input)                  // Use MUX_Input boolean to set the input pin only if this MUX will be used as input, output MUX doesn't use
    {
      pinMode(pinMUX_A, INPUT);
    }
}


// -------------------------------------------------------------
uint8_t NodeIDDetect(uint8_t pinToReadMUXNodeID, uint8_t pinMUX_S0NodeID, uint8_t pinMUX_S1NodeID, uint8_t pinMUX_S2NodeID, uint8_t pinMUX_ANodeID,
                    uint16_t nodeIDDetermineAddress, uint8_t nodeID, bool nodeIDdetermine, uint8_t nodeIDfromEEPROM1, uint8_t nodeIDfromEEPROM2, uint8_t nodeIDfromEEPROM3)       //Function to run the nodeID hardware addressing
{
uint8_t NodeIDAddressRead;
for (size_t i = 0; i < 8; i++)
{
  NodeIDAddressRead = readOnlyMUX(i, pinMUX_S0NodeID, pinMUX_S1NodeID,  pinMUX_S2NodeID, pinMUX_ANodeID) << i;
}
/* 
  if (nodeIDdetermine)
    {

    cli(); // disables interrupts to protect write command
    EEPROM.update(nodeIDDetermineAddress, 0);                                 // Never use .write()
    sei(); // reenables interrupts after write is completed
    }
  else
    NodeIDAddressRead = nodeIDfromEEPROM;      //Need to ADD FEATURE where the nodeIDdetermine is variable so on a quick power cycle it doesn't reset, but a manual "shutdown" can
  return NodeIDAddressRead;
   */
}
// -------------------------------------------------------------

void tripleEEPROMwrite(uint8_t byteToWrite, uint32_t byteAddress1, uint32_t byteAddress2, uint32_t byteAddress3)
{
    // -----Update State on EEPROM -----
  cli(); // disables interrupts to protect write command
  EEPROM.update(byteAddress1, byteToWrite);                                 // Never use .write()
  EEPROM.update(byteAddress2, byteToWrite);                                 // Never use .write()
  EEPROM.update(byteAddress3, byteToWrite);                                 // Never use .write()
  sei(); // reenables interrupts after write is completed
}

uint8_t tripleEEPROMread(uint32_t byteAddress1, uint32_t byteAddress2, uint32_t byteAddress3, uint32_t &errorFlag)
{
  uint8_t byteReadFrom1;
  uint8_t byteReadFrom2;
  uint8_t byteReadFrom3;
  byteReadFrom1 = EEPROM.read(byteAddress1);
  byteReadFrom2 = EEPROM.read(byteAddress2);
  byteReadFrom3 = EEPROM.read(byteAddress3);

// Error handling and voting for non matching results
// errorFlag = 0 means no error, 
// otherwise bytes 0,1,2 are combined to return to mixed result in totality
// bits above 24 of EEPROM byte info are set as boolean digits to flag the non matching bytes

  if (byteReadFrom1 == byteReadFrom2 && byteReadFrom1 == byteReadFrom3)
  {
    errorFlag = 0;           
    return byteReadFrom1;
  }
  else if (byteReadFrom1 == byteReadFrom2)
  {
    errorFlag = (4 >> 24) + (byteReadFrom3 >> 16);
    return byteReadFrom1;
  }
  else if (byteReadFrom1 == byteReadFrom3)
  {
    errorFlag = (2 >> 24) + (byteReadFrom2 >> 8);
    return byteReadFrom1;
  }
  else if (byteReadFrom2 == byteReadFrom3)
  {
    errorFlag = (1 >> 24) + (byteReadFrom1 >> 0);
    return byteReadFrom2;
  }
  else
    errorFlag = (7 >> 24) + (byteReadFrom3 >> 16) + (byteReadFrom2 >> 8) + (byteReadFrom1 >> 0);
    return byteReadFrom1;
}

// ----- Teensy Internal Reset -----
// Teensy 3.5/3.6 MCU restart register definitions
#define RESTART_ADDR       0xE000ED0C
#define READ_RESTART()     (*(volatile uint32_t *)RESTART_ADDR)
#define WRITE_RESTART(val) ((*(volatile uint32_t *)RESTART_ADDR) = (val))

void TeensyInternalReset (bool& localNodeResetFlagIn, uint8_t addressIn1, uint8_t addressIn2, uint8_t addressIn3)
{
  if (localNodeResetFlagIn)
  {
    tripleEEPROMwrite(1, addressIn1, addressIn2, addressIn3);
    WRITE_RESTART(0x5FA0004);
  }
  else; //nothing else but it feels right
}

// ----- Software PWM Function -----
// behavior is not reliable when there are delays
elapsedMicros fakePWMMicros;
uint32_t dutyOnMicros;
uint32_t periodMicros;

void analogWriteSoft(uint8_t outputPin, bool outputState, uint32_t freqIN, uint16_t dutyCycleIn)
{
    periodMicros = 1000000/freqIN;
    dutyOnMicros = (dutyCycleIn * periodMicros)/256;
    if (outputState)
    {
        if (fakePWMMicros >= (periodMicros))
        {
            digitalWrite(outputPin,1);
            fakePWMMicros = 0;
        }
        if (fakePWMMicros >= dutyOnMicros)
        {
            digitalWrite(outputPin,0);
        }
    } 
}

#endif