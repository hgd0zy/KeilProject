#include <REGX52.H>
#include "Delay.h"

/**
  * @brief 用来判别按键按下的信号
  * @param 无
  * @retval 按键标号（0-4）,无按键按下时为0
  */
unsigned char getKey(void)
{
	unsigned char Key_number = 0;
	if(P3_1 == 0){
		Delay(20);while(P3_1 == 0);Delay(20);
		Key_number = 1;
	}else if(P3_0 == 0){
		Delay(20);while(P3_0 == 0);Delay(20);
		Key_number = 2;
	}else if(P3_2 == 0){
		Delay(20);while(P3_2 == 0);Delay(20);
		Key_number = 3;
	}else if(P3_3 == 0){
		Delay(20);while(P3_3 == 0);Delay(20);
		Key_number = 4;
	}
	return Key_number;
}
