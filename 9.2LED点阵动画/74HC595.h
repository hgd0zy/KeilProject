#ifndef __74HC595_H__
#define __74HC595_H__

void _74HC595_Init(void);
void _74HC595_Write(unsigned char byte);
void LED_Show_column(unsigned char column, Data);

#endif