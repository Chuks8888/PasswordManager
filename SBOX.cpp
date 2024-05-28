#include "Sboxes.h"
void SBOX(unsigned char &character)
{
	character = Sbox[character];
}

void INVSBOX(unsigned char &character)
{
	character = invSbox[character];
}
