#include <REGX52.H>
#include "Nixie.h"
#include "Key.h"
#include "Buzzer.h"

void Timer0Init(void);

void main(void)
{
	unsigned char Key;
	Nixie(1,0);
	while(1)
	{
		Key = getKey();
		if(Key)
		{
			Nixie(1,Key);
			Buzzer_time(1000);
		}
	}
}

