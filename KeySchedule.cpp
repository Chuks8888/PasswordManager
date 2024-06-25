#include "qswap.h"
#include "Tables.h"
#include "KeySchedule.h"
#include <vector>

void RotWord(unsigned char KeyByte[])
{
    qSwap(KeyByte[0], KeyByte[3]);
    qSwap(KeyByte[0], KeyByte[2]);
    qSwap(KeyByte[0], KeyByte[1]);
}

void Rcon(unsigned char word[])
{
    word[0] = word[0] ^ RconVal.back();
    RconVal.pop_back();
}

void CreateG(unsigned char word[], unsigned char origin[])
{
    for(int i=0;i<4;i++)
        word[i] = origin[i];
    RotWord(word);
    for(int i=0;i<4;i++)
        SBOX(word[i]);
    Rcon(word);
}

void KeySchedule()
{
    unsigned char word0[4], word1[4], word2[4], word3[4];
    for(int i=0;i<4;i++)
    {
        word0[i] = RoundKey[0][i];
        word1[i] = RoundKey[1][i];
        word2[i] = RoundKey[2][i];
        word3[i] = RoundKey[3][i];
    }

    unsigned char G[4];
    CreateG(G, word3);

    XorWords(word0, word0, G);
    XorWords(word1, word1, word0);
    XorWords(word2, word2, word1);
    XorWords(word3, word3, word2);

    FillRoundKey(word0, word1, word2, word3);
}

void XorWords(unsigned char destination[], unsigned char first[], unsigned char second[])
{
    for(int i=0;i<4;i++)
    {
        destination[i] = first[i] ^ second[i];
    }
}

void FillRoundKey(unsigned char word0[], unsigned char word1[], unsigned char word2[], unsigned char word3[])
{
    for(int i=0;i<4;i++)
    {
        RoundKey[0][i] = word0[i];
        RoundKey[1][i] = word1[i];
        RoundKey[2][i] = word2[i];
        RoundKey[3][i] = word3[i];
    }
}
