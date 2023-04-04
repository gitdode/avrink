/* 
 * File:   eink.h
 * Author: torsten.roemer@luniks.net
 * Thanks to https://github.com/adafruit/Adafruit_EPD for helping me out!
 *
 * Created on 1. April 2023, 20:48
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "eink.h"
#include "pins.h"
#include "usart.h"
#include "sram.h"
#include "spi.h"

/**
 * Does a hardware reset.
 */
static void hwReset(void) {
    PORT_SRDI &= ~(1 << PIN_RST);
    _delay_ms(10);
    PORT_SRDI |= (1 << PIN_RST);
}

/**
 * Selects the display to talk to via SPI.
 */
static void csLow(void) {
    PORT_SRDI &= ~(1 << PIN_ECS);
}

/**
 * Deselects the display to talk to via SPI.
 */
static void csHigh(void) {
    PORT_SRDI |= (1 << PIN_ECS);
}

/**
 * Send a command to the display.
 */
static void dcLow(void) {
    PORT_SRDI &= ~(1 << PIN_DC);
}

/**
 * Send data to the display.
 */
static void dcHigh(void) {
    PORT_SRDI |= (1 << PIN_DC);
}

static void waitBusy(void) {
    loop_until_bit_is_clear(PINP_SRDI, PIN_BUSY);
}

static void ledOn(void) {
    PORT_LED |= (1 << PIN_LED);
}

static void ledOff(void) {
    PORT_LED &= ~(1 << PIN_LED);
}

static void initDisplay(void) {
    // 1. Power On
    // VCI already supplied - could supply by MCU output pin?
    // - Supply VCI
    // - Wait 10ms
    _delay_ms(10);

    // 2. Set Initial Configuration
    // board selects 4-wire SPI by pulling BS1 low
    // - Define SPI interface to communicate with MCU

    // - HW Reset
    hwReset();

    _delay_ms(100);
    waitBusy();

    // - SW Reset by Command 0x12
    dcLow();
    csLow();
    transmit(SW_RESET);
    csHigh();

    // - Wait 10ms
    waitBusy(); // datasheet mentions BUSY is high during reset
    _delay_ms(10);

    printString("done setting initial configuration\r\n");
    
    // 3. Send Initialization Code
    // - Set gate driver output by Command 0x01
    dcLow();
    csLow();
    transmit(DRIVER_OUTPUT_CONTROL);
    dcHigh();
    transmit(DISPLAY_WIDTH - 1);
    transmit((DISPLAY_WIDTH - 1) >> 8);
    transmit(0);
    csHigh();
    
    // - Set display RAM size by Command 0x11, 0x44, 0x45
    dcLow();
    csLow();
    transmit(DATA_ENTRY_MODE_SETTING);
    dcHigh();
    transmit(0x03); // Define data entry sequence A[2:0] = 011 [POR]
    csHigh();
    
    uint8_t height = DISPLAY_HEIGHT + 8 - DISPLAY_HEIGHT % 8;
    
    dcLow();
    csLow();
    transmit(RAM_X_ADDRESS_POSITION);
    dcHigh();
    transmit(0x00 + RAM_X_OFFSET);
    transmit(height / 8 - 1 + RAM_X_OFFSET);
    csHigh();
    
    dcLow();
    csLow();
    transmit(RAM_Y_ADDRESS_POSITION);
    dcHigh();
    transmit(0x00);
    transmit(0x00);
    transmit(DISPLAY_WIDTH - 1);
    transmit((DISPLAY_WIDTH - 1) >> 8);
    csHigh();
    
    // - Set panel border by Command 0x3C
    dcLow();
    csLow();
    transmit(BORDER_WAVEFORM_CONTROL);
    dcHigh();
    transmit(0x05); // ?
    csHigh();
    
    printString("done sending initialization code\r\n");

    // 4. Load Waveform LUT
    // - Sense temperature by int/ext TS by Command 0x18
    dcLow();
    csLow();
    transmit(TEMP_SENSOR_CONTROL);
    dcHigh();
    transmit(0x80); // A[7:0] = 80h Internal temperature sensor
    csHigh();
    
    // done at the end
    // - Load waveform LUT from OTP by Command 0x22, 0x20 or by MCU
    // - Wait BUSY Low
    waitBusy();
    
    /*
    // Vcom voltage
    dcLow();
    csLow();
    transmit(0x2c);
    dcHigh();
    transmit(0x36); // not in datasheet table?
    csHigh();
    
    // gate voltage
    dcLow();
    csLow();
    transmit(0x03);
    dcHigh();
    transmit(0x17); // 0x17 = 20V = 0x00 [POR]
    csHigh();

    // source voltage
    dcLow();
    csLow();
    transmit(0x04);
    dcHigh();
    transmit(0x41); [POR]
    transmit(0x00); // not in datasheet table, should be 0xa8 [POR]?
    transmit(0x32); [POR]
    csHigh();
    */
}

/**
 * Sets the RAM address pointer to the starting position.
 */
static void resetRAMAddressCounter(void) {
    dcLow();
    csLow();
    transmit(RAM_X_ADDRESS_COUNTER);
    dcHigh();
    transmit(RAM_X_OFFSET);
    csHigh();
    
    dcLow();
    csLow();
    transmit(RAM_Y_ADDRESS_COUNTER);
    dcHigh();
    transmit(0);
    transmit(0);
    csHigh();
}

/**
 * Writes the given pixels to the RAM area used by the display
 * and resets the address pointer to the starting position.
 * @param data
 */
static void setRAM(uint8_t data) {
    resetRAMAddressCounter();
    
    uint8_t height = DISPLAY_HEIGHT + 8 - DISPLAY_HEIGHT % 8;
    uint16_t bytes = DISPLAY_WIDTH * height / 8;
    dcLow();
    csLow();
    transmit(WRITE_RAM_BW);
    dcHigh();
    for (uint16_t i = 0; i < bytes; i++) {
        transmit(data);
    }
    csHigh();
    
    resetRAMAddressCounter();
}

/**
 * Updates the display and puts it in deep sleep mode.
 */
static void updateDisplay(void) {
    // - Set softstart setting by Command 0x0C
    dcLow();
    csLow();
    transmit(BOOSTER_SOFT_START_CONTROL);
    dcHigh();
    transmit(0x8b); // A[7:0] -> Soft start setting for Phase1 = 8Bh [POR]
    transmit(0x9c); // B[7:0] -> Soft start setting for Phase2 = 9Ch [POR]
    transmit(0x96); // C[7:0] -> Soft start setting for Phase3 = 96h [POR]
    transmit(0x0f); // D[7:0] -> Duration setting = 0Fh [POR]
    csHigh();

    printString("done setting softstart\r\n");
    
    // - Drive display panel by Command 0x22, 0x20
    dcLow();
    csLow();
    transmit(DISPLAY_UPDATE_CONTROL2);
    dcHigh();
    transmit(0xf4); // not in datasheet table? 0xff (POR) does nothing.
    csHigh();
    
    dcLow();
    csLow();
    transmit(MASTER_ACTIVATION);
    csHigh();
    
    // - Wait BUSY Low
    waitBusy();

    printString("done driving display\r\n");

    // 6. Power Off
    // - Deep sleep by Command 0x10
    dcLow();
    csLow();
    transmit(DEEP_SLEEP_MODE);
    dcHigh();
    transmit(0x01); // Enter Deep Sleep Mode 1
    csHigh();
    
    printString("done setting deep sleep\r\n");
    
    // - Power OFF
    // see 1. Power On
}

/**
 * Initializes the display, blanks the RAM, writes the image to RAM
 * and updates the display.
 */
void writeImage(void) {
    printString("starting to drive display...\r\n");

    ledOn();
    initDisplay();
    setRAM(255);
    
    // 5. Write Image and Drive Display Panel
    // - Write image data in RAM by Command 0x4E, 0x4F, 0x24, 0x26
    dcLow();
    csLow();
    transmit(WRITE_RAM_BW);
    dcHigh();
    // draw a grid
    for (int j = 0; j < 31; j++) {
        for (int i = 0; i < 16; i++) {
            transmit(0);
        }
        for (int i = 0; i < 112; i++) {
            transmit(127);
        }
    }       
    csHigh();
    
    printString("done writing data to RAM\r\n");
    
    updateDisplay();
    ledOff();
}