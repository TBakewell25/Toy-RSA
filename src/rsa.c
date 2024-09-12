#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../utils/types.h"
#include<unistd.h>
#include <gmp.h>

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

void init_key(rsakey_t* Key){
	mpz_init(Key->e);
	mpz_init(Key->d);
	mpz_init(Key->n);
}

void fill_key(unsigned long l, mpz_t e, mpz_t d, mpz_t n, rsakey_t* key){
	key->l = l;	

	mpz_set(key->e, e);
	mpz_set(key->d, d);
	mpz_set(key->n, n);
}

void generate_prime(int bits, int k, mpz_t result){
	int count, iterations, i;
	mpz_t n, a, num, tmp, j, l;
	
	gmp_randstate_t state;
    	gmp_randinit_default(state);  // Initialize state
	
	mpz_init(n);
	mpz_init(a);
	mpz_init(num);
	mpz_init(tmp);
	mpz_init(j);
	mpz_init(l);


	count = 0;
	while (1){
		mpz_urandomb(n, state, bits);
		mpz_mod_ui(l, n, 2);
		if (mpz_cmp_ui(l, 0) == 0)
			mpz_add_ui(n, n, 1);
		count++;
		iterations = 0;
		for (i = 0; i < k; i++){
			mpz_urandomb(a, state, 200);
			mpz_sub_ui(tmp, n, 1);	
			mpz_powm(j, a, tmp, n);
			if (mpz_cmp_ui(j, 1) != 0)
				break;
			else
				iterations++;
		}
		if (iterations == k){
			mpz_set(result, n);
			return;
		}
	}
}

rsakey_t* generateKeys(int bitlength){
	mpz_t n, p ,q, e, d;

	mpz_init(n);
	mpz_init(p);
	mpz_init(q);
	mpz_init(e);
	mpz_init(d);

	rsakey_t* key;

	generate_prime(bitlength, 10, p);
	generate_prime(bitlength, 10, q);
	
	mpz_mul(n, p, q);
	generate_prime(bitlength, 10, e);

	while(mpz_cmp(e, n) >=  0)	
		generate_prime(200, 10, e);
	
	mpz_powm_ui(d, e, -1, n); 
	
	if (!(key = (rsakey_t*) malloc(sizeof(rsakey_t)))){
		printf("BAD MALLOC");
		return NULL;
	}

	init_key(key);
	fill_key(bitlength, e, d, n, key);
	
	return key;
}


/*
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
