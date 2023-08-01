#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

void main(){
	//模块化使用
	LCD_Init();
	LCD_ShowString(1,1,"Hello World!");
	
	while(1){
		//读取矩阵键盘输入并显示在屏幕上
		unsigned char number = getKey();
		if(number != 0){
			LCD_ShowNum(2,1,number,2);
		}
	}
}
