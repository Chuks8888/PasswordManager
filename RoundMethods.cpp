#include "AES.h"
#include "Tables.h"
#include "qswap.h"

void Rijndael::mixColumns()
{
    // multiply each column of a single block by the matrix:
    // [ 2, 3, 1, 1 ]
    // | 1, 2, 3, 1 |
    // | 1, 1, 2, 3 |
    // [ 3, 1, 1, 2 ]
    unsigned char temp[4];
    for(auto& block : blocks)
    {
        for(int i = 0; i < 4; i++) // 4 columns - 4 iterations
        {
            int column = i * 4; // since a block has 16 elements, we need to iterate through each column by adding 4 * i
            temp[0] = multiply2[(int)block[0 + column]] ^ multiply3[(int)block[1 + column]] ^ block[2 + column] ^ block[3 + column];
            temp[1] = block[0 + column] ^ multiply2[(int)block[1 + column]] ^ multiply3[(int)block[2 + column]] ^ block[3 + column];
            temp[2] = block[0 + column] ^ block[1 + column] ^ multiply2[(int)block[2 + column]] ^ multiply3[(int)block[3 + column]];
            temp[3] = multiply3[(int)block[0 + column]] ^ block[1 + column] ^ block[2 + column] ^ multiply2[(int)block[3 + column]];

            // assign calculated values to the column of the block
            for(int j = 0; j < 4; j++)
                block[j] = temp[j];
        }
    }
}

void Rijndael::shiftRows()
{
    for(auto& block : blocks)
    {
        // Shift second row by one
        qSwap(block[1], block[5]);
        qSwap(block[5], block[9]);
        qSwap(block[9], block[13]);

        // Shift third row by two
        qSwap(block[2], block[10]);
        qSwap(block[6], block[14]);

        // Shift fourth row by three
        qSwap(block[12], block[13]);
        qSwap(block[12], block[14]);
        qSwap(block[12], block[15]);
    }
}

void Rijndael::subbytes()
{
    for(auto& block : blocks)
    {
        // Put every byte of the block matrix (4x4 = 16) through the S-box
        for(int i = 0; i < 16; i++)
            block[i] = Sbox[(int)block[i]];
    }
}

void Rijndael::addRoundKey()
{
    for(auto& block : blocks)
    {
        // XOR the block with the current key, both have 128 bits i.e. 16 bytes
        for(int i = 0; i < 16; i++)
            block[i] ^= key[i];
    }
}
