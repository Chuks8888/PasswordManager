#include "randomGenerator.h"

#ifdef _WIN32 // for Windows
#include<windows.h>
#include<wincrypt.h>

void randomString(unsigned char* buffer, std::size_t length)
{
    HCRYPTPROV hProv;
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        throw std::runtime_error("CryptAcquireContext failed");
    }
    if (!CryptGenRandom(hProv, length, buffer)) {
        CryptReleaseContext(hProv, 0);
        throw std::runtime_error("CryptGenRandom failed");
    }
    CryptReleaseContext(hProv, 0);
}

#else // Unix systems
#include <fstream>
#include <stdexcept>

void randomString(unsigned char* buffer, std::size_t lenght)
{
    std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
    if (!urandom) {
        throw std::runtime_error("Failed to open /dev/urandom");
    }
    urandom.read(reinterpret_cast<char*>(buffer), length);
    if (!urandom) {
        throw std::runtime_error("Failed to read from /dev/urandom");
    }
}

#endif
