#ifndef __DS18B20_H__
#define __DS18B20_H__

#define SKIP_ROM 0xCC
#define CONVERT_T 0x44
#define READ_SCRATCHPAD 0xBE

void DS18B20_ConvertT(void);
float DS18B20_readT(void);

#endif