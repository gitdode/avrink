/* 
 * File:   eink.h
 * Author: torsten.roemer@luniks.net
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
 * Selects the Display to talk to via SPI.
 */
static void csLow(void) {
    PORT_SRDI &= ~(1 << PIN_ECS);
}

/**
 * Selects the Display to talk to via SPI.
 */
static void csHigh(void) {
    PORT_SRDI |= (1 << PIN_ECS);
}

/**
 * Send a command to the Display.
 */
static void dcLow(void) {
    PORT_SRDI &= ~(1 << PIN_DC);
}

/**
 * Send data to the Display.
 */
static void dcHigh(void) {
    PORT_SRDI |= (1 << PIN_DC);
}

static void waitBusy(void) {
    loop_until_bit_is_clear(PINP_SRDI, PIN_BUSY);
}

void display(void) {
    PORT_LED |= (1 << PIN_LED);

    printString("----------------\r\n");

    // 1. Power On
    // VCI already supplied - could supply by MCU output pin?
    // - Supply VCI
    // - Wait 10ms
    _delay_ms(10);

    // 2. Set Initial Configuration
    // board selects 4-wire SPI by pulling BS1 low
    // - Define SPI interface to communicate with MCU

    // - HW Reset
    PORT_SRDI &= ~(1 << PIN_RST);
    _delay_ms(10);
    PORT_SRDI |= (1 << PIN_RST);

    _delay_ms(100);
    waitBusy();

    // - SW Reset by Command 0x12
    dcLow();
    csLow();
    transmit(0x12);
    dcLow();
    csHigh();

    // - Wait 10ms
    waitBusy();
    _delay_ms(10);

    printString("initial config done\r\n");

    // write the first byte of the user id and read it back
    // doesn't seem to work - because the driver is not fully initialized yet?
    dcLow();
    csLow();
    transmit(0x38);
    dcHigh();
    transmit(123);
    dcLow();
    csHigh();

    dcLow();
    csLow();
    transmit(0x2e);
    dcHigh();
    uint8_t id = transmit(0);
    dcLow();
    csHigh();
    
    printUint(id);

    // 3. Send Initialization Code
    // - Set gate driver output by Command 0x01
    // - Set display RAM size by Command 0x11, 0x44, 0x45
    // - Set panel border by Command 0x3C

    // 4. Load Waveform LUT
    // - Sense temperature by int/ext TS by Command 0x18
    // - Load waveform LUT from OTP by Command 0x22, 0x20 or by MCU
    // - Wait BUSY Low
    waitBusy();

    // 5. Write Image and Drive Display Panel
    // - Write image data in RAM by Command 0x4E, 0x4F, 0x24, 0x26
    // - Set softstart setting by Command 0x0C
    // - Drive display panel by Command 0x22, 0x20
    // - Wait BUSY Low
    waitBusy();

    // should do this only when VCI is supplied by MCU pin?
    // 6. Power Off
    // - Deep sleep by Command 0x10
    // - Power OFF

    PORT_LED &= ~(1 << PIN_LED);
}