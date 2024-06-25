#ifndef AES_H
#define AES_H
#include <QMatrix4x4>
#include <iostream>
class Rijndael
{
private:
    std::string Message; // what we want to encrypt/decrypt (will change)
    std::string Key; // will also be changed throught the encryption process

    // encryption
    void ShiftRows();
    void MixColumns();
    void Subbytes();
    void AddRoundKey();
    void KeySchedule();

public:
    Rijndael(std::string Input, std::string Key);
    void encrypt();
    void decrypt();
};

#endif // AES_H
