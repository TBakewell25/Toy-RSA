#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../utils/types.h"
#include<unistd.h>


int power(int x, int y, int p){
    int res = 1;
    while (y > 0) {
        if (y % 2 == 1)
            res = (res * x);
        y = y >> 1;
        x = (x * x);
    }
    return res % p;
}

int mod_inverse(int A, int M){
    for (int X = 1; X < M; X++)
        if (((A % M) * (X % M)) % M == 1)
            return X;
}


int findPrime(int* list,int size){
	int i, count = 0;

	for (i = 0; i < size;i++){
		if (list[i] == 0)
			count++;
	}
	return count;
}	

int eratos(int target){
	int *prime, *primeList, n, j, rand_ind, ret, counter;
	
	prime = (int*) malloc(sizeof(int) * (target+1));	
	memset(prime, 0, sizeof(int)* (target+1));

	for (int p = 2; p * p <= (target); p++) {
        	if (prime[p] == 0) {
            		for (int i = p * p; i <= target; i += p)
                		prime[i] = 1;
        	}
	}
	n = findPrime(prime, target+1);

	primeList = (int*) malloc(sizeof(int) * n);
	counter = 0;
	while (counter < n){	
		for (j = 0; j < target; j++){
			if (prime[j] == 0){
				primeList[counter] = j;
				counter++;
			}
		}
	}

	rand_ind = (rand() % (counter));
	ret = primeList[rand_ind];
	free(prime);
	free(primeList);
	return ret;
}
	
rsakey_t* generateKeys(unsigned int bitlength){
	srand(time(NULL));
	unsigned int p, q, e, d;
	long n;
	rsakey_t* key;
	
	p = eratos(bitlength);
	q = eratos(bitlength);
	
	n = p * q;
	
	e = eratos(bitlength);
	d = mod_inverse(e, ((q-1) * (p-1)));
	
	if (!(key = (rsakey_t*) malloc(sizeof(rsakey_t)))){
		printf("BAD MALLOC");
		return NULL;
	}

	key->l = bitlength;
	key->e = e;
	key->d = d;
	key->n = n;
	
	return key;
}

cipher_t* encrypt(rsakey_t* key, char* plaintext){
	int blocksize = strlen(plaintext);
	unsigned int i,  cryptext[blocksize];
	int encrypted, e, n, letter, l;
	cipher_t* cipher;
	char buff[blocksize];

	e = key->e;
	n = key->n;
	
	if (!(cipher = malloc(sizeof(cipher_t)))){
		printf("BAD MALLOC");
		return NULL;
	}

	for (i = 0; i < blocksize; i++){
		letter = (int)plaintext[i];
		cryptext[i] = power(letter, e, n);
		sprintf(&buff[i],"%d", cryptext[i]); 
	}
	
	cipher->c = buff;
 	cipher->l = blocksize;
	cipher->b = blocksize;

	return cipher;
}
/*
char* decrypt(rsakey_t* key, cipher_t* cipher){
	int* encrypted;
	int blocks, i, n, d;
	char decoded[256];
	
	encrypted = cipher->c;
	blocks = strlen(encrypted);
	
	d = key->d;
	n = key->n;

	for (i = 0; i < blocks; i++)
		decoded[i] = power(encrypted[i], d, n);

	return decoded;
}
		
*/					

