#include <REGX52.H>
#include <LCD1602.h>

void main(){
	//目前不知道lcd的使用，
	//这里使用的是已经封装好的函数
	LCD_Init();
	
	while(1){
		LCD_ShowString(2,1,"");
	}
}
