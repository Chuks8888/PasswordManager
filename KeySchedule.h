#ifndef KEYSCHEDULE_H
#define KEYSCHEDULE_H

#include <vector>

std::vector<unsigned char> RconVal = {0x36, 0x1b, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00};
unsigned char RoundKey[4][4];

void RotWord(unsigned char KeyByte[]);
void Rcon(unsigned char word[]);
void CreateG(unsigned char word[], unsigned char origin[]);
void KeySchedule(unsigned char Key[16]);
void XorWords(unsigned char destination[], unsigned char first[], unsigned char second[]);
void FillRoundKey(unsigned char word0[], unsigned char word1[], unsigned char word2[], unsigned char word3[]);

#endif // KEYSCHEDULE_H
