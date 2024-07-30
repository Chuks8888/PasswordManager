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
    std::string roundKey;

    bool finished;

    // encryption
    void shiftRows();
    void mixColumns();
    void subbytes();
    void addRoundKey();

    // Round key managment
    void keySchedule();
    void keyschedule(int round);

public:
    Rijndael(std::string Input, std::string Key);
	~Rijndael();
    void encrypt();
    std::string getmessage();
};

#endif // AES_H
