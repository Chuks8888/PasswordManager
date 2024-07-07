#include "AES.h"
#include "Tables.h"
#include "qswap.h"

// Method confirmed to work
void Rijndael::mixColumns()
{
    // multiply each column of a single block by the matrix:
    // [ 2, 3, 1, 1 ]
    // | 1, 2, 3, 1 |
    // | 1, 1, 2, 3 |
    // [ 3, 1, 1, 2 ]
    unsigned char temp[4];

    // blocks is the private parameter of the Rijndael class that holds the message
    for(auto& block : blocks)
    {
        for(int i = 0; i < 4; i++) // 4 columns - 4 iterations
        {
            int column = i * 4; // since a block has 16 elements, we need to iterate through each column by adding 4 * i
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

// Method confirmed to work
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
        qSwap(block[3], block[7]);
        qSwap(block[3], block[11]);
        qSwap(block[3], block[15]);
    }
}


void Rijndael::subbytes()
{
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
            block[i] ^= (unsigned char)key[i];
    }
}

std::vector<unsigned char>RconVal = {0x36, 0x1b, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

void Rijndael::keySchedule()
{
	unsigned char temporary[4];
    // Take the fourth word of the key and shift it once to the left
    // Also put the characters through Sbox
	for(int i = 0; i < 3; i++)
        temporary[i] = Sbox[(unsigned char)key[13+i]];
    temporary[3] = Sbox[(unsigned char)key[12]];

    // Then xor the first char with the Rcon Value
    temporary[0] ^= RconVal.back();
	RconVal.pop_back();

    // Now do the key schedule by xoring the previous key words
    // For further info check this link:
    // https://braincoke.fr/blog/2020/08/the-aes-key-schedule-explained/#aes-key-schedule
    for(int i = 0; i < 16; i++)
	{
        key[i] ^= temporary[i&3];
        temporary[i&3] = key[i];
    }
}
