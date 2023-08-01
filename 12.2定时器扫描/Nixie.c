#include <Nixie.h>
#include <REGX52.H>

unsigned char numbers[9] = {0,10,10,10,10,10,10,10,10};
unsigned char Number[] = {0x3f,0x06,0x5b,0x4f,0x66,
0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x40}; //给P0赋的值,代表了0到9的10个数字


/**
  * @brief 设置数码管的显示值
  * @param 设置的位置(Location)和要显示的数字(num)
  * @retval 无
  */
void Nixie_setNum(unsigned char Location,num)
{
	numbers[Location] = num;
}

void Nixie(unsigned char Location, number){
	
	//通过给P2_4、P2_3、P2_2赋值来指定点亮的数码管
	//CBA指定点亮的数码管(Y0-Y7,最左为Y7)
	//case(1-8)为从左到右的第1到第8个数码管
	P0 = 0x00;
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


/**
  * @brief 扫描数码管并显示
  * @param 无
  * @retval 无
  */
void Nixie_scan(void)
{
	static unsigned char i = 0;
	
	i++;
	if(i>8){i=1;}
	Nixie(i,numbers[i]);
}


/*定时器扫描模板
void Timer0_Rountine(void) interrupt 1
{
	static unsigned int T0count = 0;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	
	T0count++;
	if(T0count == 2)
	{
		Nixie_scan();
		T0count = 0;
	}
}
*/