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

// galois field multpiplication
uint8_t gmul(uint8_t a, uint8_t b)
{
    uint8_t result = 0;
    for (int i = 0; i < 8; ++i) {
        if (b & 1) {
            result ^= a;
        }
        a = (a & 0x80) ? ((a << 1) ^ 0x1b) : (a << 1);
        b >>= 1;
    }
    return result;
}

// galios field multiplication for a single byte of a column
unsigned char rowgmul(std::string block, int column, unsigned char* mixmatrix, int row){
    return (
        gmul((unsigned char)block[column], mixmatrix[row]) ^
        gmul((unsigned char)block[1 + column], mixmatrix[row + 1]) ^
        gmul((unsigned char)block[2 + column], mixmatrix[row + 2]) ^
        gmul((unsigned char)block[3 + column], mixmatrix[row + 3]) );
}

unsigned char mixMatrix[16] = {
    0x02, 0x03, 0x01, 0x01,
    0x01, 0x02, 0x03, 0x01,
    0x01, 0x01, 0x02, 0x03,
    0x03, 0x01, 0x01, 0x02
};

unsigned char invMixMatrix[16] = {
    0x0e, 0x0b, 0x0d, 0x09,
    0x09, 0x0e, 0x0b, 0x0d,
    0x0d, 0x09, 0x0e, 0x0b,
    0x0b, 0x0d, 0x09, 0x0e
};

void Rijndael::mixColumns()
{
    unsigned char* matrix;
    if(mode)
        matrix = mixMatrix;
    else
        matrix = invMixMatrix;

    // temp array is one column
    unsigned char temp[4];

    // iterate through all blocks of 16 byte messages
    for(auto& block : blocks)
    {
        for(int i = 0; i < 4; i++) // 4 columns
        {
            // the 4 columns start with the numbers 0, 4, 8, 12 which is equal to i * 4
            int column = i * 4;

            // calculating each column cell
            for(int j = 0; j < 4; j++) // j represenst mix matrix row
                temp[j] = rowgmul(block, column, matrix, j * 4);

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

void Rijndael::invShiftRows()
{
    for(auto& block : blocks)
    {
        // Inverse shift fourth row by three
        qSwap(block[3], block[15]);
        qSwap(block[3], block[11]);
        qSwap(block[3], block[7]);

        // Inverse shift third row by two
        qSwap(block[2], block[10]);
        qSwap(block[6], block[14]);

        // Inverse shift second row by one
        qSwap(block[9], block[13]);
        qSwap(block[5], block[9]);
        qSwap(block[1], block[5]);
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

void Rijndael::invSubbytes()
{
    // iterate through all blocks of 16 byte messages
    for(auto& block : blocks)
    {
        // Put every byte of the block matrix (4x4 = 16) through the inverse S-box
        for(int i = 0; i < 16; i++)
            block[i] = invSbox[(unsigned char)block[i]];
    }
}

void Rijndael::addRoundKey(int round)
{
    std::string RoundKey = roundKey[round/2];
    for(auto& block : blocks)
    {
        int part = round%2 == 0 ? 0 : 16;
        // XOR the block with the current key, both have 128 bits i.e. 16 bytes
        for(int i = 0; i < 16; i++)
            block[i] ^= (unsigned char)RoundKey[i + part];
    }
}

// Sbox but for the key schedule word
void subWord(unsigned char word[])
{
    for(int i = 0; i < 4; i++)
        word[i] = Sbox[(unsigned char)word[i]];
}

// Rcon values for the key schedule
unsigned char Rconval[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

// Create round keys
void Rijndael::keyschedule()
{
    for(int i = 0; i < 7; i++)
    {
        // temporary represents the g function
        unsigned char temporary[4];

        // assign g function
        for(int i = 0; i < 3; i++)
            temporary[i] = key[29+i];
        temporary[3] = key[28];
        subWord(temporary);
        temporary[0] ^= Rconval[i];

        // Then xor the words based on the
        // AES key expansion for 256 bit keys
        for(int i = 0; i < 16; i++)
        {
            key[i] ^= temporary[i&3];
            temporary[i&3] = key[i];
        }
        subWord(temporary);
        for(int i = 16; i < 32; i++)
        {
            key[i] ^= temporary[i&3];
            temporary[i&3] = key[i];
        }
        roundKey.push_back(key);
    }
}
