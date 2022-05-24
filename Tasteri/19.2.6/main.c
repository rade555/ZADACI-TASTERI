/*Napisati program koji simulira proveru PIN koda korisnika na
bankomatu.
• Realizovati unos imena i prezimena korisnika putem serijskog terminala, a
potom izvršiti proveru da li se korisnik nalazi u bazi. Primer jednostavne
baze korisnika je dat u nastavku.
# define NUM_OF_USERS 5
int8_t user_database [ NUM_OF_USERS ][32] = {
" Marko ␣ Markovic " ,
" Milos ␣ Milosevic " ,
" Petar ␣ Petrovic " ,
" Jovan ␣ Jovanovic " ,
" Janko ␣ Jankovic "
};
• Ukoliko se korisnik nalazi u bazi, omogućiti unos PIN koda putem matrične
tastature. PIN kod predstavlja četvorocifreni decimalni broj koji se unosi
karakter po karakter. Prilikom unosa pina potrebno je izvršiti ispis ’*’ preko
serijskog terminala za svaki uneti karakter. Unos se okončava pritiskom na
taster ’#’. Po okončanju unosa, obavestiti korisnika da li je PIN ispravno
unet ili ne. Primer baze korisničkih PIN-ova je dat u nastavku.
int8_t users_pin_database [ NUM_OF_USERS ][32] = {
" 3595 " ,
" 7897 " ,
" 5656 " ,
" 3373 " ,
" 5114 "
};
*/





#include <avr/io.h>
#include <string.h>
#include "usart.h"
#include "keypad.h"
#include "generate.h"

#define NUM_OF_USERS 5
#define PIN_LENGTH 4

int8_t user_database[NUM_OF_USERS][32] = {
		"Marko Markovic",
		"Milos Milosevic",
		"Petar Petrovic",
		"Jovan Jovanovic",
		"Janko Jankovic"
};

int8_t user_pin_database[NUM_OF_USERS][32] = {
		"3595",
		"7897",
		"5656",
		"3373",
		"5114"
};

uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5, 4};

int16_t main()
{
	usartInit(9600);
	keypadInit(rows, cols);

	uint8_t button_new, button_old;
	uint8_t person[32];
	uint8_t input_pin[32];

	uint8_t cond = 0;
	uint8_t fnd = NUM_OF_USERS;
	uint8_t tmp = 0;
	uint8_t pin_l = 0;

	while (1)
	{
		if (!cond)
		{
			usartPutString("Unesite ime i prezime: ");
			while (!usartAvailable())
			;
			_delay_ms(100);

			usartGetString(person);

			for (uint8_t i = 0; i != NUM_OF_USERS; i++)
			{
				if (matching(user_database[i], strlen(user_database[i]), person, strlen(person)))
				{
					fnd = i;
					break;
				}
			}

			if (fnd == NUM_OF_USERS)
			{
				usartPutString("\rKorisnik se ne nalazi u bazi!\r\r");
			}
			else
			{
				usartPutString("\rKorisnik pronadjen! Unesite pin: ");
				cond = 1;
			}
		}

		button_new = keypadScan();
		if (button_new != 0x00 && button_new != button_old)
		{
			if (button_new >= '0' && button_new <= '9')
				{
					usartPutChar('*');
					input_pin[tmp] = button_new;
					tmp++;
				}
			else if (button_new == '#')
				{
					pin_l = strlen(input_pin);

					usartPutString("#\r");
					if (matching(user_pin_database[fnd], PIN_LENGTH, input_pin, pin_l))
						usartPutString("Uneti PIN je ispravan!\r\r");
					else
						usartPutString("Uneti PIN nije ispravan!\r\r");

					for (uint8_t i = 0; i != pin_l; i++)
						input_pin[i] = 0;

						cond = 0;
						tmp = 0;
				}
			}

		button_old = button_new;
	}
}
