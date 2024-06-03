#include "Mixing.h"
#include "qswap.h"

// Funtction tested and works correctly
void LeftShift(unsigned char text[])
{
    // second row
    qSwap(text[1], text[13]);
    qSwap(text[1], text[9]);
    qSwap(text[1], text[5]);

    // third row
    qSwap(text[2], text[10]);
    qSwap(text[6], text[14]);

    // fourth row
    qSwap(text[3], text[7]);
    qSwap(text[3], text[11]);
    qSwap(text[3], text[15]);
}

// function tested and now works
void MixColumns(unsigned char text[])
{
    unsigned char matrixEl[4];
    matrixEl[0] = (2*text[0] + 3*text[1] + text[2] + text[3]);
    matrixEl[1] = (text[0] + 2*text[1] + 3*text[2] + text[3]);
    matrixEl[2] = (text[0] + text[1] + 2*text[2] + 3*text[3]);
    matrixEl[3] = (3*text[0] + text[1] + text[2] + 2*text[3]);

    text[0] = matrixEl[0];
    text[1] = matrixEl[1];
    text[2] = matrixEl[2];
    text[3] = matrixEl[3];

    matrixEl[0] = (2*text[4] + 3*text[5] + text[6] + text[7]);
    matrixEl[1] = (text[4] + 2*text[5] + 3*text[6] + text[7]);
    matrixEl[2] = (text[4] + text[5] + 2*text[6] + 3*text[7]);
    matrixEl[3] = (3*text[4] + text[5] + text[6] + 2*text[7]);

    text[4] = matrixEl[0];
    text[5] = matrixEl[1];
    text[6] = matrixEl[2];
    text[7] = matrixEl[3];
    matrixEl[0] = (2*text[8] + 3*text[9] + text[10] + text[11]);
    matrixEl[1] = (text[8] + 2*text[9] + 3*text[10] + text[11]);
    matrixEl[2] = (text[8] + text[9] + 2*text[10] + 3*text[11]);
    matrixEl[3] = (3*text[8] + text[9] + text[10] + 2*text[11]);

    text[8] = matrixEl[0];
    text[9] = matrixEl[1];
    text[10] = matrixEl[2];
    text[11] = matrixEl[3];

    matrixEl[0] = (2*text[12] + 3*text[13] + text[14] + text[15]);
    matrixEl[1] = (text[12] + 2*text[13] + 3*text[14] + text[15]);
    matrixEl[2] = (text[12] + text[13] + 2*text[14] + 3*text[15]);
    matrixEl[3] = (3*text[12] + text[13] + text[14] + 2*text[15]);

    text[12] = matrixEl[0];
    text[13] = matrixEl[1];
    text[14] = matrixEl[2];
    text[15] = matrixEl[3];
}

void AddRoundKey(unsigned char text[])
{
    return;
}
