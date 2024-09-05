#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../utils/types.h"

int findPrime(int* list){
	int i, count = 0;

	for (i = 0; i < sizeof(list);i++){
		if (list[i] == 0)
			count++;
	}
	return count;
}	

int generate_prime(unsigned int bits, int k){
	srand(time(NULL));
	int count, iterations, j, a, m;
	long long n, b;
	count = 0;
	b = (2<<(bits+1))-1;

	while(1){
		n = (rand() % (b - 1))+3;
		iterations = 0;
		if ((n % 2) == 0)
			n++;
		count++;
		for (j = 0; j < k; j++){
			a = (rand() % (n - 1))+1;
			if (fmod(pow(a,n-1), (double)n) != 1) 
				break;
			else 
				iterations++;	
		}
		if (iterations == k)
			return n;
	}

}

int eratos(int target){
	srand(time(NULL));
	int *prime, *primeList, n, j;
	
	prime = (int*) malloc(sizeof(int) * (target+1));	
	memset(prime, 0, sizeof(int)* (target+1));

	for (int p = 2; p * p <= (target); p++) {
        	if (prime[p] == 0) {
            		for (int i = p * p; i <= target; i += p)
                		prime[i] = 1;
        	}
	}
	n = findPrime(prime);

	primeList = (int*) malloc(sizeof(int) * n);
	int counter = 0;
	while (counter < n){	
		for (j = 0; j < target; j++){
			if (prime[j] == 0){
				primeList[counter] = j;
				counter++;
			}
		}
	}

	int rand_ind = (rand() % (counter));
	int ret = primeList[rand_ind];
	free(prime);
	free(primeList);
	return ret;
}

		
	
		 
	

rsakey_t* generateKeys(unsigned int bitlength){
	unsigned int p, q, e, d;
	long n;
	rsakey_t* key;
	size_t block_length;
	
	p = eratos(bitlength);
	q = eratos(bitlength);

	n = p * q;
	
	e = eratos(bitlength);
	d = fmod(pow(e, -1), ((p-1) * (q-1)));

	if ((key = (rsakey_t*) malloc(sizeof(rsakey_t)))){
		printf("BAD MALLOC");
		return NULL;
	}

	key->l = &bitlength;
	key->e = &e;
	key->d = &d;
	key->n = &n;
	
	return key;
}

cipher_t* encrypt(rsakey_t* key, char* plaintext){
	unsigned int blocksize, text_len, i;
	int encrypted, e, n, **blocks;
	int* letter;
	cipher_t* cipher;

	e = *(key->e);
	n = *(key->n);

	blocksize = strlen(plaintext);

	if ((blocks = malloc(sizeof(int*)*blocksize)) != 0){
		printf("BAD MALLOC");
		return NULL;
	}

	if ((cipher = malloc(sizeof(cipher_t))) != 0){
		printf("BAD MALLOC");
		return NULL;
	}

	for (i = 0; i < blocksize; i++){
		letter = (int*) plaintext[i];
		encrypted = fmod(pow(*letter, e) , (long)n);
		blocks[i] = letter;
	}

	cipher->c = (char*) *blocks;
	cipher->l = blocksize;
	cipher->b = blocksize;

	return cipher;
}

char* decrypt(rsakey_t* key, cipher_t* cipher){
	char* encrypted;
	int blocks, i, n, d;
	char decoded[256];
	
	encrypted = cipher->c;
	blocks = strlen(encrypted);
	
	d = *(key->d);
	n = *(key->n);

	for (i = 0; i < blocks; i++)
		decoded[i] = fmod(pow(encrypted[i], d), n);

	return decoded;
}
		
					

	
	

	

	

	

