#include <REGX52.H>
#include "Delay.h"
#include "Uart.h"


void main(void){
	unsigned char sec = 0;
	UartInit();
	while(1)
	{
		Uart_sendByte(sec++);
		Delay(1000);
	}
}
