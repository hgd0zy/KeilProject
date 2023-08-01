#include <REGX52.H>
#include "LCD1602.h"
#include "MatrixKey.h"

void main(){
	//初始化密码
	const int __password__ = 1470;
	long int password = 0;
	unsigned char number = 0;
	unsigned char len = 0;
	unsigned char enter = 0;
	
	//模块化使用
	LCD_Init();
	LCD_ShowString(1,1,"PassWord:");
	
	while(1){
		//读取矩阵键盘输入
		number = getKey();
		if(number != -1){
			//处理按下确定的情况
			if(11 == number) {enter = 1;}
			//处理按下退格的情况
			if(12 == number) {len = (len<=0)?0:len-1;password = password/10;}
			//处理按下第四行按键的请况
			if(number > 12);
			//其它情况
			if(number <= 10){
				password = password*10 +number;
				len++;
				//超出4位则归0
				if(len > 4){
					password = password%10;
					len = 1;
				}
			}
		}
		if(1 == enter){
			//判断密码是否正确
			if(password == __password__){
				LCD_ShowString(1,14," OK");
			}else {
				LCD_ShowString(1,14,"ERR");
			}
			enter = 0;
		}
		//已经输入的数字的显示
		LCD_ShowNum(2,1,password,4);
	}
}
