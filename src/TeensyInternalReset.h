#ifndef TEENSYINTERNALRESET_H
#define TEENSYINTERNALRESET_H

// Teensy 3.5/3.6 MCU restart register definitions
#define RESTART_ADDR       0xE000ED0C
#define READ_RESTART()     (*(volatile uint32_t *)RESTART_ADDR)
#define WRITE_RESTART(val) ((*(volatile uint32_t *)RESTART_ADDR) = (val))


bool localNodeResetFlagIn;
uint8_t nodeIDDetermineAddressIn;
uint8_t nodeIDIn;

void TeensyInternalReset (bool& localNodeResetFlagIn, uint8_t& nodeIDDetermineAddressIn, uint8_t& nodeIDIn)
{
  if (localNodeResetFlagIn)
  {
    cli(); // disables interrupts to protect write command
    EEPROM.update(nodeIDDetermineAddressIn, 1);                                 // Never use .write()
    sei(); // reenables interrupts after write is completed
    WRITE_RESTART(0x5FA0004);
  }
  else; //nothing else but it feels right
}

#endif