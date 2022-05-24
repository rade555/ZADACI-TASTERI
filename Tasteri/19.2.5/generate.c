/*Napisati program koji proverava da li je korisnik ljudsko biće.
Na početku, potrebno je generisati slučajan niz karaktera dužine od 5 do 9 karaktera. Podrazumevati da karakteri mogu biti brojevi 0-9 i slova A-D. Dužinu
niza, takođe, generisati na slučajan način. Tako generisan niz karaktera ispisati
putem serijskog terminala. Nakon toga, potrebno je preko matrične tastature uneti
prikazani niz karaktera. Ukoliko je niz ispravno unet, putem serijskog terminala
potrebno je ispisati "Ispravno unet kod", odnosno "Neispravno unet kod" ukoliko
niz nije ispravno unet.*/



#include <stdlib.h>
#include "generate.h"

#define UPPER 9
#define LOWER 5

void generateCode(uint8_t *code)
{
	uint8_t length = (rand() % (UPPER - LOWER + 1)) + LOWER;

	for (uint8_t i = 0; i != length;)
	{
		if (rand() % 2)
			*code = rand() % ('9' - '0' + 1) + '0';
		else
			*code = rand() % ('D' - 'A' + 1) + 'A';

		i++;
		code++;
	}
}

bool matching(uint8_t *a, uint8_t a_l, uint8_t *b, uint8_t b_l)
{
	if (a_l != b_l)
		return false;

	for (uint8_t i = 0; i != a_l - 1;)
	{
		if (*a != *b)
			return false;

		i++;
		a++;
		b++;
	}

	return true;
}
