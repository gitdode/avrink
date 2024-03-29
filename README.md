# AVRInk

[![make](https://github.com/gitdode/avrink/actions/workflows/build.yml/badge.svg)](https://github.com/gitdode/avrink/actions/workflows/build.yml)

Project to drive an E-Ink display like the 
[Adafruit Monochrome 2.13" 250x122 SSD1680](https://www.adafruit.com/product/4197)
with an AVR MCU (ATmega328P) and avr-libc.  

Currently implemented:

* Nearly complete UTF-8 set (code points U+0000 to U+00FF) of GNU Unifont
* Small subset of large glyphs in DejaVu: 0-9 and some special characters
* Store font and bitmaps in program memory instead of RAM
* Use SRAM as frame buffer
* Fast and full update mode
* Draw strings in Unifont and DejaVu
* Draw bitmaps
* Write text and bitmaps via USART
* Logging via USART

Thanks to:  

* [https://github.com/adafruit/Adafruit_EPD](https://github.com/adafruit/Adafruit_EPD) 
for helping me out with the display initialization!  
* [https://github.com/markbirss](https://github.com/markbirss) 
for telling me that fast update mode _is_ supported!  
* [https://github.com/sprintersb](https://github.com/sprintersb) 
for helping me to improve the code and making it more efficient!

<img src="https://luniks.net/other/AVRInk/AVRInk-06.jpg"/>

## Write something via USART

Connect to the controller with for example GTKTerm (9600 Baud).  
Write some text and a bitmap:

`c 0` // clear display  
`t 0 0 d 0-9` // write text in DejaVu (large) to row 0 column 0  
`t 2 128 u Small text in` // write text in Unifont (small) to row 2 column 128  
`t 4 128 u Unifont` // write text in Unifont (small) to row 4 column 128  
`t 8 0 d !#%*+,-°` // write text in DejaVu (large) to row 8 column 0  
`b 7 198 0` // write bitmap with index 0 (Tux) to row 7 column 198  
`u 1` // update display in fast update mode  (0 = full update mode)  

<img src="https://luniks.net/other/AVRInk/AVRInk-11.jpg"/>
