#include "GP2Y0A.h"

void GP2Y0A_Init()
{
    LQ_ADC_Init(GP2Y0A_1);
}


void GP2Y0A_Get()
{
    float res;
    uint8_t txt[20];
    res=1.0*5*ADC_Read(GP2Y0A_1)/4096;
    // sprintf(txt," %.2f ",res);
    // LCD_P6x8Str(0,1,txt);
}
