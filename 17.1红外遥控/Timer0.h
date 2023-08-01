#ifndef __Timer0_H__
#define __Timer0_H__

void Timer0Init(void);
void Timer0_setCount(unsigned int value);
void Timer0_run(unsigned char run);
unsigned int Timer0_getCount(void);

#endif