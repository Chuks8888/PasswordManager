#include "AES.h"

Rijndael::Rijndael(std::string Input, std::string Key)
{
	int bit = 0; // from 0 to 16
    std::string temp = ""; // new block

	for(int j = 0; j < Input.size(); j++) // iterating through all characters
	{
		// assigning characters from the input to the 16 byte block
        temp += Input[j];
		bit++;

		// when the temp is full
		if(bit%16 == 0 && bit != 0) 
		{
            temp += "\0";
            blocks.push_back(temp); // push the block to the vector in the class
            temp = ""; // reset the block for futher input
			bit = 0; // reset the bit for the next block
		}
	}
    // If the input does not reach 16 bytes, then fill the rest with whitespace char
    if(bit != 0 || !Input.size())
	{
		for(int j = bit; j < 16; j++)
            temp += " ";
        temp += "\0";
        blocks.push_back(temp);
	}

    // Fill the key
	key = Key;
    if(Key.size() < 16)
        for(int i = Key.size() - 1; i < 16; i++)
            Key[i] = 32;

    std::cout << "class created" << std::endl;
}

Rijndael::~Rijndael()
{
    blocks.clear();
    std::cout << "class destroyed\n";
}

void Rijndael::printBlocks() const
{
    for(const auto& it : blocks)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int i = j; i <= (16 - 4 + j); i+=4)
                printf("%X ", (unsigned char)it[i]);
            std::cout << std::endl;
        }
    }
}

void Rijndael::encrypt()
{
    // Pre round transformation
    addRoundKey();
    keySchedule();

    // 9 rounds
    for(int i = 0; i < 9; i++)
    {
        subbytes();
        shiftRows();
        mixColumns();
        addRoundKey();
        keySchedule();
    }

    // Last Round without mix Columns
    subbytes();
    shiftRows();
    addRoundKey();
}
