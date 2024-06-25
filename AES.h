#ifndef AES_H
#define AES_H

#include <vector>
#include <iostream>
class Rijndael
{
private:

    // Primary Parameters
    std::string key;
    std::vector<unsigned char> blocks; // 16 byte blocks of input message

    // encryption
    void shiftRows();
    void mixColumns();
    void subbytes();
    void addRoundKey();

    // Round key managment
    void keySchedule();

public:
    Rijndael(std::string Input, std::string Key);
    void encrypt();
    void decrypt();
};

#endif // AES_H
