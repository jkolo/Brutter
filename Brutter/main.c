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
#include <omp.h>
#include <unistd.h>

#include "bruteforce.h"
#include "crypter.h"

//Parametry programu:
const char PASSWORD[] = "pwd1234";
const char SECRET_KEY[] = "zABCD";
const int MAX_KEY_LENGTH = 5;
const int PRINT_ITERATION_OUTPUT = 0;

void printHeader()
{
	printf("############### Brutter v1.0 ###############\n");
	printf("Autor: Daniel Andraszewski, nr albumu: 287412\n");
	printf("\n");
}

int main(int argc, char *argv[]) 
{
	char * result = NULL;
	char encrypted[sizeof(PASSWORD)];

	if(!omp_get_cancellation())
    {
      printf("Cancellations were not enabled, enabling cancellation and rerunning program\n");
      putenv("OMP_CANCELLATION=true");
      execv(argv[0], argv);
    }

	printHeader();
	secretEncrypt(PASSWORD, encrypted);

	printf("Zdefiniowane haslo: %s\n", PASSWORD);
	printf("Otrzymane zaszyfrowane haslo: %s\n", encrypted);
	printf("\n");

	//sleep(3); // niech użytkownik zobaczy początkowy header!

	if (PRINT_ITERATION_OUTPUT)
	{
		printf("Rozpoczynamy iterowanie w celu znalezienia klucza:\n");
		//sleep(1); // j.w.
	}
	else
	{
		printf("(Wylaczono wyswietlanie iteracji lancucha znakow)\n");
	}

	double start_time = omp_get_wtime();
	result = bruteforce(PASSWORD, encrypted);
	double time = omp_get_wtime() - start_time;

	if (result != NULL)
	{
		printf("Znaleziono klucz szyfrujacy: %s\n", result);
	}
	else
	{
		printf("Nie znaleziono klucza szyfrujacego!\n");
	}

	printf("Operacja zajela %.3f sekund.\n", time);

	//free(result);
	return 0;
}


