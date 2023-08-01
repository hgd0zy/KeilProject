#include <Nixie.h>
#include <REGX52.H>

unsigned char Number[] = {0x3f,0x06,0x5b,0x4f,0x66,
0x6d,0x7d,0x07,0x7f,0x6f,0x3f}; //给P0赋的值,代表了0到9的10个数字


void Nixie(unsigned char Location, number){
	
		//通过给P2_4、P2_3、P2_2赋值来指定点亮的数码管
	//CBA指定点亮的数码管(Y0-Y7,最左为Y7)
	//case(1-8)为从左到右的第1到第8个数码管
	switch(Location){
		case 1:
			P2_4 = 1;// C = 1
			P2_3 = 1;// B = 1
			P2_2 = 1;// A = 1
			break;
		case 2:
			P2_4 = 1;P2_3 = 1;P2_2 = 0;//CBA = 110
			break;
		case 3:
			P2_4 = 1;P2_3 = 0;P2_2 = 1;//CBA = 101
			break;
		case 4:
			P2_4 = 1;P2_3 = 0;P2_2 = 0;//CBA = 100
			break;
		case 5:
			P2_4 = 0;P2_3 = 1;P2_2 = 1;//CBA = 011
			break;
		case 6:
			P2_4 = 0;P2_3 = 1;P2_2 = 0;//CBA = 010
			break;
		case 7:
			P2_4 = 0;P2_3 = 0;P2_2 = 1;//CBA = 001
			break;
		case 8:
			P2_4 = 0;P2_3 = 0;P2_2 = 0;//CBA = 000
			break;
	}
	//给P0指定值来显示数字
	P0 = Number[number];
}