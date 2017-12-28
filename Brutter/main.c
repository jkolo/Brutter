/*
################## Brutter v1.0 ######################
Autor: Daniel Andraszeski, nr albumu: 287412
Program na potrzeby z projektu przedmiotu
Programowanie Równoległe i Rozproszone
Politechnika Warszawska, 2017/2018
Program do łamania hasła zaszyfrowanego algorytmem XOR
przy użyciu metody bruteforce
######################################################
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "bruteforce.h"
#include "crypter.h"

//Parametry programu:
const char PASSWORD[] = "pwd123456";
const char SECRET_KEY[] = "!AABCD";
const int MAX_KEY_LENGTH = 8;

void printHeader()
{
	printf("############### Brutter v1.0 ###############\n");
	printf("Autor: Daniel Andraszeski, nr albumu: 287412\n");
	printf("\n");
}

int main(int argc, char *argv[]) 
{
	char * result = NULL;
	char encrypted[sizeof(PASSWORD)];

	printHeader();
	secretEncrypt(PASSWORD, encrypted);

	printf("Zdefiniowane haslo: %s\n", PASSWORD);
	printf("Otrzymane zaszyfrowane haslo: %s\n", encrypted);
	printf("\n");

	sleep(3); // niech użytkownik zobaczy początkowy header!

#ifdef PRINT_ITERATION_OUTPUT
	printf("Rozpoczynamy iterowanie w celu znalezienia klucza:\n");
	sleep(2); // j.w.
#else
	printf("(Wylaczono wyswietlanie iteracji lancucha znakow)\n");
#endif

	clock_t start = clock();
	result = bruteforce(PASSWORD, encrypted);
	clock_t end = clock();

	if (result != NULL)
	{
		printf("Znaleziono klucz szyfrujacy: %s\n", result);
	}
	else
	{
		printf("Nie znaleziono klucza szyfrujacego!\n");
	}

	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Operacja zajela %.2f sekund.\n", seconds);

	free(result);
}


