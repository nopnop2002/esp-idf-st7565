# esp-idf-st7565
ST7565 Driver for esp-idf

![st7565-11](https://user-images.githubusercontent.com/6020549/93008588-62926800-f5b1-11ea-8752-fa042139acdc.JPG)

You have to set this config value with menuconfig.   
- CONFIG_WIDTH   
- CONFIG_HEIGHT   
- CONFIG_MOSI_GPIO   
- CONFIG_SCLK_GPIO   
- CONFIG_CS_GPIO   
- CONFIG_DC_GPIO   
- CONFIG_RESET_GPIO   
- CONFIG_BL_GPIO   
- CONFIG_ROTATION   
- CONFIG_INVERSION   


```
git clone https://github.com/nopnop2002/esp-idf-st7565
cd esp-idf-st7565/
make menuconfig
make flash
```

![config-1](https://user-images.githubusercontent.com/6020549/93008473-07ac4100-f5b0-11ea-940c-4bd7416f1ebf.jpg)

![config-2](https://user-images.githubusercontent.com/6020549/93008474-0aa73180-f5b0-11ea-9a5d-0ae4867a4fc4.jpg)

---

# Software requirements

esp-idf v4.2-dev-2243 or later.

---

# Hardware requirements

ST7565 Graphic LCD Module with SPI interface.

![st7565-1](https://user-images.githubusercontent.com/6020549/93008469-febb6f80-f5af-11ea-991e-e9d38df74b16.JPG)

---

# Wireing  

|ST7565||ESP32|
|:-:|:-:|:-:|
|1 DB0|--|N/C|
|2 DB1|--|N/C|
|3 DB2|--|N/C|
|4 DB3|--|N/C|
|5 DB4|--|N/C|
|6 DB5|--|N/C|
|7 SCL|--|GPIO18|
|8 SDI|--|GPIO23|
|9 VDD|--|3.3V|
|10 VSS|--|GND|
|11 LEDA|--|GPIO32(*)|
|12 /CS|--|GPIO5(*)|
|13 /RES|--|GPIO33(*)|
|14 A0|--|GPIO27(*)|
|15 /WR|--|N/C|
|16 /RD|--|N/C|

(*) You can change any GPIO using menuconfig.   

---

![st7565-12](https://user-images.githubusercontent.com/6020549/93008589-63c39500-f5b1-11ea-8721-c6b276d3ceba.JPG)
![st7565-13](https://user-images.githubusercontent.com/6020549/93008590-64f4c200-f5b1-11ea-8948-9b56ec54bcec.JPG)
![st7565-14](https://user-images.githubusercontent.com/6020549/93008591-6625ef00-f5b1-11ea-9db4-f35876ab6c2f.JPG)
![st7565-15](https://user-images.githubusercontent.com/6020549/93008592-66be8580-f5b1-11ea-9311-0f5f6310d501.JPG)
![st7565-16](https://user-images.githubusercontent.com/6020549/93008593-66be8580-f5b1-11ea-9787-401ffb47f5b7.JPG)
![st7565-17](https://user-images.githubusercontent.com/6020549/93008595-67571c00-f5b1-11ea-93d7-0ca3b264ed9c.JPG)
![st7565-18](https://user-images.githubusercontent.com/6020549/93008597-67efb280-f5b1-11ea-9e0e-256bd5204bcd.JPG)

---

# Font File   
I am using this font.

- 8x6 font   
https://github.com/Defragster/ssd1306xled/blob/master/font6x8.h

- 8x8 font   
https://opengameart.org/content/8x8-ascii-bitmap-font-with-c-source

- 8x8 bold font   
https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h
