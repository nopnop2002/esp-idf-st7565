# esp-idf-st7565
ST7565 Driver for esp-idf

![st7565-11](https://user-images.githubusercontent.com/6020549/93008588-62926800-f5b1-11ea-8752-fa042139acdc.JPG)
![st7565-19](https://user-images.githubusercontent.com/6020549/148663141-e12245a4-655c-47c5-9254-ceaaba13286c.JPG)

# Software requirements
ESP-IDF V4.4/V5.x.   
ESP-IDF V5.0 is required when using ESP32-C2.   
ESP-IDF V5.1 is required when using ESP32-C6.   

# Hardware requirements

ST7565 Graphic LCD Module with SPI interface.   
I bought it on AliExpress.   
You can change the interface to Parallel and SPI by changing the chip resistor on the back, but for this project we will use SPI.   

![st7565-1](https://user-images.githubusercontent.com/6020549/93008469-febb6f80-f5af-11ea-991e-e9d38df74b16.JPG)


# Installation

```
git clone https://github.com/nopnop2002/esp-idf-st7565
cd esp-idf-st7565/
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```
__Note for ESP32-C3__   
For some reason, there are development boards that cannot use GPIO06, GPIO08, GPIO09, GPIO19 for SPI clock pins.   
According to the ESP32C3 specifications, these pins can also be used as SPI clocks.   
I used a raw ESP-C3-13 to verify that these pins could be used as SPI clocks.   

# Configuration   
You have to set this config value with menuconfig.   
- CONFIG_WIDTH   
- CONFIG_HEIGHT   
- CONFIG_MOSI_GPIO   
- CONFIG_SCLK_GPIO   
- CONFIG_CS_GPIO   
- CONFIG_DC_GPIO   
- CONFIG_RESET_GPIO   
- CONFIG_BL_GPIO   
- CONFIG_FLIP   
- CONFIG_INVERSION   

![config-1](https://user-images.githubusercontent.com/6020549/93008473-07ac4100-f5b0-11ea-940c-4bd7416f1ebf.jpg)

![config-2](https://user-images.githubusercontent.com/6020549/148663125-94faec59-7e82-46d9-977c-124310dd2e18.jpg)

# Wireing  

|#|ST7565||ESP32|ESP32S2/S3|ESP32C2/C3/C6|
|:-:|:-:|:-:|:-:|:-:|:-:|
|1|DB0|--|N/C|N/C|N/C|
|2|DB1|--|N/C|N/C|N/C|
|3|DB2|--|N/C|N/C|N/C|
|4|DB3|--|N/C|N/C|N/C|
|5|DB4|--|N/C|N/C|N/C|
|6|DB5|--|N/C|N/C|N/C|
|7|DB6(=SCLK)|--|GPIO18(*)|GPIO36(*)|GPIO1(*)|
|8|DB7(=MOSI)|--|GPIO23(*)|GPIO35(*)|GPIO0(*)|
|9|VDD|--|3.3V|3.3V|3.3V|
|10|VSS|--|GND|GND|GND|
|11|LEDA|--|GPIO32(*)|GPIO33(*)|GPIO4(*)|
|12|/CS|--|GPIO5(*)|GPIO34(*)|GPIO5(*)|
|13|/RES|--|GPIO33(*)|GPIO41(*)|GPIO3(*)|
|14|A0|--|GPIO27(*)|GPIO40(*)|GPIO2(*)|
|15|/WR|--|N/C|N/C|N/C|
|16|/RD|--|N/C|N/C|N/C|

For SPI interfaces, DB6 is the SPI CLOCK.   
For SPI interfaces, DB7 is the SPI MOSI.   

(*) You can change any GPIO using menuconfig.   


![st7565-12](https://user-images.githubusercontent.com/6020549/93008589-63c39500-f5b1-11ea-8721-c6b276d3ceba.JPG)
![st7565-13](https://user-images.githubusercontent.com/6020549/93008590-64f4c200-f5b1-11ea-8948-9b56ec54bcec.JPG)
![st7565-14](https://user-images.githubusercontent.com/6020549/93008591-6625ef00-f5b1-11ea-9db4-f35876ab6c2f.JPG)
![st7565-15](https://user-images.githubusercontent.com/6020549/93008592-66be8580-f5b1-11ea-9311-0f5f6310d501.JPG)
![st7565-16](https://user-images.githubusercontent.com/6020549/93008593-66be8580-f5b1-11ea-9787-401ffb47f5b7.JPG)
![st7565-17](https://user-images.githubusercontent.com/6020549/93008595-67571c00-f5b1-11ea-93d7-0ca3b264ed9c.JPG)
![st7565-18](https://user-images.githubusercontent.com/6020549/93008597-67efb280-f5b1-11ea-9e0e-256bd5204bcd.JPG)


# Font File   
I am using this font.

- 8x6 font   
https://github.com/Defragster/ssd1306xled/blob/master/font6x8.h

- 8x8 font   
https://opengameart.org/content/8x8-ascii-bitmap-font-with-c-source

- 8x8 bold font   
https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h
