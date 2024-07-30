#include "AES.h"
#include "Tables.h"
#include "qswap.h"

/*/
 * This source file contains all the functions
 * used in the AES encryption rounds
 * Each block of message is contained within
 * a 16 byte string o unsigned char values
 * The order of bytes in the message
 * is like this:
 * [ 0 4 8  12 ]
 * | 1 5 9  13 |
 * | 2 6 10 14 |
 * [ 3 7 11 15 ]
/*/

void Rijndael::mixColumns()
{
    // multiply the message by this matrix:
    // [ 2 3 1 1 ]
    // | 1 2 3 1 |
    // | 1 1 2 3 |
    // [ 3 1 1 2 ]

    // temp array is one column
    unsigned char temp[4];

    // iterate through all blocks of 16 byte messages
    for(auto& block : blocks)
    {
        for(int i = 0; i < 4; i++) // 4 columns
        {
            // the 4 columns start with the numbers 0, 4, 8, 12 which is equal to i * 4
            int column = i * 4;
            temp[0] = multiply2[(unsigned char)block[0 + column]] ^ multiply3[(unsigned char)block[1 + column]] ^ block[2 + column] ^ block[3 + column];
            temp[1] = block[0 + column] ^ multiply2[(unsigned char)block[1 + column]] ^ multiply3[(unsigned char)block[2 + column]] ^ block[3 + column];
            temp[2] = block[0 + column] ^ block[1 + column] ^ multiply2[(unsigned char)block[2 + column]] ^ multiply3[(unsigned char)block[3 + column]];
            temp[3] = multiply3[(unsigned char)block[0 + column]] ^ block[1 + column] ^ block[2 + column] ^ multiply2[(unsigned char)block[3 + column]];

            // assign calculated values to the column of the block
            for(int j = 0; j < 4; j++)
                block[j + column] = temp[j];
        }
    }
}

void Rijndael::shiftRows()
{
    // iterate through all blocks of 16 byte messages
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
        qSwap(block[3], block[7]);
        qSwap(block[3], block[11]);
        qSwap(block[3], block[15]);
    }
}

void Rijndael::subbytes()
{
    // iterate through all blocks of 16 byte messages
    for(auto& block : blocks)
    {
        // Put every byte of the block matrix (4x4 = 16) through the S-box
        for(int i = 0; i < 16; i++)
            block[i] = Sbox[(unsigned char)block[i]];
    }
}

void Rijndael::addRoundKey()
{
    for(auto& block : blocks)
    {
        // XOR the block with the current key, both have 128 bits i.e. 16 bytes
        for(int i = 0; i < 16; i++)
        {
            block[i] ^= (unsigned char)roundKey[i];
        }
    }
}

// Sbox but for the key schedule word
void subWord(unsigned char word[])
{
    for(int i = 0; i < 4; i++)
    {
        word[i] = Sbox[(unsigned char)word[i]];
    }
}

// Rcon values for the key schedule
unsigned char Rconval[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

/*/
 * Key schedule is triggered every round
 * depending on the round, the function
 * either creates a set of two new round keys
 * or simply assigns the second key that was
 * generated the previous round
/*/
void Rijndael::keyschedule(int round)
{
    // Reset the round key
    roundKey = "";

    if(round%2 == 0)
        // assign the second part of the previousl created key
        for(int i = 16; i < 32; i++)
            roundKey += key[i];
    else {
        // Else create a set of two new keys
        // temporary represents the g function
        unsigned char temporary[4];

        // Shift the word by one to left
        // then apply sbox and xor the
        // first value with the Rconval
        for(int i = 0; i < 3; i++)
            temporary[i] = key[29+i];
        temporary[3] = key[28];
        subWord(temporary);
        temporary[0] ^= Rconval[round/2];

        // Then xor the words based on the
        // AES key expansion for 256 bit keys
        for(int i = 0; i < 16; i++)
        {
            roundKey += (key[i] ^= temporary[i&3]);
            temporary[i&3] = key[i];
        }
        subWord(temporary);
        for(int i = 16; i < 32; i++)
        {
            key[i] ^= temporary[i&3];
            temporary[i&3] = key[i];
        }
    }
}
