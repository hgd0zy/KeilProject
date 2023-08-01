#ifndef __myLCD1602_H__
#define __myLCD1602_H__

void LCD_Init();
void LCD_ShowChar(unsigned char line,unsigned char column,unsigned char Char);
void LCD_ShowString(unsigned char line,unsigned char column,unsigned char string[]);
void LCD_ShowNum(unsigned char line,unsigned char column,unsigned int num,unsigned char length);
void LCD_ShowSignedNum(unsigned char line,unsigned char column,int num,unsigned char length);
void LCD_ShowHexNum(unsigned char line,unsigned char column,unsigned int num,unsigned char length);
void LCD_ShowBinNum(unsigned char line,unsigned char column,unsigned char num,unsigned char length);

#endif