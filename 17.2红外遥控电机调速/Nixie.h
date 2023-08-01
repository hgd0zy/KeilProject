#include <REGX52.H>

#ifndef __Nixie_H__
#define __Nixie_H__

//在指定位置显示数字number
void Nixie(unsigned char Location, char number);
extern unsigned char Number[];//声明给P0的0-9的10个数字

#endif