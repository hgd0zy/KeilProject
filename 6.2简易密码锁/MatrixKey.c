#include <REGX52.H>
#include "MatrixKey.h"
#include "Delay.h"

unsigned char getKey(void){
	//返回值
	unsigned char key_number = -1;
	
	//判断第一列
	P1 = 0xff;
	P1_3 = 0;
	if(0 == P1_7){
		Delay(20);while(0 == P1_7);Delay(20);
		key_number = 1;
	}else if(0 == P1_6){
		Delay(20);while(0 == P1_6);Delay(20);
		key_number = 5;
	}else if(0 == P1_5){
		Delay(20);while(0 == P1_5);Delay(20);
		key_number = 9;
	}else if(0 == P1_4){
		Delay(20);while(0 == P1_4);Delay(20);
		key_number = 13;
	}
	
	//判断第二列
	P1 = 0xff;
	P1_2 = 0;
	if(0 == P1_7){
		Delay(20);while(0 == P1_7);Delay(20);
		key_number = 2;
	}else if(0 == P1_6){
		Delay(20);while(0 == P1_6);Delay(20);
		key_number = 6;
	}else if(0 == P1_5){
		Delay(20);while(0 == P1_5);Delay(20);
		key_number = 0;
	}else if(0 == P1_4){
		Delay(20);while(0 == P1_4);Delay(20);
		key_number = 14;
	}
	
	//判断第三列
	P1 = 0xff;
	P1_1 = 0;
	if(0 == P1_7){
		Delay(20);while(0 == P1_7);Delay(20);
		key_number = 3;
	}else if(0 == P1_6){
		Delay(20);while(0 == P1_6);Delay(20);
		key_number = 7;
	}else if(0 == P1_5){
		Delay(20);while(0 == P1_5);Delay(20);
		key_number = 11;
	}else if(0 == P1_4){
		Delay(20);while(0 == P1_4);Delay(20);
		key_number = 15;
	}
	
	//判断第四列
	P1 = 0xff;
	P1_0 = 0;
	if(0 == P1_7){
		Delay(20);while(0 == P1_7);Delay(20);
		key_number = 4;
	}else if(0 == P1_6){
		Delay(20);while(0 == P1_6);Delay(20);
		key_number = 8;
	}else if(0 == P1_5){
		Delay(20);while(0 == P1_5);Delay(20);
		key_number = 12;
	}else if(0 == P1_4){
		Delay(20);while(0 == P1_4);Delay(20);
		key_number = 16;
	}
	
	return key_number;
}

