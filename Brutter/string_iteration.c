/* basic demo-bruteforce algorithm in C++ from hacksenkessel.com
*
* compile: g++ -O3 -pedantic -Wall -pipe -o bruteforce bruteforce.cpp
* run:     ./bruteforce
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define keyLength 2

void bruteforce();

int main(void) {
	bruteforce();
	return 0;
}


void bruteforce() {

	const char *alphabet = "abcdefghijklmnopqrstuvwxyz";
	//char pw[max_pw_len + 2];
	char pw[keyLength + 1];
	int n;
	int	pos = 0;
	int	count = 0;
	int max_perms = 0;

	/* create last possible password based on max. password length
	* and alphabet,  i.e. 'zzzz' for an alphabet [a-z] with 4 chars
	*/
	/*for (int k = 0; k<max_pw_len; k++) final += alphabet[alphabet.length() - 1];*/
	/* calculate number of permutations to run by interpreting the
	* final password as polynomial. Be careful, this is where an integer
	* overflow can occur by exceeding the max. password length and/or the alphabet
	*/
	//for (int n = 0; n < (int)final.length(); n++)
	//	max_perms += (long double)((long double)(alphabet.find_first_of(string(1, final[n])) + 1) * powl(alphabet.length(), final.length() - n - 1));
	/* Print out calculated information and set password
	* to first char in alphabet
	*/
	/*cout << "Last password: " << final << endl << "Permutations:  " << max_perms << endl << endl;
	cout << "Starting bruteforce:" << endl;*/

	int alphabetLength = strlen(alphabet);
	for (int n = 1; n <= keyLength; n++)
	{
		max_perms += (int)pow(alphabetLength, n);
	}

	printf("Number of permutations: %d\n", max_perms);

	memset(pw, '\0', sizeof(pw));
	pw[0] = alphabet[0];
	/* bruteforce until previously calculated max. number
	* of permutations is exceeded */
	while (count < max_perms) {
		/* iterate last password index separately, as we know its number
		* of iterations matches the alphabet's length
		*/
		for (int a = 0; a < alphabetLength; a++)
		{
			pw[pos] = alphabet[a];
			/*cout << pw << endl;*/
			printf("%s\n", pw);
			if (count++ >= max_perms) break;
		}
		/* iterate remaining indexes in descending order, as in
		* all indexes except for the last index we already iterated
		*/
		for (n = pos; n >= 0; n--) {
			if (pw[n] != alphabet[alphabetLength - 1]) {
				pw[n]++;
				break;
			}
			else {
				if (n == 0) {
					/* increase password length */
					memset(pw, (int)alphabet[0], ++pos + 1);
					break;
				}
				/* re-initialize current password index */
				pw[n] = alphabet[0];
			}
		}
	}
}