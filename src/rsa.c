#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../utils/types.h"
#include<unistd.h>


unsigned int power(unsigned int x, unsigned int y, unsigned int p){
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


int findPrime(BIGNUM* list,int size){
	BIGNUM i, count = 0;

	for (i = 0; i < size;i++){
		if (list[i] == 0)
			count++;
	}
	return count;
}	



/*int eratos(BIGNUM target){
	BIGNUM *prime, *primeList, n, j, rand_ind, ret, counter;
	
	prime = (BIGNUM*) malloc(sizeof(BIGNUM) * (target+1));	
	memset(prime, 0, sizeof(BIGNUM)* (target+1));

	for (BIGNUM p = 2; p * p <= (target); p++) {
        	if (prime[p] == 0) {
            		for (BIGNUM i = p * p; i <= target; i += p)
                		prime[i] = 1;
        	}
	}
	n = findPrime(prime, target+1);

	primeList = (BIGNUM*) malloc(sizeof(BIGNUM) * n);
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
	
rsakey_t* generateKeys(BIGNUM bitlength){
	srand(time(NULL));
	unsigned int p, q, e, d, size;
	BIGNUM n;
	rsakey_t* key;

	n = 
	size = bitlength / 3.321928;

	p = eratos(pow(10, size));
	q = eratos(pow(10, size));
	
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

int* encode(int* ascii, int blocksize, int n, int e, unsigned int size){
	int i, num, retBuff[50], tmp, l, j = 0;
	char *combo, curr[5], next[5], full[size+1]; 
	
	while(j <= blocksize){
		sprintf(curr, "%d", ascii[j]);	
		if (j <= blocksize-1)
			sprintf(next, "%d", ascii[j+1]);	
		strcat(curr, next);
		strcat(full, curr);
		j= j + 2;
	}
	i = 0;
	while (i < sizeof(full)){
		combo = strtok(full, &full[j+blocksize]);
		tmp = atoi(combo);
		l = fmod(pow(tmp, e), n);
		j = j + blocksize;
		retBuff[j%blocksize];
	}

	return retBuff;
}
				
	

cipher_t* encrypt(rsakey_t* key, char* plaintext){
	int blocksize = strlen(plaintext);
	int i,  cryptext[blocksize];
	unsigned int encrypted, e, n, letter, l;
	cipher_t* cipher;
	int *buff, *encoded;

	e = key->e;
	n = key->n;
	
	if (!(cipher = malloc(sizeof(cipher_t)))){
		printf("BAD MALLOC");
		return NULL;
	}
	if (!(buff = malloc(sizeof(int)*(blocksize+1)))){
		printf("BAD MALLOC");
		return NULL;
	}

	for (i = 0; i < blocksize; i++){
		letter = (int)plaintext[i];
		//l = power(letter, e, n);
		//l = fmod(pow(letter, e), n);
		buff[i] = letter;
	}
	
	encoded = encode(buff, 3, n, e, blocksize-1); 
	
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

