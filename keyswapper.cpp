#include "keyswapper.h"
#include "randomGenerator.h"

keyswapper::keyswapper() {
    key = "";
    loop = false;
}

// give the key to the thread
void keyswapper::givekey(std::string k)
{
    if(loop == false)
    {
        key = k;
        loop = true;
    }
}

void keyswapper::sendtext(std::string & text, bool mode)
{
    if(loop == false)
    {
        aes.Use(text, key, mode);
        loop = true;
    }
}

void keyswapper::run()
{
    if(key.empty())
        return;

    encryptor1 = randomkey();
    aes.Use(key, encryptor1, 1);

    while(loop)
    {
        for(int i = 0; i < 25; i++)
        {
            encryptor2 = randomkey();
            aes.Use(encryptor1, encryptor2, 1);

            for(int j = 0; j < 125; j++)
            {
                encryptor3 = randomkey();
                aes.Use(encryptor2, encryptor3, 1);
                aes.Use(encryptor2, encryptor3, 0);
            }

            aes.Use(encryptor1, encryptor2, 0);
        }
    }
    aes.Use(key, encryptor1, 0);
}

// turn off the thread loop
void keyswapper::endloopslot()
{
    loop = false;
}
