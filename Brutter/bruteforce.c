/*
Algorytm do generowania stringów na potrzeby metody brute force zaczerpnięty ze strony
http://hacksenkessel.com/2014/brute-force-algorithm-in-c/, przepisany przeze mnie z C++ na C
oraz dostosowany do bieżących potrzeb
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#include "crypter.h"
#include "main.h"

char * bruteforce(char *password, char *encrypted) 
{
	size_t keySize = sizeof(char) * (MAX_KEY_LENGTH + 1);

	char* keyResult = NULL;
	unsigned long long max_perms = 0;

	//Założenie: klucz składa się tylko ze znaków, które można wywołać klawiaturą
	const int asciiMinIndex = 32; //' '
	const int asciiMaxIndex = 126; //'~'
	const int alphabetLength = asciiMaxIndex - asciiMinIndex + 1;

	//iteracje opierają się na maksymalnej liczbie permutacji tablicy z dopuszczalnymi znakami
	for (int n = 1; n <= MAX_KEY_LENGTH; n++)
	{
		max_perms += (unsigned long long)pow(alphabetLength, n);
	}

	//omp_set_dynamic(0);     // Explicitly disable dynamic teams
	omp_set_num_threads(1); // Use 4 threads for all consecutive parallel regions

	printf("OMP max threads: %d, alphabetLength = %d, MAX_KEY_LENGTH = %d, max_perms = %lld\n", omp_get_max_threads(), alphabetLength, MAX_KEY_LENGTH, max_perms);

	#pragma omp parallel
	{
		char *encryptedResult = malloc(sizeof(char) * (strlen(password) + 1));
		char *key = malloc(keySize);

		memset(key, '\0', keySize);
		int pos = 0;
		
		printf("Thread: %d starting\n", omp_get_thread_num());

		#pragma omp for
		for (unsigned long long count = 0; count < max_perms; count++) 
		{
			int pos = 0;
			unsigned long long tmp = count + 1;
			while (tmp > 0)
			{
				key[pos++] = (char)(tmp % alphabetLength) + asciiMinIndex;
				tmp /= (unsigned long long)alphabetLength;
			}

			if (PRINT_ITERATION_OUTPUT)
			{
				printf("Thread: %d, key = \"%s\", count = %lld\n", omp_get_thread_num(), key, count);
			}

			encrypt(password, key, encryptedResult);

			if (strcmp(encrypted, encryptedResult) == 0)
			{
				printf("Thread: %d, key = \"%s\", count = %lld, FOUND!\n", omp_get_thread_num(), key, count);
				#pragma omp atomic write
				keyResult = strdup(key);
				#pragma omp cancel for
			}

			#pragma omp cancellation point for
		}

		free(encryptedResult);
	}

	return keyResult;
}
