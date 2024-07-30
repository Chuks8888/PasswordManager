#include "AES.h"

Rijndael::Rijndael(std::string Input, std::string Key)
{
    finished = false;
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
    roundKey = Key;
    if(Key.size() < 32)
        for(int i = Key.size() - 1; i < 32; i++)
            Key[i] = 32;

    encrypt();
    finished = 1;
    for(auto& block : blocks)
        for(int i = 0; i < 16; i++)
            printf("%X ", (unsigned char)block[i]);
    std::cerr << "text encrypted" << std::endl;
}
Rijndael::~Rijndael()
{
    blocks.clear();
    std::cout << "class destroyed\n";
}

void Rijndael::encrypt()
{
    // Pre round transformation
    addRoundKey();
    keyschedule(0);

    // 13 rounds
    for(int i = 1; i < 14; i++)
    {
        subbytes();
        shiftRows();
        mixColumns();
        addRoundKey();
        keyschedule(i);
    }

    // Last Round without mix Columns
    subbytes();
    shiftRows();
    addRoundKey();

}

std::string Rijndael::getmessage()
{
    if(finished)
    {
        std::string message;
        for(const auto& it : blocks)
        {
            message += it;
        }
        return message;
    }
    return " ";
}
