#include <REGX52.H>
#include "74HC595.h"

void main(void)
{
	_74HC595_Init();
	while(1)
	{
		LED_Write_column(0, 0x3c);
		LED_Write_column(1, 0x42);
		LED_Write_column(2, 0xa9);
		LED_Write_column(3, 0x85);
		LED_Write_column(4, 0x85);
		LED_Write_column(5, 0xa9);
		LED_Write_column(6, 0x42);
		LED_Write_column(7, 0x3c);
	}
}
