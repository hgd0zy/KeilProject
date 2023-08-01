#include <REGX52.H>
#include "Delay.h"
#include "Uart.h"

void main(void)
{
	UartInit();
	while(1)
	{
		
	}
}

void UART_Routine(void) interrupt 4
{
	//只有在单片机接受数据时才执行
	if(RI == 1)
	{
		P2 = SBUF;//通过发送的数据控制灯的亮灭
		Uart_sendByte(SBUF);//返回单片机所接收到的数据
		RI = 0;
	}
}
