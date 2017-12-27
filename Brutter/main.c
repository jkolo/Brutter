/*
################## Brutter v1.0 ######################
Autor: Daniel Andraszeski, nr albumu: 287412
Program na potrzeby z projektu przedmiotu
Programowanie Równoleg³e i Rozproszone
Politechnika Warszawska, 2017/2018
Program do ³amania has³a zaszyfrowanego algorytmem XOR
przy u¿yciu metody bruteforce
######################################################
*/

#include <stdio.h>
#include <string.h>
#include "bruteforce.h"
#include "crypter.h"

//Parametry programu:
const char password[] = "kylewbanks.com";
const char *secretKey = "!AAB";

void printHeader()
{
	printf("############### Brutter v1.0 ###############\n");
	printf("Autor: Daniel Andraszeski, nr albumu: 287412\n");
	printf("\n");
}

int main(int argc, char *argv[]) 
{
	char * result = NULL;
	char encrypted[sizeof(password)];

	printHeader();
	secretEncrypt(password, encrypted);

	printf("Zdefiniowane haslo: %s\n", password);
	printf("Otrzymane zaszyfrowane haslo: %s\n", encrypted);

	printf("\n");
	printf("Rozpoczynamy iterowanie w celu znalezienia klucza:\n");

	result = bruteforce(password, encrypted);

	if (result != NULL)
	{
		printf("Znaleziono klucz szyfrujacy: %s\n", result);
	}
	else
	{
		printf("Nie znaleziono klucza szyfrujacego!\n");
	}

	free(result);
}


