#include <REGX52.H>
#include "Nixie.h"
#include "IR.h"
#include "Motor.h"

unsigned char Speed = 0,Command;

void main(void)
{
	IR_Init();
	Motor_Init();
	
	while(1)
	{
		if(IR_getDataFlag())
		{
			Command = IR_getCommand();
			switch(Command)
			{
				case IR_0:
					Speed = 0;
					break;
				case IR_1:
					Speed = 1;
					break;
				case IR_2:
					Speed = 2;
					break;
				case IR_3:
					Speed = 3;
					break;
			}
			Motor_setSpeed(Speed);
		}
		Nixie(1,Speed);
	}
}


