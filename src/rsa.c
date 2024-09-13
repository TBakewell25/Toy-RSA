#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../utils/types.h"
#include<unistd.h>
#include <gmp.h>

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
	mpz_powm_ui(d, e, -1, n); 
	
	if (!(key = (rsakey_t*) malloc(sizeof(rsakey_t)))){
		printf("BAD MALLOC");
		return NULL;
	}

	init_key(key);
	fill_key(bitlength, e, d, n, key);
	
	return key;
}

char* strSplit(char* string, int base, int index) {
	int size;

	size = index-base+1;
	char* retString = (char*) malloc(sizeof(char)*size);
    

	memcpy(retString, string + base, index -base);
    
	retString[index] = '\0';

	return retString;
}
	
				
char* encode(char* text, unsigned int size){
	unsigned int j, i, buff[size];
	char* encoded, *tmp;
	

	encoded = (char*) malloc(sizeof(char) * size * 3);
	
	encoded[0] = '\0';

	for (j = 0; j < size; j++)
		buff[j] = (int) text[j];

	for (i = 0; i < size; i++){
		tmp = malloc(sizeof(char)*5);
		sprintf(tmp, "%d", buff[i]);
		char new[sizeof(tmp)+1];

		if(strlen(tmp) == 2){
			new[0] = '\0';
			strcat(new, tmp);
			tmp = new;
		}
		strcat(encoded, tmp);
	}
	return encoded;
}


		
cipher_t* encrypt(rsakey_t* key, char* plaintext){
	unsigned int size, blocksize, j, i =0, blockCount = 0;
	mpz_t n, m, e, *blocks, tmp;
	char* encoded, *block; 
	cipher_t* cipher;

	mpz_init(n);
	mpz_init(e);
	mpz_init(m);
	mpz_set(n, key->n);
	mpz_set(n, key->e);

	size = strlen(plaintext);
	encoded = encode(plaintext, size);

	blocksize = (int)floor(mpz_sizeinbase(n, 10)/3.32);
	blocks = malloc(sizeof(int) * size);
	block = malloc(sizeof(mpz_t) * 10);
	
	cipher = malloc(sizeof(cipher));
	printf("%d\n", size);
	printf("%d\n", blocksize);
	for (j = 0; j < size-6; j += 6){
		block = strSplit(encoded, j, j + 6);
		
		mpz_init(tmp);
		mpz_init(blocks[i]);
		
		mpz_set_ui(m, atoi(block));
		mpz_powm(tmp, m, e, n);
		mpz_set(blocks[i], tmp);
		mpz_clear(tmp);

		blockCount++;
		i++;
		
	}
	cipher->l = blockCount;

	cipher->c = blocks;
	return cipher;
}
	

	

/*	
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
