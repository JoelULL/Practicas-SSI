#include <stdio.h>
#include "kasumi.h"


int main(void)
{
    int i;

    u8 key[16] = {
        0x99, 0x00, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 
    };
    u8 text[8]  = {
        0xFE, 0xDC, 0xBA, 0x09, 0x87, 0x65, 0x43, 0x21,
    };

    KeySchedule(key);
 
    printf("El texto original es: ");
    for (i = 0; i < 8; i++)
        printf("%02x ", text[i]);
    printf("\n");

    Kasumi(text);

    //printf("\n");
    printf("El texto encriptado es: ");
    for (i = 0; i < 8; i++)
        printf("%02x ", text[i]);
    printf("\n");

    decrypt(text);
    printf("El texto descifrado es: ");
    for (i = 0; i < 8; i++)
        printf("%02x ", text[i]);
    printf("\n");

    return 0;
}
