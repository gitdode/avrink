# AVRInk

Experimental project to drive an E-Ink display like the 
[Adafruit Monochrome 2.13" 250x122 SSD1680](https://www.adafruit.com/product/4197)
with an AVR MCU and avr-libc.  

Currently implemented:

* Store font pixmaps in program memory instead of RAM
* Use SRAM as frame buffer
* Display initialization
* Draw the single character the font has to offer for now :)

<img src="https://luniks.net/other/AVRInk-03.jpg" height="405"/>

Thanks to [https://github.com/adafruit/Adafruit_EPD](https://github.com/adafruit/Adafruit_EPD)
for helping me out!
