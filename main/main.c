#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_vfs.h"

#include "st7565.h"
#include "font6x8.h"
#include "font8x8.h"
#include "font8x8_bold.h"

#define	INTERVAL		400
#define WAIT	vTaskDelay(INTERVAL)

static const char *TAG = "ST7565";

// You have to set these CONFIG value using menuconfig.
#if 0
#define CONFIG_WIDTH 128
#define CONFIG_HEIGHT 64
#define CONFIG_MOSI_GPIO 23
#define CONFIG_SCLK_GPIO 18
#define CONFIG_CS_GPIO 5
#define CONFIG_DC_GPIO 27
#define CONFIG_RESET_GPIO 33
#define CONFIG_BL_GPIO 32
#endif

TickType_t FillTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	lcdFillScreen(dev, WHITE);
	lcdWriteBuffer(dev);
	vTaskDelay(500);
	lcdFillScreen(dev, BLACK);
	lcdWriteBuffer(dev);
	vTaskDelay(500);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%d",diffTick*portTICK_RATE_MS);
	return diffTick;
}

TickType_t BarTest(TFT_t * dev, int direction, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	if (direction == HORIZONTAL) {
		uint16_t y1 = height/5;
		lcdDrawFillRect(dev, 0, 0, width-1, y1-1, BLACK);
		vTaskDelay(1);
		lcdDrawFillRect(dev, 0, y1, width-1, y1*2-1, WHITE);
		vTaskDelay(1);
		lcdDrawFillRect(dev, 0, y1*2, width-1, y1*3-1, BLACK);
		vTaskDelay(1);
		lcdDrawFillRect(dev, 0, y1*3, width-1, y1*4-1, WHITE);
		vTaskDelay(1);
		lcdDrawFillRect(dev, 0, y1*4, width-1, height-1, BLACK);
		lcdWriteBuffer(dev);
	} else {
		uint16_t x1 = width/5;
		lcdDrawFillRect(dev, 0, 0, x1-1, height-1, BLACK);
		vTaskDelay(1);
		lcdDrawFillRect(dev, x1, 0, x1*2-1, height-1, WHITE);
		vTaskDelay(1);
		lcdDrawFillRect(dev, x1*2, 0, x1*3-1, height-1, BLACK);
		vTaskDelay(1);
		lcdDrawFillRect(dev, x1*3, 0, x1*4-1, height-1, WHITE);
		vTaskDelay(1);
		lcdDrawFillRect(dev, x1*4, 0, width-1, height-1, BLACK);
		lcdWriteBuffer(dev);
	}

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%d",diffTick*portTICK_RATE_MS);
	return diffTick;
}

TickType_t ArrowTest(TFT_t * dev, uint8_t * font, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	// get font width & height
	uint8_t fontWidth;
	uint8_t fontHeight;
	fontWidth = font[0];
	fontHeight = font[1];
	//ESP_LOGI(__FUNCTION__,"fontWidth=%d fontHeight=%d",fontWidth,fontHeight);
	
	uint16_t xpos;
	uint16_t ypos;
	int	stlen;
	uint8_t ascii[24];

	lcdFillScreen(dev, WHITE);

	strcpy((char *)ascii, "ST7565");
	ypos = ((height + fontHeight) / 2) - 1;
	//printf("height=%d fontHeight=%d ypos=%d\n", height,fontHeight,ypos);
	xpos = (width - (strlen((char *)ascii) * fontWidth)) / 2;
	lcdSetFontDirection(dev, DIRECTION0);
	lcdDrawString2(dev, font, xpos, ypos, ascii, BLACK);

	lcdDrawTriangle(dev, 4, 4, 10, 10, 225, BLACK);
	//lcdDrawFillArrow(dev, 10, 10, 0, 0, 5, BLACK);
	strcpy((char *)ascii, "0,0");
	lcdDrawString2(dev, font, 0, 20, ascii, BLACK);

	lcdDrawTriangle(dev, width-4, 4, 10, 10, 135, BLACK);
	//lcdDrawFillArrow(dev, width-11, 10, width-1, 0, 5, BLACK);
	sprintf((char *)ascii, "%d,0",width-1);
	stlen = strlen((char *)ascii);
	xpos = (width-1) - (fontWidth*stlen);
	lcdDrawString2(dev, font, xpos, 20, ascii, BLACK);

	lcdDrawTriangle(dev, width-4, height-5, 10, 10, 45, BLACK);
	//lcdDrawFillArrow(dev, 10, height-11, 0, height-1, 5, BLACK);
	sprintf((char *)ascii, "0,%d",height-1);
	ypos = (height-11) - (fontHeight) + 5;
	lcdDrawString2(dev, font, 0, ypos, ascii, BLACK);

	lcdDrawTriangle(dev, 4, height-5, 10, 10, 315, BLACK);
	//lcdDrawFillArrow(dev, width-11, height-11, width-1, height-1, 5, BLACK);
	sprintf((char *)ascii, "%d,%d",width-1, height-1);
	stlen = strlen((char *)ascii);
	xpos = (width-1) - (fontWidth*stlen);
	lcdDrawString2(dev, font, xpos, ypos, ascii, BLACK);
	lcdWriteBuffer(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%d",diffTick*portTICK_RATE_MS);
	return diffTick;
}

TickType_t DirectionTest(TFT_t * dev, uint8_t * font, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	// get font width & height
	uint8_t fontWidth;
	uint8_t fontHeight;
	fontWidth = font[0];
	fontHeight = font[1];
	//ESP_LOGI(__FUNCTION__,"fontWidth=%d fontHeight=%d",fontWidth,fontHeight);

	lcdFillScreen(dev, WHITE);
	uint8_t ascii[20];
	strcpy((char *)ascii, "ST7565");
	lcdSetFontDirection(dev, DIRECTION0);
	lcdDrawString2(dev, font, 0, fontHeight-1, ascii, BLACK);

	lcdSetFontDirection(dev, DIRECTION90);
	lcdDrawString2(dev, font, (width-fontHeight-1), 0, ascii, BLACK);

	lcdSetFontDirection(dev, DIRECTION180);
	lcdDrawString2(dev, font, (width-1), (height-fontHeight-1), ascii, BLACK);

	lcdSetFontDirection(dev, DIRECTION270);
	lcdDrawString2(dev, font, fontWidth-1, height-1, ascii, BLACK);
	lcdWriteBuffer(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%d",diffTick*portTICK_RATE_MS);
	return diffTick;
}


TickType_t LineTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	lcdFillScreen(dev, WHITE);
	for(int ypos=0;ypos<height;ypos=ypos+10) {
		lcdDrawLine(dev, 0, ypos, width, ypos, BLACK);
	}

	for(int xpos=0;xpos<width;xpos=xpos+10) {
		lcdDrawLine(dev, xpos, 0, xpos, height, BLACK);
	}
	lcdWriteBuffer(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%d",diffTick*portTICK_RATE_MS);
	return diffTick;
}

TickType_t CircleTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	lcdFillScreen(dev, WHITE);
	uint16_t xpos = width/2;
	uint16_t ypos = height/2;
	for(int i=5;i<height;i=i+5) {
		lcdDrawCircle(dev, xpos, ypos, i, BLACK);
	}
	lcdWriteBuffer(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%d",diffTick*portTICK_RATE_MS);
	return diffTick;
}

TickType_t RectAngleTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	lcdFillScreen(dev, WHITE);
	uint16_t xpos = width/2;
	uint16_t ypos = height/2;

	uint16_t w = height * 0.8;
	uint16_t h = w * 0.5;

#if 0
	for(int angle=0;angle<=(360*3);angle=angle+30) {
		lcdDrawRectAngle(dev, xpos, ypos, w, h, angle, BLACK);
		lcdWriteBuffer(dev);
		usleep(10000);
		lcdDrawRectAngle(dev, xpos, ypos, w, h, angle, WHITE);
		lcdWriteBuffer(dev);
	}
#endif

	lcdDrawRectAngle(dev, xpos, ypos, w, h, 0, BLACK);
	lcdWriteBuffer(dev);
	vTaskDelay(1000 / portTICK_PERIOD_MS);

	for(int angle=0;angle<=180;angle=angle+30) {
		lcdDrawRectAngle(dev, xpos, ypos, w, h, angle, BLACK);
		lcdWriteBuffer(dev);
	}

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%d",diffTick*portTICK_RATE_MS);
	return diffTick;
}

TickType_t TriangleTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	lcdFillScreen(dev, WHITE);
	uint16_t xpos = width/2;
	uint16_t ypos = height/2;

	uint16_t w = height / 2;
	uint16_t h = w * 1.0;

#if 0
	for(int angle=0;angle<=(360*2);angle=angle+30) {
		lcdDrawTriangle(dev, xpos, ypos, w, h, angle, BLACK);
		lcdWriteBuffer(dev);
		usleep(10000);
		lcdDrawTriangle(dev, xpos, ypos, w, h, angle, WHITE);
		lcdWriteBuffer(dev);
	}
#endif

	lcdDrawTriangle(dev, xpos, ypos, w, h, 0, BLACK);
	lcdWriteBuffer(dev);
	vTaskDelay(1000 / portTICK_PERIOD_MS);

	for(int angle=0;angle<=360;angle=angle+30) {
		lcdDrawTriangle(dev, xpos, ypos, w, h, angle, BLACK);
		lcdWriteBuffer(dev);
	}

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%d",diffTick*portTICK_RATE_MS);
	return diffTick;
}

TickType_t RoundRectTest(TFT_t * dev, int width, int height) {
	TickType_t startTick, endTick, diffTick;
	startTick = xTaskGetTickCount();

	uint16_t limit = width;
	if (width > height) limit = height;
	lcdFillScreen(dev, WHITE);
	for(int i=5;i<limit;i=i+5) {
		if (i > (limit-i-1) ) break;
		//ESP_LOGI(__FUNCTION__, "i=%d, width-i-1=%d",i, width-i-1);
		lcdDrawRoundRect(dev, i, i, (width-i-1), (height-i-1), 10, BLACK);
	}
	lcdWriteBuffer(dev);

	endTick = xTaskGetTickCount();
	diffTick = endTick - startTick;
	ESP_LOGI(__FUNCTION__, "elapsed time[ms]:%d",diffTick*portTICK_RATE_MS);
	return diffTick;
}

void ST7565(void *pvParameters)
{
	TFT_t dev;
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
	lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);

#if CONFIG_ROTATION
	ESP_LOGI(TAG, "Enable Display Rotation");
	lcdRotationOn(&dev);
#endif

#if CONFIG_INVERSION
	ESP_LOGI(TAG, "Enable Display Inversion");
	lcdInversionOn(&dev);
#endif

#if 0
	//for TEST
	while (1) {
		lcdFillScreen(&dev, WHITE);
		uint8_t ascii[24];
		strcpy((char *)ascii, "ST7565");
		uint8_t ch;
		ch = 0x42;

		lcdSetFontDirection(&dev, DIRECTION0);
		lcdDrawChar2(&dev, font6x8, 0, 8, ch, BLACK);
		lcdDrawString2(&dev, font6x8, 8, 8, ascii, BLACK);

		lcdDrawChar2(&dev, font8x8, 0, 16, ch, BLACK);
		lcdDrawString2(&dev, font8x8, 8, 16, ascii, BLACK);

		lcdDrawChar2(&dev, font8x8_bold, 0, 24, ch, BLACK);
		lcdDrawString2(&dev, font8x8_bold, 8, 24, ascii, BLACK);

		lcdWriteBuffer(&dev);
		WAIT;
	}
#endif

#if 0
	//for TEST
	while(1) {
		TriangleTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		RectAngleTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;
	}
#endif

	while(1) {
		FillTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		BarTest(&dev, VERTICAL, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		BarTest(&dev, HORIZONTAL, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		ArrowTest(&dev, font8x8, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		LineTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		CircleTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		RectAngleTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		RoundRectTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		TriangleTest(&dev, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		DirectionTest(&dev, font8x8, CONFIG_WIDTH, CONFIG_HEIGHT);
		WAIT;

		// Multi Font Test
		uint8_t ascii[40];
		lcdFillScreen(&dev, WHITE);
		lcdSetFontDirection(&dev, DIRECTION0);
		strcpy((char *)ascii, "6x8 Font");
		int xpos = (CONFIG_WIDTH - (strlen((char *)ascii) * 6)) / 2;
		lcdDrawString2(&dev, font6x8, xpos, 8, ascii, BLACK);

		lcdSetFontRevert(&dev);
		lcdDrawString2(&dev, font6x8, xpos, 16, ascii, BLACK);
		lcdUnsetFontRevert(&dev);

		strcpy((char *)ascii, "8x8 NormalFont");
		xpos = (CONFIG_WIDTH - (strlen((char *)ascii) * 8)) / 2;
		lcdDrawString2(&dev, font8x8, xpos, 32, ascii, BLACK);

		lcdSetFontRevert(&dev);
		lcdDrawString2(&dev, font8x8, xpos, 40, ascii, BLACK);
		lcdUnsetFontRevert(&dev);

		strcpy((char *)ascii, "8x8 Bold Font");
		xpos = (CONFIG_WIDTH - (strlen((char *)ascii) * 8)) / 2;
		lcdDrawString2(&dev, font8x8_bold, xpos, 56, ascii, BLACK);

		lcdSetFontRevert(&dev);
		lcdDrawString2(&dev, font8x8_bold, xpos, 64, ascii, BLACK);
		lcdUnsetFontRevert(&dev);

		lcdWriteBuffer(&dev);
		WAIT;

	} // end while

	// never reach
	while (1) {
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}


void app_main(void)
{
	xTaskCreate(ST7565, "ST7565", 1024*6, NULL, 2, NULL);
}
