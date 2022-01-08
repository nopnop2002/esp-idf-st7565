#ifndef MAIN_ST7565_H_
#define MAIN_ST7565_H_

#include "driver/spi_master.h"

#define BLACK			0xff
#define WHITE			0x00

#define VERTICAL		0
#define HORIZONTAL		1


#define DIRECTION0		0
#define DIRECTION90		1
#define DIRECTION180	2
#define DIRECTION270	3


typedef struct {
	uint16_t _width;
	uint16_t _height;
	uint16_t _font_direction;
	uint16_t _font_revert;
	int16_t _dc;
	int16_t _bl;
	int16_t _flip;
	int16_t _invert;
	int16_t _blen;
	uint8_t _buffer[128*64/8];
	spi_device_handle_t _SPIHandle;
} TFT_t;

void spi_master_init(TFT_t * dev, int16_t GPIO_MOSI, int16_t GPIO_SCLK, int16_t GPIO_CS, int16_t GPIO_DC, int16_t GPIO_RESET, int16_t GPIO_BL);
bool spi_master_write_byte(spi_device_handle_t SPIHandle, const uint8_t* Data, size_t DataLength);
bool spi_master_write_command(TFT_t * dev, uint8_t cmd);
bool spi_master_write_data(TFT_t * dev, uint8_t * data, int16_t len);
bool spi_master_write_data_byte(TFT_t * dev, uint8_t data);

void delayMS(int ms);
void lcdInit(TFT_t * dev, int width, int height);
void lcdWriteBuffer(TFT_t * dev);
void lcdDrawPixel(TFT_t * dev, uint16_t x, uint16_t y, uint8_t color);
void lcdDrawMultiPixels(TFT_t * dev, uint16_t x, uint16_t y, uint16_t size, uint8_t * colors);
void lcdDrawFillRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
void lcdFillScreen(TFT_t * dev, uint8_t color);
void lcdDrawLine(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
void lcdDrawRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
void lcdDrawRectAngle(TFT_t * dev, uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint8_t color);
void lcdDrawTriangle(TFT_t * dev, uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint8_t color);
void lcdDrawCircle(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t r, uint8_t color);
void lcdDrawFillCircle(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t r, uint8_t color);
void lcdDrawRoundRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t r, uint8_t color);
void lcdDrawArrow(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t w, uint8_t color);
void lcdDrawFillArrow(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t w, uint8_t color);
int lcdDrawChar2(TFT_t * dev, uint8_t *font, uint16_t x, uint16_t y, uint8_t ascii, uint8_t color);
int lcdDrawString2(TFT_t * dev, uint8_t * font, uint16_t x, uint16_t y, uint8_t * ascii, uint8_t color);
void lcdSetFontDirection(TFT_t * dev, uint16_t);
void lcdBacklightOff(TFT_t * dev);
void lcdBacklightOn(TFT_t * dev);
void lcdFlipOn(TFT_t * dev);
void lcdInversionOn(TFT_t * dev);
void lcdSetFontRevert(TFT_t * dev);
void lcdUnsetFontRevert(TFT_t * dev);

#endif /* MAIN_ST7565_H_ */

