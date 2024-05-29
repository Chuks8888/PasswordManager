#include "Mixing.h"
#include "qswap.h"

// Funtction tested and works correctly
void LeftShift(unsigned char text[])
{
    // second row
    qSwap(text[4], text[7]);
    qSwap(text[4], text[6]);
    qSwap(text[4], text[5]);

    // third row
    qSwap(text[8], text[10]);
    qSwap(text[9], text[11]);

    // fourth row
    qSwap(text[12], text[13]);
    qSwap(text[12], text[14]);
    qSwap(text[12], text[15]);
}

void RightShift(unsigned char text[])
{
    return;
}

void MixColumns(unsigned char text[])
{
    return;
}

void AddRoundKey(int noKey, unsigned char text[])
{
    return;
}
