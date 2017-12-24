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
#define keyLength 1





char password[] = "kylewbanks.com";
char encrypted[sizeof(password)];
char decrypted[sizeof(password)];
char encryptedResult[sizeof(password)];

void printHeader()
{
	printf("############### Brutter v1.0 ###############\n");
	printf("Autor: Daniel Andraszeski, nr albumu: 287412\n");
	printf("\n");
}

/*
Algorytm szyfrowania XOR zaczerpniêty ze repozytorium https://github.com/KyleBanks/XOREncryption/tree/master/C.
Uzupe³niony o drobne poprawki z mojej strony
*/
void encryptDecrypt(char *input, char key[], char *output) 
{
	int i;
	for (i = 0; i < strlen(input); i++) {
		output[i] = input[i] ^ key[i % (sizeof(key) / sizeof(char))];
		//printf("i: %d , sizeof(key): %d , sizeof(char): %d , output: %c\n", i, sizeof(key), sizeof(char), output[i]);
	}

	output[i] = 0;
}


int brute_impl(char *str, int index, int max_depth)
{
	for (char i = 66; i < 127; i++)
	{
		str[index] = i;

		if (index == max_depth - 1)
		{
			printf("%s\n", str);
			encryptDecrypt(password, str, encryptedResult);

			if (strcmp(encryptedResult, encrypted) == 0)
			{
				printf("Znaleziono klucz szyfrowania: %s\n", str);
				return 1;
			}
		}
		else
		{
			int result = brute_impl(str, index + 1, max_depth);
			if (result == 1) return result;
		}
	}
}

void brute_sequential()
{
	char buf[keyLength + 1];

	int i;
	for (i = 1; i <= keyLength; ++i)
	{
		memset(buf, 0, sizeof(buf));
		int result = brute_impl(buf, 0, i);
		if (result == 1) break;
	}
}

int main(int argc, char *argv[]) 
{
	//char secretKey[] = "B"; //Can be any chars, and any size array
	const char secretKey[] = "B"; //Can be any chars, and any size array

	printHeader();
	encryptDecrypt(password, secretKey, encrypted);

	printf("Zdefiniowane has³o: %s\n", password);
	printf("Otrzymane zaszyfrowane has³o: %s\n", encrypted);

	//printf("Zdefiniowany klucz szyfrowania: %s\n", key);

	printf("\n");
	printf("Rozpoczynamy iterowanie w celu znalezienia klucza:\n");

	/*for (char i = -128; i < 127; i++)
	{		
		printf("Iteracja: %d, znak: %c", i + 129, i);

		char testKey[] = { i, '\0' };

		encryptDecrypt(password, testKey, encryptedResult);
		printf(" Zaszyfrowane has³o: %s\n", encryptedResult);

		if (strcmp(encryptedResult, encrypted) == 0)
		{
			printf("Znaleziono klucz szyfrowania: %s\n", testKey);
			break;
		}
	}*/

	brute_sequential();

	printf("Koniec!\n");

	//encryptDecrypt(password, encrypted);
	//printf("Encrypted:%s\n", encrypted);

	//encryptDecrypt(encrypted, decrypted);
	//printf("Decrypted:%s\n", decrypted);
}


