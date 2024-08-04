#ifndef AES_H
#define AES_H

#include <vector>
#include <iostream>

class Rijndael
{
private:

    // Primary Parameters
    std::string key;
    std::vector<std::string> blocks; // 16 byte blocks of input message
    std::vector<std::string> roundKey;

    bool finished;
    bool mode;

    // encryption
    void shiftRows();
    void invShiftRows();
    void mixColumns();
    void subbytes();
    void invSubbytes();
    void addRoundKey(int round);

    // Round key creation
    void keyschedule();

    // Mode
    void encrypt();
    void decrypt();

public:
    Rijndael(std::string Input, std::string Key, bool Mode);
	~Rijndael();
    std::string getmessage();
};

#endif // AES_H
