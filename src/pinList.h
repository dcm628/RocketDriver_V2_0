#ifndef PINLIST_H
#define PINLIST_H
#pragma once

#define ALARAV2     // Used to be able to have ALARA version dependant pin mappings in future
#ifdef ALARAV2

// ALARA pin mapping definitions
// Analog Inputs
#define ALARA_ANALOG_IN1 A2
#define ALARA_ANALOG_IN2 A20
#define ALARA_ANALOG_IN3 A21
#define ALARA_ANALOG_IN4 A22
#define ALARA_ANALOG_IN5 A10
#define ALARA_ANALOG_IN6 A11
#define ALARA_ANALOG_IN7 A12
#define ALARA_ANALOG_IN8 A13
#define ALARA_ANALOG_3_3RAIL A23
#define ALARA_ANALOG_5RAIL A24

// Digital Inputs
#define ALARA_DIGITAL_ADDRESS_1 
#define ALARA_DIGITAL_ADDRESS_2 
#define ALARA_DIGITAL_ADDRESS_3 
#define ALARA_DIGITAL_ADDRESS_4 

// Digital Outputs
#define ALARA_DIGITAL_EXTERNAL_1 
#define ALARA_DIGITAL_EXTERNAL_2 

//High Power Outputs
#define ALARA_HIGHPOWER_DIGITALOUT1 56
#define ALARA_HIGHPOWER_DIGITALOUT2 47
#define ALARA_HIGHPOWER_DIGITALOUT3 48
#define ALARA_HIGHPOWER_DIGITALOUT4 55
#define ALARA_HIGHPOWER_DIGITALOUT5 53
#define ALARA_HIGHPOWER_DIGITALOUT6 52
#define ALARA_HIGHPOWER_DIGITALOUT7 51
#define ALARA_HIGHPOWER_DIGITALOUT8 997 //54
#define ALARA_HIGHPOWER_DIGITALOUT9 998
#define ALARA_HIGHPOWER_DIGITALOUT10 999
#define ALARA_HIGHPOWER_PWMOUT1 3
#define ALARA_HIGHPOWER_PWMOUT2 4
#define ALARA_HIGHPOWER_PWMOUT3 29
#define ALARA_HIGHPOWER_PWMOUT4 30
#define ALARA_HIGHPOWER_PWMOUT5 22
#define ALARA_HIGHPOWER_PWMOUT6 9
#define ALARA_HIGHPOWER_PWMOUT7 2
#define ALARA_HIGHPOWER_PWMOUT8 7
#define ALARA_HIGHPOWER_PWMOUT9 8
#define ALARA_HIGHPOWER_PWMOUT10 6
#define ALARA_HIGHPOWER_ANALOGREAD1 A3
#define ALARA_HIGHPOWER_ANALOGREAD2 A1
#define ALARA_HIGHPOWER_ANALOGREAD3 A9
#define ALARA_HIGHPOWER_ANALOGREAD4 A16
#define ALARA_HIGHPOWER_ANALOGREAD5 A17
#define ALARA_HIGHPOWER_ANALOGREAD6 A18
#define ALARA_HIGHPOWER_ANALOGREAD7 A19
#define ALARA_HIGHPOWER_ANALOGREAD8 A0
#define ALARA_HIGHPOWER_ANALOGREAD9 A6
#define ALARA_HIGHPOWER_ANALOGREAD10 A7

// Bus Pins
#define ALARA_PRIMARY_I2C_SCL 19
#define ALARA_PRIMARY_I2C_SDA 18
#define ALARA_PRIMARY_UART_MOSI 0
#define ALARA_PRIMARY_UART_MISO 1
#define ALARA_PRIMARY_SPI_SCK 13
#define ALARA_PRIMARY_SPI_MOSI 11
#define ALARA_PRIMARY_SPI_MISO 12
#define ALARA_CAN_CS 42
#define ALARA_CAN_IO_0 40
#define ALARA_CAN_IO_1 41
#define ALARA_CAN_IO_2 43
#define ALARA_RS485_A 
#define ALARA_RS485_B 
#define ALARA_RS485_Y 
#define ALARA_RS485_Z 

// NOR
#define ALARA_NOR_CS1 57
#define ALARA_NOR_CS2 24
#define ALARA_NOR_CS3 25
#define ALARA_NOR_CS4 26

// SMD Sensors
#define ALARA_ACC_CS 27

// LEDs - placeholder pending final ALARA V2 design decision
#define ALARA_PROG_LED1 
#define ALARA_PROG_LED2 
#define ALARA_PROG_LED3 

// NRF and LORA external jumper connectors
#define ALARA_NRF_CS
#define ALARA_LORA_CS

#endif

// NON ALARA prior gen stuff below
namespace pin
{
    
    const int led = 13;
    

    // Node Addressing pins
    const int NodeAddress0{0};
    const int NodeAddress1{1};
    const int NodeAddress2{28};
    const int NodeAddress3{29};   // Need to figure out this pin assignment to get the extra NodeID space

    // abort interrupt pins - Not fully implemented, need to test and check
    // const int abort{};


};

#endif