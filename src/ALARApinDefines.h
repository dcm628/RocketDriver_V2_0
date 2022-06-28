#ifndef ALARAPINDEFINES_H
#define ALARAPINDEFINES_H
#pragma once

// remove this define later and make it based on the ALARA SN lookup
#define ALARAV2

#ifdef ALARAV2

// ALARA pin mapping definitions
// Analog Inputs
#define ALARA_ANALOG_IN1 A13
#define ALARA_ANALOG_IN2 A12
#define ALARA_ANALOG_IN3 A15
#define ALARA_ANALOG_IN4 A14
#define ALARA_ANALOG_IN5 A21
#define ALARA_ANALOG_IN6 A22
#define ALARA_ANALOG_IN7 A11
#define ALARA_ANALOG_IN8 A10
#define ALARA_ANALOG_3_3RAIL A20
#define ALARA_ANALOG_5RAIL A23

// Digital I/O for MUXed addressing system (or V2 plain digital inputs?)
#define ALARA_DIGITAL_ADDRESS_1 79
#define ALARA_DIGITAL_ADDRESS_2 80
#define ALARA_DIGITAL_ADDRESS_3 81
#define ALARA_DIGITAL_ADDRESS_4 82

// Digital Outputs
#define ALARA_DIGITAL_EXTERNAL_1 83
#define ALARA_DIGITAL_EXTERNAL_2 84
#define ALARA_DIGITAL_EXTERNAL_3 63
#define ALARA_DIGITAL_EXTERNAL_4 64

//High Power Outputs
#define ALARA_HIGHPOWER_DIGITALOUT1 54
#define ALARA_HIGHPOWER_DIGITALOUT2 51
#define ALARA_HIGHPOWER_DIGITALOUT3 52
#define ALARA_HIGHPOWER_DIGITALOUT4 53
#define ALARA_HIGHPOWER_DIGITALOUT5 55
#define ALARA_HIGHPOWER_DIGITALOUT6 87
#define ALARA_HIGHPOWER_DIGITALOUT7 48
#define ALARA_HIGHPOWER_DIGITALOUT8 47
#define ALARA_HIGHPOWER_DIGITALOUT9 86
#define ALARA_HIGHPOWER_DIGITALOUT10 85
#define ALARA_HIGHPOWER_PWMOUT1 5
#define ALARA_HIGHPOWER_PWMOUT2 6
#define ALARA_HIGHPOWER_PWMOUT3 8
#define ALARA_HIGHPOWER_PWMOUT4 7
#define ALARA_HIGHPOWER_PWMOUT5 2
#define ALARA_HIGHPOWER_PWMOUT6 10
#define ALARA_HIGHPOWER_PWMOUT7 9
#define ALARA_HIGHPOWER_PWMOUT8 22
#define ALARA_HIGHPOWER_PWMOUT9 30
#define ALARA_HIGHPOWER_PWMOUT10 29
#define ALARA_HIGHPOWER_ANALOGREAD1 A7
#define ALARA_HIGHPOWER_ANALOGREAD2 A6
#define ALARA_HIGHPOWER_ANALOGREAD3 A0
#define ALARA_HIGHPOWER_ANALOGREAD4 A19
#define ALARA_HIGHPOWER_ANALOGREAD5 A18
#define ALARA_HIGHPOWER_ANALOGREAD6 A17
#define ALARA_HIGHPOWER_ANALOGREAD7 A116
#define ALARA_HIGHPOWER_ANALOGREAD8 A9
#define ALARA_HIGHPOWER_ANALOGREAD9 A1
#define ALARA_HIGHPOWER_ANALOGREAD10 A24

// Bus Pins
#define ALARA_PRIMARY_I2C_SCL 19
#define ALARA_PRIMARY_I2C_SDA 18
#define ALARA_PRIMARY_UART_MOSI 0
#define ALARA_PRIMARY_UART_MISO 1
#define ALARA_PRIMARY_SPI_SCK 13
#define ALARA_PRIMARY_SPI_MOSI 11
#define ALARA_PRIMARY_SPI_MISO 12
#define ALARA_CAN_CS 74
#define ALARA_CAN_INTN0 42
#define ALARA_CAN_INTN1 40
#define ALARA_CAN_INTN 41
#define ALARA_CAN_CLK0 75
#define ALARA_RS485_D 72
#define ALARA_RS485_R 73

// NOR
#define ALARA_NOR_S0 43
#define ALARA_NOR_S1 46
#define ALARA_NOR_S2 44
#define ALARA_NOR_OE 45

// SMD Sensors
#define ALARA_IMU1_RST 68
#define ALARA_IMU2_CSBG 77
#define ALARA_IMU2_CSBA 78
#define ALARA_ACC_CSN 66
#define ALARA_ACC_TRIG 67
#define ALARA_BPS_CSN 76

// On board indicators - LEDs and Buzzer
#define ALARA_PROG_LED_BLU1 69
#define ALARA_PROG_LED_GRN1 70
#define ALARA_PROG_LED_RED1 71
#define ALARA_PROG_LED_BLU2 58
#define ALARA_PROG_LED_GRN2 59
#define ALARA_PROG_LED_RED2 60
#define ALARA_BUZZ 16

// NRF and LORA external jumper connectors
#define ALARA_NRF_CSN 28
#define ALARA_NRF_CE 27
#define ALARA_NRF_IRQ 65

#define ALARA_LORA_CS 24
#define ALARA_LORA_INT 26
#define ALARA_LORA_RST 25

// GPS
#define ALARA_GPS_INT 56
#define ALARA_GPS_RST 57


#endif

#ifdef ALARAV2_1
// duplicate full pin mapping here with required changes
#endif

/* // NON ALARA prior gen stuff below
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


}; */

#endif