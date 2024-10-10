#include "rijndael.h"

Rijndael::Rijndael(){
    std::cout << "class created" << std::endl;
}

void Rijndael::Use(std::string &Input, std::string Key, bool Mode)
{
    key = Key;
    Key = "";
    mode = Mode;

    // Input the message into blocks of 16 byte strings
    int bit = 0;
    std::string temp = "";
    for(int j = 0; j < Input.size(); j++)
    {
        temp += Input[j];
        bit++;

        // when the temp is full
        if(bit&16)
        {
            temp += "\0";
            blocks.push_back(temp);
            temp = "";
            bit = 0;
        }
    }
    // Zero the original message
    Input = "";

    // If the input does not reach 16 bytes, then fill the rest with whitespace char
    if(bit != 0)
    {
        for(int j = bit; j < 16; j++)
            temp += ' ';
        temp += "\0";
        blocks.push_back(temp);
        temp = "";
    }

    // Create round Keys
    roundKey.push_back(key);
    keyschedule();
    key = "";
    // which method
    if(mode)
        encrypt();
    else
        decrypt();

    roundKey.clear();

    // Fill the Input with the new text
    for(const auto& block : blocks)
        Input += block;
    blocks.clear();
}

Rijndael::~Rijndael()
{
    std::cout << "class destroyed" << std::endl;
}

void Rijndael::encrypt()
{
    // Pre round transformation
    addRoundKey(0);

    // 13 rounds
    for(int i = 1; i < 14; i++)
    {
        subbytes();
        shiftRows();
        mixColumns();
        addRoundKey(i);
    }

    // Last Round without mix Columns
    subbytes();
    shiftRows();
    addRoundKey(14);
}

// Reverse the encryption
// All steps are the same as in
// encrypt() but reverse
void Rijndael::decrypt()
{
    addRoundKey(14);
    invShiftRows();
    invSubbytes();

    for(int i = 13; i > 0; i--)
    {
        addRoundKey(i);
        mixColumns();
        invShiftRows();
        invSubbytes();
    }

    addRoundKey(0);
}
