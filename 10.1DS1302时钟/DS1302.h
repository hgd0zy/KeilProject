#ifndef __DS1302_H__
#define __DS1302_H__

#define DS1302_Sec (0x80)
#define DS1302_Min (0x82)
#define DS1302_Hour (0x84)
#define DS1302_Date (0x86)
#define DS1302_Mon (0x88)
#define DS1302_Year (0x8C)
#define DS1302_WP (0x8E)

extern unsigned char DS1302_time[];

void DS1302_Init(void);
void DS1302_Write(unsigned char Command, Data);
unsigned char DS1302_Read(unsigned char Command);
void DS1302_setTime(void);
void DS1302_readTime(void);

#endif