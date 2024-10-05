#include "keyswapper.h"
#include "randomGenerator.h"

keyswapper::keyswapper() {
    key = "";
    loop = false;

    connect(this, &keyswapper::started, this, &keyswapper::threadStart);
    connect(this, &keyswapper::finished, this, &keyswapper::threadEnd);
}

// give the key to the thread
void keyswapper::givekey(std::string k)
{
    if(loop == false)
        key = k;
}

bool keyswapper::sendtext(std::string & text, bool mode)
{
    if(loop == false)
    {
        if(!key.empty())
        {
            aes.Use(text, key, mode);
            return true;
        }
    }
    return false;
}

void keyswapper::run()
{
    if(key.empty())
        return;

    loop = true;
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

    /////// TEST COUT /////////
    std::cout << key << std:: endl;
}

// turn off the thread loop
void keyswapper::endloopslot()
{
    loop = false;
}

// Both are testing functions
void keyswapper::threadStart()
{
    std::cout<<"Resuming thread" << std::endl;
}

void keyswapper::threadEnd()
{
    std::cout<<"Thread stopped" << std::endl;
}
