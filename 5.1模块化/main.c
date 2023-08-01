#include <Delay.h>
#include <REGX52.H>
#include <Nixie.h>

//使用模块化操作，
//将函数的声明和实现放到其它文件中去
void main(){
	while(1){
		
		Nixie(1,1);
		Delay(5);//延时5ms，防止闪烁太快看不出来
		Nixie(2,5);
		Delay(5);
		Nixie(3,5);
		Delay(5);
		Nixie(4,7);
		Delay(5);
		
	}
}
