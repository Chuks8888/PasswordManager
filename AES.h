#ifndef AES_H
#define AES_H

#include <vector>
#include <iostream>

class Rijndael
{
private:

    // Primary Parameters
    std::string key;
    std::vector<std::string> blocks;
    std::vector<std::string> roundKey;
    bool mode;

    // Algorithm methods
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
    void Use(std::string &Input, std::string Key, bool Mode); // Mode 1 - encrypt, 0 - decrypt
    //Rijndael(std::string &Input, std::string Key, bool Mode); // Mode 1 - encrypt, 0 - decrypt
    Rijndael();
    ~Rijndael();
};

#endif // AES_H
