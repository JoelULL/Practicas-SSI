#include "chacha20.h"

uint32_t swap_endian(uint32_t u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        uint32_t u;
        unsigned char u8[sizeof(uint32_t)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(uint32_t); k++)
        dest.u8[k] = source.u8[sizeof(uint32_t) - k - 1];

    return dest.u;
}


int main (void) {

    uint32_t tochacha [12];

    // test program

    // key
    tochacha[0] = 0x00010203;
    tochacha[1] = 0x04050607;
    tochacha[2] = 0x08090a0b;
    tochacha[3] = 0x0c0d0e0f;
    tochacha[4] = 0x10111213;
    tochacha[5] = 0x14151617;
    tochacha[6] = 0x18191a1b;
    tochacha[7] = 0x1c1d1e1f;
    //counter
    tochacha[8] = 0x01000000;
    //nonce
    tochacha[9] = 0x00000009;
    tochacha[10]= 0x0000004a;
    tochacha[11]= 0x00000000;

    for (int i = 0; i < 12; i++)
        tochacha[i] = swap_endian(tochacha[i]);

    ChaCha20 test (tochacha);

    test.ChaChaBlock();
    test.ShowResult();

    return 0;
}