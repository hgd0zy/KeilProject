#include <REGX52.H>


/**
* @brief 外部中断初始化
  * @param 无
  * @retval 无
  */
void Int0_Init(void)
{
	IT0 = 1;
	IE0 = 0;
	EX0 = 1;
	EA = 1;
	PX0 = 1;
}
	


/**
  * @brief 中断调用模板
  * @param 无
  * @retval 无
  */
/*
void Int0_Routine(void) interrupt 0
{
	
}
*/
