#include "AES.h"

Rijndael::Rijndael(std::string Input, std::string Key)
{
	int bit = 0; // from 0 to 16
    //unsigned char* temp = new unsigned char[16 + 1]; // allocating a block
    std::string temp = "";

	for(int j = 0; j < Input.size(); j++) // iterating through all characters
	{
		// assigning characters from the input to the 16 byte block
        //temp[bit] = Input[j];
        temp += Input[j];
		bit++;

		// when the temp is full
		if(bit%16 == 0 && bit != 0) 
		{
            //temp[16] = '\0'; // set last character to be null
            temp += "\0";
			blocks.push_back(temp); // push the block to the vector in the class 
            //temp = new unsigned char[16 + 1]; // assign a new pointer to the temp parameter
            temp = "";
			bit = 0; // reset the bit for the next block
		}
	}
    if(bit != 0 || !Input.size())
	{
		for(int j = bit; j < 16; j++)
		{
            temp += " ";
            //temp[j] = 32;
		}
        //temp[16] = '\0';
        temp += "\0";
        blocks.push_back(temp);
	}
    //temp = nullptr;

	key = Key;
    if(Key.size() < 16)
        for(int i = Key.size() - 1; i < 16; i++)
            Key[i] = 32;

    std::cout << "class created" << std::endl;
}

Rijndael::~Rijndael()
{
    /*for(auto& it : blocks)
    {
        delete[] it;
    }*/
    blocks.clear();
    std::cout << "class destroyed\n";
}

void Rijndael::printBlocks()
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

void Rijndael::testMixColumns()
{
    mixColumns();
}

void Rijndael::testShiftRows()
{
    shiftRows();
}
