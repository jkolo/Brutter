/*
Algorytm do generowania string�w na potrzeby algorytmu brute force zaczerpni�ty ze strony
http://hacksenkessel.com/2014/brute-force-algorithm-in-c/, przepisany przeze mnie z C++ na C
oraz dostosowany do bie��cych potrzeb
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "crypter.h"

#define MAX_KEY_LENGTH 8

char * bruteforce(char *password, char *encrypted) 
{
	char *encryptedResult = malloc(sizeof(char) * (strlen(password) + 1));

	size_t keySize = sizeof(char) * (MAX_KEY_LENGTH + 1);
	char *key = malloc(keySize);
	memset(key, '\0', keySize);

	int n;
	int	pos = 0;
	int	count = 0;
	int max_perms = 0;

	//Za�o�enie: klucz sk�ada si� tylko ze znak�w, kt�re mo�na wywo�a� klawiatur�
	const int asciiMinIndex = 32;
	const int asciiMaxIndex = 127;
	const int charRange = asciiMaxIndex - asciiMinIndex;

	char *charArray = malloc((sizeof(char) * (charRange + 1)));

	int b = 0;
	for (char i = asciiMinIndex; i < asciiMaxIndex; i++)
	{
		charArray[b] = i;
		b++;
	}

	charArray[b] = '\0'; //NULL terminator na ko�cu tablicy

	//iteracje opieraj� si� na maksymalnej liczbie permutacji
	int alphabetLength = strlen(charArray);
	for (int n = 1; n <= MAX_KEY_LENGTH; n++)
	{
		max_perms += (int)pow(alphabetLength, n);
	}

	while (count < max_perms) 
	{
		for (int a = 0; a < alphabetLength; a++)
		{
			key[pos] = charArray[a];
			printf("%s\n", key);

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
					/* increase password length */
					memset(key, (int)charArray[0], ++pos + 1);
					break;
				}
				/* re-initialize current password index */
				key[n] = charArray[0];
			}
		}
	}

	free(charArray);
	free(encryptedResult);
	return NULL;
}