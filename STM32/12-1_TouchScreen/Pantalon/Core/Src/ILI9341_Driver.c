#include "ILI9341_Driver.h"

extern SPI_HandleTypeDef hspi3;
#include "characters.h"

static void ILI9341_SPI_Init(void);
static void Before_Sending_Data(void);
static void Before_Sending_Command(void);
static void ILI9341_Send_Data(unsigned char data);
static void ILI9341_Send_Command(unsigned char command);
static void ILI9341_Send_Burst(unsigned short color, unsigned long len);
//static void ILI9341_Draw_Double_Pixel(int x, int y, unsigned int color1, unsigned int color2);
static void  ILI9341_Draw_Char(int x, int y, unsigned int color, unsigned int phone, unsigned char charcode, unsigned char size);

static unsigned int X_SIZE = 240;
static unsigned int Y_SIZE = 320;

unsigned char hh;
extern SPI_HandleTypeDef hspi1;
#define lcd_spi hspi1

void LCD_ILI9341_Init(void) {
	ILI9341_SPI_Init();

	/* Reset The Screen */
	ILI9341_Reset();
	HAL_Delay(5);

	/* Power Control A */
	ILI9341_Send_Command(0xCB);
	ILI9341_Send_Data(0x39);
	ILI9341_Send_Data(0x2C);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x34);
	ILI9341_Send_Data(0x02);

	/* Power Control B */
	ILI9341_Send_Command(0xCF);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0xC1);
	ILI9341_Send_Data(0x30);

	/* Driver timing control A */
	ILI9341_Send_Command(0xE8);
	ILI9341_Send_Data(0x85);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x78);

	/* Driver timing control B */
	ILI9341_Send_Command(0xEA);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x00);

	/* Power on Sequence control */
	ILI9341_Send_Command(0xED);
	ILI9341_Send_Data(0x64);
	ILI9341_Send_Data(0x03);
	ILI9341_Send_Data(0x12);
	ILI9341_Send_Data(0x81);

	/* Pump ratio control */
	ILI9341_Send_Command(0xF7);
	ILI9341_Send_Data(0x20);

	/* Power Control 1 */
	ILI9341_Send_Command(0xC0);
	ILI9341_Send_Data(0x23);

	/* Power Control 2 */
	ILI9341_Send_Command(0xC1);
	ILI9341_Send_Data(0x10);

	/* VCOM Control 1 */
	ILI9341_Send_Command(0xC5);
	ILI9341_Send_Data(0x3E);
	ILI9341_Send_Data(0x28);

	/* VCOM Control 2 */
	ILI9341_Send_Command(0xC7);
	ILI9341_Send_Data(0x86);

	/* VCOM Control 2 */
	ILI9341_Send_Command(0x36);
	ILI9341_Send_Data(0x40);

	/* Pixel Format Set */
	ILI9341_Send_Command(0x3A);
	ILI9341_Send_Data(0x55);    //16bit

	ILI9341_Send_Command(0xB1);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x18);

	/* Display Function Control */
	ILI9341_Send_Command(0xB6);
	ILI9341_Send_Data(0x08);
	ILI9341_Send_Data(0x82);
	ILI9341_Send_Data(0x27);

	/* 3GAMMA FUNCTION DISABLE */
	ILI9341_Send_Command(0xF2);
	ILI9341_Send_Data(0x00);

	/* GAMMA CURVE SELECTED */
	ILI9341_Send_Command(0x26); //Gamma set
	ILI9341_Send_Data(0x01); 	//Gamma Curve (G2.2)

	//Positive Gamma  Correction
	ILI9341_Send_Command(0xE0);
	ILI9341_Send_Data(0x0F);
	ILI9341_Send_Data(0x31);
	ILI9341_Send_Data(0x2B);
	ILI9341_Send_Data(0x0C);
	ILI9341_Send_Data(0x0E);
	ILI9341_Send_Data(0x08);
	ILI9341_Send_Data(0x4E);
	ILI9341_Send_Data(0xF1);
	ILI9341_Send_Data(0x37);
	ILI9341_Send_Data(0x07);
	ILI9341_Send_Data(0x10);
	ILI9341_Send_Data(0x03);
	ILI9341_Send_Data(0x0E);
	ILI9341_Send_Data(0x09);
	ILI9341_Send_Data(0x00);

	//Negative Gamma  Correction
	ILI9341_Send_Command(0xE1);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x0E);
	ILI9341_Send_Data(0x14);
	ILI9341_Send_Data(0x03);
	ILI9341_Send_Data(0x11);
	ILI9341_Send_Data(0x07);
	ILI9341_Send_Data(0x31);
	ILI9341_Send_Data(0xC1);
	ILI9341_Send_Data(0x48);
	ILI9341_Send_Data(0x08);
	ILI9341_Send_Data(0x0F);
	ILI9341_Send_Data(0x0C);
	ILI9341_Send_Data(0x31);
	ILI9341_Send_Data(0x36);
	ILI9341_Send_Data(0x0F);

	/* Interface control */
	ILI9341_Send_Command(0xF6);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x00);

	//EXIT SLEEP
	ILI9341_Send_Command(0x11);
	HAL_Delay(120);

	//TURN ON DISPLAY
	ILI9341_Send_Command(0x29);
	HAL_Delay(20);
}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void ILI9341_SPI_Init() {
	/* SPI1 is initialized by MX_SPI1_Init before the LCD starts. */
}

void ILI9341_SPI_Send(unsigned char data)
{
	HAL_SPI_Transmit(&lcd_spi, &data, 1, 100);
}

void ILI9341_SPI_Send_Multiple(unsigned char data, int size)
{
	HAL_SPI_Transmit(&lcd_spi, &data, size, 10);
}

void ILI9341_Reset() {
	RESET_ON;
	HAL_Delay(50);
	RESET_OFF;
	CS_ON;
	HAL_Delay(50);
	ILI9341_Send_Command(0x01);
	CS_OFF;
}

void LCD_ILI9341_Rotate(unsigned char rotation) {
	ILI9341_Send_Command(0x36);
	switch (rotation) {
	case 0:
		ILI9341_Send_Data(0x40);
		X_SIZE = 240;
		Y_SIZE = 320;
		break;
	case 1:
		ILI9341_Send_Data(0x20);
		X_SIZE = 320;
		Y_SIZE = 240;
		break;
	case 2:
		ILI9341_Send_Data(0x80);
		X_SIZE = 240;
		Y_SIZE = 320;
		break;
	case 3:
		ILI9341_Send_Data(0xE0);
		X_SIZE = 320;
		Y_SIZE = 240;
		break;
	}
}

void ILI9341_SPI_Send_32(unsigned char command, unsigned long data) {
	CS_ON;
	DC_COMMAND;
	ILI9341_SPI_Send(command);

	DC_DATA;
	ILI9341_SPI_Send(data >> 24);
	ILI9341_SPI_Send(data >> 16);
	ILI9341_SPI_Send(data >> 8);
	ILI9341_SPI_Send(data);
	CS_OFF;

}

void ILI9341_Set_Address(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
	unsigned long t;
	t = x1;
	t <<= 16;
	t |= x2;
	ILI9341_SPI_Send_32(0x2A, t); //Column Addres Set
	t = y1;
	t <<= 16;
	t |= y2;
	ILI9341_SPI_Send_32(0x2B, t); //Page Addres Set
}

void LCD_ILI9341_Fill(unsigned int color)
{
	ILI9341_Set_Address(0, 0, 319, 239);
	ILI9341_Send_Burst(color, (long)X_SIZE * (long)Y_SIZE);
}

void LCD_ILI9341_DrawPixel(int x, int y, unsigned int color)
{
	if((x < 0) || (y < 0) || (x >= X_SIZE) || (y >= Y_SIZE))
	{
		return;
	}
	ILI9341_Set_Address(x, y, x, y);
	CS_ON;
	DC_COMMAND;
	ILI9341_SPI_Send(0x2C);
	DC_DATA;
	ILI9341_SPI_Send(color>>8);
	ILI9341_SPI_Send(color);
	CS_OFF;
}

void LCD_ILI9341_DrawFilledRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int color)
{
	ILI9341_Set_Address(x1, y1, x2, y2);
	ILI9341_Send_Burst(color, (long)(x2-x1+1) * (long)(y2-y1+1));
}

void LCD_ILI9341_DrawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color)
{
	LCD_ILI9341_DrawFilledRectangle(x1, y1, x2, y1, color);
	LCD_ILI9341_DrawFilledRectangle(x1, y2, x2, y2, color);
	LCD_ILI9341_DrawFilledRectangle(x1, y1, x1, y2, color);
	LCD_ILI9341_DrawFilledRectangle(x2, y1, x2, y2, color);
}

void LCD_ILI9341_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color)
{
	int steep = abs(y2-y1) > abs(x2-x1);

	if (steep)
	{
		swap(x1,y1);
		swap(x2,y2);
	}

	if(x1>x2)
	{
		swap(x1,x2);
		swap(y1,y2);
	}

	int dx,dy;
	dx = (x2 - x1);
	dy = abs(y2 - y1);
	int err = dx / 2;
	int ystep;
	if(y1 < y2)
	{
		ystep = 1;
	}
	else
	{
		ystep = -1;
	}
	for (; x1 <= x2; x1++)
	{
		if (steep)
		{
			ILI9341_Draw_Pixel(y1, x1, color);
		}
		else
		{
			ILI9341_Draw_Pixel(x1, y1, color);
		}
		err -= dy;
		if (err < 0)
		{
			y1 += ystep;
			err = dx;
		}
	}
}

void LCD_ILI9341_DrawCircle(unsigned int x0, unsigned int y0, int r, unsigned int color, unsigned char flood) {
	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0;
	int y = r;
	if (flood == 0) {
		ILI9341_Draw_Pixel(x0, y0 + r, color);
		ILI9341_Draw_Pixel(x0, y0 - r, color);
		ILI9341_Draw_Pixel(x0 + r, y0, color);
		ILI9341_Draw_Pixel(x0 - r, y0, color);
		while (x < y) {
			if (f >= 0) {
				y--;
				ddF_y += 2;
				f += ddF_y;
			}
			x++;
			ddF_x += 2;
			f += ddF_x;
			ILI9341_Draw_Pixel(x0 + x, y0 + y, color);
			ILI9341_Draw_Pixel(x0 - x, y0 + y, color);
			ILI9341_Draw_Pixel(x0 + x, y0 - y, color);
			ILI9341_Draw_Pixel(x0 - x, y0 - y, color);
			ILI9341_Draw_Pixel(x0 + y, y0 + x, color);
			ILI9341_Draw_Pixel(x0 - y, y0 + x, color);
			ILI9341_Draw_Pixel(x0 + y, y0 - x, color);
			ILI9341_Draw_Pixel(x0 - y, y0 - x, color);
		}
	} else {
		ILI9341_Draw_Pixel(x0, y0 + r, color);
		ILI9341_Draw_Pixel(x0, y0 - r, color);
		ILI9341_Set_Address(x0 - r, y0, x0 + r, y0);
		CS_ON;
		DC_COMMAND;
		ILI9341_SPI_Send(0x2C);
		DC_DATA;
		for (uint32_t fff = 0; fff < r * 2 + 1; fff++) {
			ILI9341_SPI_Send(color >> 8);
			ILI9341_SPI_Send(color);
		}
		while (x < y) {
			if (f >= 0) {
				y--;
				ddF_y += 2;
				f += ddF_y;
			}
			x++;
			ddF_x += 2;
			f += ddF_x;
			ILI9341_Set_Address(x0 - x, y0 + y, x0 + x, y0 + y);
			DC_COMMAND;
			ILI9341_SPI_Send(0x2C);
			DC_DATA;
			for (uint32_t fff = 0; fff < x * 2 + 1; fff++) {
				ILI9341_SPI_Send(color >> 8);
				ILI9341_SPI_Send(color);
			}
			ILI9341_Set_Address(x0 - x, y0 - y, x0 + x, y0 - y);
			DC_COMMAND;
			ILI9341_SPI_Send(0x2C);
			DC_DATA;
			for (uint32_t fff = 0; fff < x * 2 + 1; fff++) {
				ILI9341_SPI_Send(color >> 8);
				ILI9341_SPI_Send(color);
			}
			ILI9341_Set_Address(x0 - y, y0 + x, x0 + y, y0 + x);
			DC_COMMAND;
			ILI9341_SPI_Send(0x2C);
			DC_DATA;
			for (uint32_t fff = 0; fff < y * 2 + 1; fff++) {
				ILI9341_SPI_Send(color >> 8);
				ILI9341_SPI_Send(color);
			}
			ILI9341_Set_Address(x0 - y, y0 - x, x0 + y, y0 - x);
			DC_COMMAND;
			ILI9341_SPI_Send(0x2C);
			DC_DATA;
			for (uint32_t fff = 0; fff < y * 2 + 1; fff++) {
				ILI9341_SPI_Send(color >> 8);
				ILI9341_SPI_Send(color);
			}
		}
	}
}

void LCD_ILI9341_Puts(unsigned int x, unsigned int y, char *str, unsigned char size, unsigned int color, unsigned int phone)
{
	switch (size)
	{
	case 1:
		while (*str)
		{
			if ((x+(size*8))>X_SIZE)
			{
				x = 1;
				y = y + (size*8);
			}
			ILI9341_Draw_Char(x, y, color, phone, *str, size);
			x += size*8-2;
			str++;
		}
	break;
	case 2:
		hh=1;
		while (*str)
		{
			if ((x+(size*8))>X_SIZE)
			{
				x = 1;
				y = y + (size*8);
			}
			ILI9341_Draw_Char(x,y,color,phone,*str,size);
			x += hh*8;
			str++;
		}
	break;
	}
}

void ILI9341_Draw_String_Transparent(unsigned int x, unsigned int y, char *str, unsigned char size, unsigned int color)
{
	while (*str)
	{
		if ((x + (size * 8)) > X_SIZE)
		{
			x = 1;
			y = y + (size * 8);
		}
		ILI9341_Draw_Char(x, y, color, 1, *str, size);
		x += (size == 1) ? size * 8 - 2 : 8;
		str++;
	}
}

static void ILI9341_Send_Command(unsigned char command) {
	Before_Sending_Command();
	ILI9341_SPI_Send(command);
}

static void ILI9341_Send_Data(unsigned char data) {
	Before_Sending_Data();
	ILI9341_SPI_Send(data);
}

static void ILI9341_Send_Burst(unsigned short color, unsigned long len) {
	uint8_t buffer[128];
	uint8_t high_bit = color >> 8;
	uint8_t low_bit = color;

	for (unsigned int i = 0; i < 64; i++)
	{
		buffer[2 * i] = high_bit;
		buffer[2 * i + 1] = low_bit;
	}

	CS_ON;
	DC_COMMAND;
	ILI9341_SPI_Send(0x2C);
	DC_DATA;

	while (len >= 64)
	{
		HAL_SPI_Transmit(&lcd_spi, buffer, sizeof(buffer), 100);
		len -= 64;
	}

	if (len > 0)
	{
		HAL_SPI_Transmit(&lcd_spi, buffer, (uint16_t)(len * 2), 100);
	}

	CS_OFF;
}

void ILI9341_Draw_Double_Pixel(int x, int y, unsigned int color1, unsigned int color2)
{
	if((x < 0) || (y < 0) || (x >= X_SIZE) || (y >= Y_SIZE))
	{
		return;
	}
	ILI9341_Set_Address(x, y, X_SIZE - 1, Y_SIZE - 1);
	DC_COMMAND;
	ILI9341_SPI_Send(0x2C);
	DC_DATA;
	ILI9341_SPI_Send(color1);
	ILI9341_SPI_Send(color2);
}
static void ILI9341_Draw_Char(int x, int y, unsigned int color, unsigned int phone, unsigned char charcode, unsigned char size)
{
	int i, h;
	unsigned int c;
 
	switch (size)
	{
	case 1:
	{
		uint8_t buf[6 * 8 * 2];
		uint16_t k = 0;
		for (h = 0; h < 8; h++)
		{
			for (i = 2; i < 8; i++)
			{
				c = ((chars8[charcode - 0x20][h] >> (7 - i)) & 0x01) ? color : phone;
				buf[k++] = c >> 8;
				buf[k++] = c;
			}
		}
		ILI9341_Set_Address(x, y, x + 5, y + 7);
		CS_ON;
		DC_COMMAND;
		ILI9341_SPI_Send(0x2C);
		DC_DATA;
		HAL_SPI_Transmit(&lcd_spi, buf, sizeof(buf), 100);
		CS_OFF;
		break;
	}
	case 2:
	{
		uint8_t buf[8 * 16 * 2];
		uint16_t k = 0;
		for (h = 0; h < 16; h++)
		{
			for (i = 0; i < 8; i++)
			{
				c = ((chars16[charcode - 0x20][h] >> (7 - i)) & 0x01) ? color : phone;
				buf[k++] = c >> 8;
				buf[k++] = c;
			}
		}
		ILI9341_Set_Address(x, y, x + 7, y + 15);
		DC_COMMAND;
		ILI9341_SPI_Send(0x2C);
		DC_DATA;
		HAL_SPI_Transmit(&lcd_spi, buf, sizeof(buf), 100);
		CS_OFF;
		break;
	}
	}
}


static void Before_Sending_Data() {
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
}

static void Before_Sending_Command() {
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
}

void ILI9341_Init(void) {
	LCD_ILI9341_Init();
}

void ILI9341_Set_Rotation(unsigned char rotation) {
	LCD_ILI9341_Rotate(rotation);
}

void ILI9341_Fill_Screen(unsigned int color) {
	LCD_ILI9341_Fill(color);
}

void ILI9341_Draw_Pixel(int x, int y, unsigned int color) {
	LCD_ILI9341_DrawPixel(x, y, color);
}

void ILI9341_Draw_Filled_Rectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color) {
	LCD_ILI9341_DrawFilledRectangle(x1, y1, x2, y2, color);
}

void ILI9341_Draw_Empty_Rectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color) {
	LCD_ILI9341_DrawRectangle(x1, y1, x2, y2, color);
}

void ILI9341_Draw_Line(unsigned int color, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
	LCD_ILI9341_DrawLine(x1, y1, x2, y2, color);
}

void ILI9341_Draw_Circle(unsigned int x0, unsigned int y0, int r, unsigned int color, unsigned char flood) {
	LCD_ILI9341_DrawCircle(x0, y0, r, color, flood);
}

void ILI9341_Draw_String(unsigned int x, unsigned int y, char *str, unsigned char size, unsigned int color, unsigned int phone) {
	LCD_ILI9341_Puts(x, y, str, size, color, phone);
}




//------------------------------------------------ TOUCH -----------------------------------------------------


//Enviar tres bytes: control, 0, 0 y recibir 0, dato1,dato2
//control       	S  A2 A1 A0 MODE SER PD1 PD0	descipcion
	//0xd1 = 				1	 1	0	 1  0	   0	 0	 1 		Xpos, 12 bits, diferencial, PENIRQ_disabled-REF_off-ADC_on 
	//0x91 = 				1	 0	0	 1  0	   0	 0	 1 		Ypos, 12 bits, diferencial, PENIRQ_disabled-REF_off-ADC_on  
	//0x90 = 				1	 0	0	 1  0	   0	 0	 0 		Ypos, 12 bits, diferencial, PENIRQ_enabled-Power_down  
	
	//0xB0 = 				1	 0	1	 1  0	   0	 0	 0 		Z1pos, 12 bits, diferencial, PENIRQ_disabled-REF_off-ADC_on  
	//0xC0 = 				1	 1	0	 0  0	   0	 0	 0 		Z2pos, 12 bits, diferencial, PENIRQ_disabled-REF_off-ADC_on  
	
  	
	//A2 A1 A0 descipcion de medicion
	//0  0  0	 temperatura
	//0  0  1  Ypos
	//0  1  0  VBat
	//0  1  1  Z1pos
	//1  0  0  Z2pos
	//1  0  1  Xpos
	//1  1  0  Aux in
	//1  1  1  Temperatura
	
	//MODE: 0=12 bits ADC, 1=8 bits ADC
	//SER:  0=diferencial ADC, 1=single ended ADC
	
	//PD1 PD0  descripcion
	// 0   0   PENIRQ' enabled , Power down between convertions
	// 0   1   PENIRQ' disabled, Reference is off and ADC is ON
	// 1   0   PENIRQ' enabled , Reference is on and ADC is off
	// 1   1   PENIRQ' disabled, Device is always powered
//***************************************** TOUCH **********************************************************
#define XPT2046_CS_SET				GPIOD->BSRR = 0x00000080
#define XPT2046_CS_RESET			GPIOD->BSRR = 0x00800000


uint8_t TP_GetState(void)
{
	uint16_t V1,V2;
	//Por presi�n Z
	V1=TP_ReadData(0xB0); //Z1
	V2=4096-TP_ReadData(0xC0);  //Z2
	V1=V1+V2;
	if(V1>=2100) return 1;
	/*
	//Por interrupcion (a veces tarda en desconectarse al dejar de tocar)
	TP_ReadData(0x90);
	HAL_Delay(500);
	*/
//	if((GPIOG->IDR & 0x00000200) != 0x00000200) return 1; //0000 0010 0000 0000 Si IRQ=0 (PG9)
//	if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_9) == GPIO_PIN_RESET) return 1; //Si IRQ=0 (PG9)
	return 0;
}

uint16_t TP_Read_X(void)		//Estan configurados para usarse en landscape 1
{
	int32_t V;
	int16_t MAX_X = 240;
	V=TP_ReadData(0xD1)-0;  //X (calibrar con minimo al minimo)
	V=(V*MAX_X)/1900;
	if(V<0) V=0;
	if(V>MAX_X-1) V=MAX_X-1;
  return V;
}
/*

*/

uint16_t TP_Read_Y(void)
{
	int32_t V;
	int16_t MAX_Y = 320;
	V=TP_ReadData(0x91)-100; //Y (calibrar con minimo al minimo)
	V=MAX_Y-(V*MAX_Y)/1750;
	if(V<0) V=0;
	if(V>MAX_Y-1) V=MAX_Y-1;
  return V;
}

uint16_t TP_Read_Z(void)
{
	uint16_t V1,V2;
	V1=TP_ReadData(0xB0); //Z1
	V2=4096-TP_ReadData(0xC0);  //Z2
	V1=V1+V2;
	return V1;
}	

uint16_t TP_ReadData(uint8_t control) 
{
	uint8_t rData[3] = {0, 0, 0};

	SPI3->CR1 = 0x00000364;
	XPT2046_CS_RESET;

	while ((SPI3->SR & SPI_SR_TXE) == 0U) {}
	SPI3->DR = control;
	while ((SPI3->SR & SPI_SR_RXNE) == 0U) {}
	(void)SPI3->DR;

	while ((SPI3->SR & SPI_SR_TXE) == 0U) {}
	SPI3->DR = 0x00;
	while ((SPI3->SR & SPI_SR_RXNE) == 0U) {}
	rData[1] = (uint8_t)SPI3->DR;

	while ((SPI3->SR & SPI_SR_TXE) == 0U) {}
	SPI3->DR = 0x00;
	while ((SPI3->SR & SPI_SR_RXNE) == 0U) {}
	rData[2] = (uint8_t)SPI3->DR;

	while ((SPI3->SR & SPI_SR_BSY) != 0U) {}
	XPT2046_CS_SET;
	SPI3->CR1 = 0x00000364;

	return (rData[1] << 4) | (rData[2] >> 4);
}