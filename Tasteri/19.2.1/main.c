/*Napisati program koji detektuje pritisak tastera i šalje indikaciju
pritisnutog tastera na serijski terminal. Pri tome, važi pravilo jedan pritisak –
jedan karakter, bez obzira na to koliko dugo korisnik drži taster u pritisnutom
stanju.*/



#include <avr/io.h>
#include <stdint.h>
#include "usart.h"
#include "keypad.h"

uint8_t rows[4] = {11, 10, 9, 8}; /*Definisemo redove matricne tastature kroz pinove*/
uint8_t cols[4] = {7, 6, 5, 4};/*Definisemo kolone matricne tastature*/

int16_t main()
{
	
        uint8_t button_old, button_new;/*Definisemo staru i novu vrednost tastera,vremensko diferenciranje*/
	usartInit(9600);/*Brzina serijske komunikacije*/
	keypadInit(rows, cols);/*Pozivanje na elemente tastature a to su redovi i kolone*/

	while (1)
	{
		button_new = keypadScan(); /*Skeniramo pritisak na taster*/
		if (button_new != 0x00 && button_new != button_old)
		{
			usartPutChar(button_new);
			usartPutChar('\n');
		}

		button_old = button_new; /*Inicijalizacija*/
	}

	return 0;
}
