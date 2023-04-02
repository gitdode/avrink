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

    printString("starting to drive display...\r\n");

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
    csHigh();

    // - Wait 10ms
    waitBusy();
    _delay_ms(10);

    printString("done setting initial configuration\r\n");
    
    // 3. Send Initialization Code
    // - Set gate driver output by Command 0x01
    dcLow();
    csLow();
    transmit(0x01);
    dcHigh();
    transmit(250 - 1);
    transmit((250 - 1) >> 8);
    transmit(0);
    csHigh();
    
    // - Set display RAM size by Command 0x11, 0x44, 0x45
    dcLow();
    csLow();
    transmit(0x11);
    dcHigh();
    transmit(0x03);
    csHigh();
    
    dcLow();
    csLow();
    transmit(0x44);
    dcHigh();
    transmit(1);
    transmit(16);
    csHigh();
    
    dcLow();
    csLow();
    transmit(0x45);
    dcHigh();
    transmit(0x00);
    transmit(0x00);
    transmit(250 - 1);
    transmit((250 - 1) >> 8);
    csHigh();
    
    // - Set panel border by Command 0x3C
    dcLow();
    csLow();
    transmit(0x3c);
    dcHigh();
    transmit(0x05);
    csHigh();
    
    printString("done sending initialization code\r\n");

    // 4. Load Waveform LUT
    // - Sense temperature by int/ext TS by Command 0x18
    // - Load waveform LUT from OTP by Command 0x22, 0x20 or by MCU
    // - Wait BUSY Low
    
    waitBusy();
    
    /*
    // Vcom voltage
    dcLow();
    csLow();
    transmit(0x2c);
    dcHigh();
    transmit(0x36); // value not in table?
    csHigh();
    
    // gate voltage
    dcLow();
    csLow();
    transmit(0x03);
    dcHigh();
    transmit(0x17); // 0x17 = 20V = 0x00 (POR)
    csHigh();

    // source voltage
    dcLow();
    csLow();
    transmit(0x04);
    dcHigh();
    transmit(0x41); (POR)
    transmit(0x00); // value not in table, should be 0xa8 (POR)?
    transmit(0x32); (POR)
    csHigh();
    */
    
    // 5. Write Image and Drive Display Panel
    // - Write image data in RAM by Command 0x4E, 0x4F, 0x24, 0x26
    dcLow();
    csLow();
    transmit(0x4e);
    dcHigh();
    transmit(1); // offset 1? check 0x44 and 0x45
    csHigh();
    
    dcLow();
    csLow();
    transmit(0x4f);
    dcHigh();
    transmit(0);
    transmit(0);
    csHigh();
    
    // write to BW RAM
    dcLow();
    csLow();
    transmit(0x24);
    dcHigh();
    // draw vertical bars
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 16; j++) {
            transmit(0);
            transmit(0);
        }
        for (int j = 0; j < 16; j++) {
            transmit(255);
            transmit(255);
            transmit(255);
        }
    }
    csHigh();
    
    printString("done writing data to RAM\r\n");
    
    // - Set softstart setting by Command 0x0C
    dcLow();
    csLow();
    transmit(0x0c);
    dcHigh();
    transmit(0x8b);
    transmit(0x9c);
    transmit(0x96);
    transmit(0x0f);
    csHigh();
    
    printString("done setting softstart\r\n");
    
    // - Drive display panel by Command 0x22, 0x20
    dcLow();
    csLow();
    transmit(0x22);
    dcHigh();
    transmit(0xf4);
    csHigh();
    
    dcLow();
    csLow();
    transmit(0x20);
    csHigh();
    
    // - Wait BUSY Low
    waitBusy();

    printString("done driving display\r\n");

    // 6. Power Off
    // - Deep sleep by Command 0x10
    dcLow();
    csLow();
    transmit(0x10);
    dcHigh();
    transmit(0x01);
    csHigh();
    
    printString("done setting deep sleep\r\n");
    
    // - Power OFF

    PORT_LED &= ~(1 << PIN_LED);
}