#include <REGX52.H>
#include "INT0.h"
#include "Timer0.h"

//状态转移标志与时间间隔
unsigned char IR_State = 0;
unsigned int IR_Time;

//短暂接收数据
unsigned char IR_Data[4];
unsigned char IR_pData = 0;

//重发标志，数据标志，命令，地址码
unsigned char IR_DataFlag = 0;
unsigned char IR_RepeatFlag = 0;
unsigned char IR_Command;
unsigned char IR_Address;

/**
  * @brief 初始化红外接收模块
  * @param 无
  * @retval 无
  */
void IR_Init(void)
{
	Int0_Init();
	Timer0Init();
}

/**
  * @brief 返回重发标志，数据标志，命令，地址码
  * @param 无
  * @retval 重发标志或数据标志或命令或地址码
  */
unsigned char IR_getRepeatFlag(void)
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_getDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_getCommand(void)
{
	return IR_Command;
}

unsigned char IR_getAddress(void)
{
	return IR_Address;
}

/**
  * @brief 外部中断触发
  * @param 无
  * @retval 无
  */
void Int0_Routine(void) interrupt 0
{
	if(IR_State == 0)//状态0，用来开始接收
	{
		Timer0_setCount(0);
		Timer0_run(1);
		IR_State = 1;
	}
	else if(IR_State == 1)//状态1，用来接收开始标志和重发标志
	{
		IR_Time = Timer0_getCount();
		
		if((IR_Time > 12442 - 500) && (IR_Time < 12442 + 500))
		{
			//开始标志
			IR_State = 2;
			Timer0_setCount(0);
		}
		else if((IR_Time > 10368 - 500) && (IR_Time < 10368 + 500))
		{
			//重发标志
			IR_RepeatFlag = 1;
			IR_State = 0;
			Timer0_run(0);
			Timer0_setCount(0);
		}
		else 
		{
			//意外情况
			IR_State = 0;
			Timer0_run(0);
		}
	}
	else if(IR_State == 2)//状态2，用来解码数据
	{
		IR_Time = Timer0_getCount();
		Timer0_setCount(0);
		
		if((IR_Time > 1032-500) && (IR_Time < 1032+500))
		{
			//数据0
			IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));
			IR_pData++;
		}
		else if((IR_Time > 2074-500) && (IR_Time < 2074+500))
		{
			//数据1
			IR_Data[IR_pData/8] |= (0x01<<(IR_pData%8));
			IR_pData++;
		}
		else {
			IR_pData = 0;
			IR_State = 1;
		}
		if(IR_pData >= 32)//控制数据接收
		{
			IR_pData = 0;
			if((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3]))
			{
				IR_Address = IR_Data[0];
				IR_Command = IR_Data[2];
				IR_DataFlag = 1;
			}
			Timer0_run(0);
			IR_State = 0;
		}
	}
}
