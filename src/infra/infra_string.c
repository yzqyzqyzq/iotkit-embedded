#ifdef INFRA_STRING
#include "infra_string.h"

int8_t infra_hex2char(uint8_t hex)
{
    hex = hex & 0xF;
    return (int8_t)(hex < 10 ? '0' + hex : hex - 10 + 'a');
}

void infra_hex2str(uint8_t *input, uint16_t input_len, char *output)
{
    char *zEncode = "0123456789ABCDEF";
    int i = 0, j = 0;

    for (i = 0; i < input_len; i++) {
        output[j++] = zEncode[(input[i] >> 4) & 0xf];
        output[j++] = zEncode[(input[i]) & 0xf];
    }
}

void infra_int2str(uint32_t input, char output[10])
{
    uint8_t i = 0, j = 0;
    char tmp[10] = {0};

    do {
        tmp[i++] = input%10 + '0';
    }while((input/=10)>0);

    do {
        output[--i] = tmp[j++];
    }while(i > 0);
}

#endif

#ifdef INFRA_RANDOM

uint64_t HAL_UptimeMs(void);
void HAL_Srandom(uint32_t seed);
uint32_t HAL_Random(uint32_t region);

int infra_randstr(char *random, int length)
{
    int index = 0;

    HAL_Srandom(HAL_UptimeMs());

    for (index = 0; index < length; index++) {
        switch (HAL_Random(3)) {
            case 0: {
                random[index] = 'A' + HAL_Random(26);
            }
            break;
            case 1: {
                random[index]  = 'a' + HAL_Random(26);
            }
            break;
            case 2: {
                random[index] = '0' + HAL_Random(10);
            }
            break;
            default: {
                return -1;
            }
        }
    }

    return 0;
}
#endif