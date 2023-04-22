# AVRInk

[![make](https://github.com/gitdode/avrink/actions/workflows/build.yml/badge.svg)](https://github.com/gitdode/avrink/actions/workflows/build.yml)

Experimental project to drive an E-Ink display like the 
[Adafruit Monochrome 2.13" 250x122 SSD1680](https://www.adafruit.com/product/4197)
with an AVR MCU (ATmega328P) and avr-libc.  

Currently implemented:

* Nearly complete UTF-8 set of GNU Unifont
* Store font and bitmaps in program memory instead of RAM
* Use SRAM as frame buffer
* Draw strings in Unifont
* Draw bitmaps
* Clear display, write text and bitmaps and update display via USART
* Logging via USART

<img src="https://luniks.net/other/AVRInk-06.jpg"/>

Thanks to [https://github.com/adafruit/Adafruit_EPD](https://github.com/adafruit/Adafruit_EPD)
for helping me out!

## Write something via USART

Connect to the controller with for example GTKTerm (9600 Baud).  
Write some text and a bitmap:

`c 0` // clear display to white  
`t 0 0 So this is some text.` // write text to column 0 row 0  
`t 2 0 And here is another line`  
`t 4 0 of text.`  
`b 0 198 0` // write bitmap with index 0 (Tux) to row 0 column 198  
`t 6 0 There is also Tux on the`  
`t 8 0 right. That's about it!`  
`u` // update display  
