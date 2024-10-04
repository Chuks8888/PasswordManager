#include "randomGenerator.h"

#include<windows.h>
#include<wincrypt.h>

std::string randomkey()
{
    int length = 32;
    unsigned char buffer[33];
    HCRYPTPROV hProv;
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        throw std::runtime_error("CryptAcquireContext failed");
    }
    if (!CryptGenRandom(hProv, length, buffer)) {
        CryptReleaseContext(hProv, 0);
        throw std::runtime_error("CryptGenRandom failed");
    }
    CryptReleaseContext(hProv, 0);

    std::string val = "";
    for (int i = 0; i < 32; i++)
        val += buffer[i];
    return val;
}
