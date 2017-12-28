/*
Algorytm do generowania stringów na potrzeby metody brute force zaczerpnięty ze strony
http://hacksenkessel.com/2014/brute-force-algorithm-in-c/, przepisany przeze mnie z C++ na C
oraz dostosowany do bieżących potrzeb
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "crypter.h"
#include "main.h"

char * bruteforce(char *password, char *encrypted) 
{
	char *encryptedResult = malloc(sizeof(char) * (strlen(password) + 1));

	size_t keySize = sizeof(char) * (MAX_KEY_LENGTH + 1);
	char *key = malloc(keySize);
	memset(key, '\0', keySize);

	int n;
	int	pos = 0;
	int	count = 0;
	long max_perms = 0;

	//Założenie: klucz składa się tylko ze znaków, które można wywołać klawiaturą
	const int asciiMinIndex = 32;
	const int asciiMaxIndex = 127;
	const int charRange = asciiMaxIndex - asciiMinIndex;

	char *charArray = malloc((sizeof(char) * (charRange + 1)));

	int index = 0;
	for (char i = asciiMinIndex; i < asciiMaxIndex; i++)
	{
		charArray[index++] = i;
	}

	charArray[index] = '\0'; //NULL terminator na końcu tablicy

	//iteracje opierają się na maksymalnej liczbie permutacji tablicy z dopuszczalnymi znakami
	int alphabetLength = strlen(charArray);
	for (int n = 1; n <= MAX_KEY_LENGTH; n++)
	{
		max_perms += (long)pow(alphabetLength, n);
	}

	printf("Maksymalna długość hasła: %d, długość alfabetu: %d, ilość kombinacji: %d\n", MAX_KEY_LENGTH, alphabetLength, max_perms);

	while (count < max_perms) 
	{
		for (int a = 0; a < alphabetLength; a++)
		{
			key[pos] = charArray[a];
			
#ifdef PRINT_ITERATION_OUTPUT
			printf("%s\n", key);
#endif

			encryptDecrypt(password, key, encryptedResult);

			if (strcmp(encrypted, encryptedResult) == 0)
			{
				free(charArray);
				free(encryptedResult);
				return key;
			}

			if (count++ >= max_perms) break;
		}

		for (n = pos; n >= 0; n--) {
			if (key[n] != charArray[alphabetLength - 1]) {
				key[n]++;
				break;
			}
			else {
				if (n == 0) {
					memset(key, (int)charArray[0], ++pos + 1);
					break;
				}
				key[n] = charArray[0];
			}
		}
	}

	free(charArray);
	free(encryptedResult);
	return NULL;
}
