/*.Napisati program koji proverava da li je broj prost i ispisuje ga
u binarnom, decimalnom i heksadecimalnom formatu putem serijskog terminala.
Unos broja se vrši putem matrične tastature od strane korisnika. Nakon unetog
broja, pritiskom na taster #, traženi parametri se ispisuju. Primer unosa je dat u
nastavku.
ULAZ (matrična tastatura): 31
IZLAZ (serijski terminal): prost, bin:11111, dec:31, hex:1F*/






#include "prost.h"

bool isPrime(uint32_t  n)
{
	if (n == 1)
		return 0;

	for (uint32_t i = 2; i <= n/2; i++)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}

	return 1;
}
