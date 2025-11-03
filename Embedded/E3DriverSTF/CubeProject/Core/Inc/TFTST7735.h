/*
 * TFTST7735.h
 *
 *  Created on: Nov 2, 2025
 *      Author: dasre
 */

#ifndef INC_TFTST7735_H_
#define INC_TFTST7735_H_

class TFT_ST7735 {
public:
	
	TFT_ST7735();
	void DrawPixel(uint16_t x, uint16_t y, uint16_t color);
	
	void WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
	void WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
	void WriteData(uint8_t* data, uint16_t size);
	
	virtual ~TFT_ST7735();
};

#endif /* INC_TFTST7735_H_ */
