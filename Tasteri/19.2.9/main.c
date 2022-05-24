/*Napisati program koji implementira igru sličnu popularnoj igri
Guitar Hero. Putem serijskog terminala se ispisuju karakteri brojeva 0-9 i slova AD jedan po jedan, generisani na slučajan način. Korisnik putem matrične tastature
unosi odgovarajuće vrednosti karaktera koje su prikazane na serijskom terminalu.
Pri tome, potrebno je da korisnik unese trenutno prikazani karakter u odgovarajućem vremenskom intervalu. Inicijalno, ovaj vremenski interval iznosi 2s, pri
čemu se umanjuje za 100ms nakon svakih 10 uspešnih unosa. Za svaki uspešan
unos, ukupan broj pogodaka se uvećava. U suprotnom ukoliko je unos neispravan,
prikazuje se novi slučajan karakter i korisnik gubi jedan, od ukupno tri života.
Igra se završava kada korisnik izgubi sva tri života. Na kraju, potrebno je ispisati
ukupan broj pogodaka u serijskom terminalu.
*/




#include <avr/io.h>
#include "usart.h"
#include "keypad.h"
#include "ghero.h"

uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5, 4};

int16_t main()
{
	timerOn();
	usartInit(9600);
	keypadInit(rows, cols);

	uint8_t button_old , button_new;

	uint8_t gen_symbol, input_symbol;

	uint8_t cond = 0;

	uint32_t lives = 3;
	uint32_t points = 0;
	uint32_t time = 2000;
	uint32_t counter = 0;

	while (1)
	{
		if (!cond)
		{
			ghDisplay(lives, points, time, counter);

			gen_symbol = symGen();

			usartPutChar(gen_symbol);
			usartPutString("     ");

			cond = 1;
		}

		button_new = keypadScan();

		if (button_new != 0x00 && button_new != button_old)
		{
			usartPutChar(button_new);
			usartPutChar('\r');

			ghOperation(gen_symbol, button_new, &lives, &points, &time, &counter);

			if (lives == 0)
				ghResult(&lives, &points, &time, &counter);

			cond = 0;
		}

		button_old = button_new;
	}
}
