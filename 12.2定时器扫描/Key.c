#include <REGX52.H>

static unsigned char resultKey = 0,temp;//用来返回的key

/**
  * @brief 返回按下的按键标号
  * @param 无
  * @retval 按下的按键标号
  */
unsigned char Key(void)
{
	temp = resultKey;
	resultKey = 0;
	return temp;
}

/**
  * @brief 用来判别按键按下的信号
  * @param 无
  * @retval 按键标号（0-4）,无按键按下时为0
  */
unsigned char getKey(void)
{
	unsigned char Key_number = 0;
	if(P3_1 == 0){
		Key_number = 1;
	}else if(P3_0 == 0){
		Key_number = 2;
	}else if(P3_2 == 0){
		Key_number = 3;
	}else if(P3_3 == 0){
		Key_number = 4;
	}
	return Key_number;
}


/**
  * @brief 扫描key按下的下降沿
  * @param 无
  * @retval 无
  */
void Key_scan(void)
{
	static unsigned char nowkey,lastkey = 0;
	nowkey = getKey();
	if(lastkey == 1 && nowkey == 0){resultKey = 1;}
	if(lastkey == 2 && nowkey == 0){resultKey = 2;}
	if(lastkey == 3 && nowkey == 0){resultKey = 3;}
	if(lastkey == 4 && nowkey == 0){resultKey = 4;}
	lastkey = nowkey;
}


/*定时器扫描模板
void Timer0_Rountine(void) interrupt 1
{
	static unsigned int T0count = 0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	
	T0count++;
	if(T0count == 20)//控制执行次数，每次1ms
	{
		Key_scan();
		T0count = 0;
	}
}
*/