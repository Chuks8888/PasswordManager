#include "AES.h"

Rijndael::Rijndael(std::string Input, std::string Key)
{
    // need to convert the input into blocks of 16 bytes
    key = Key;
}
