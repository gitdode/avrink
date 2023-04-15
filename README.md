# AVRInk

Experimental project to drive an E-Ink display like the 
[Adafruit Monochrome 2.13" 250x122 SSD1680](https://www.adafruit.com/product/4197)
with an AVR MCU (ATmega328P) and avr-libc.  

Currently implemented:

* Nearly complete UTF-8 set of GNU Unifont
* Store font code points and pixmaps in program memory instead of RAM
* Use SRAM as frame buffer
* Display initialization
* Draw lines of text in Unifont
* Logging via USART

<img src="https://luniks.net/other/AVRInk-05.jpg"/>

Thanks to [https://github.com/adafruit/Adafruit_EPD](https://github.com/adafruit/Adafruit_EPD)
for helping me out!
