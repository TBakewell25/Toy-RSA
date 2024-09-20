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
	if (e)
		mpz_set(key->e, e);
	if(d)
		mpz_set(key->d, d);
	mpz_set(key->n, n);
}

void generate_prime(int bits, int k, mpz_t result){
	int count, iterations, i;
	mpz_t n, a, num, tmp, j, l;
	
	gmp_randstate_t state;
    	gmp_randinit_mt(state);  // Initialize state
	
	mpz_inits(n, a, num, tmp, j, l, NULL);

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

/*
void generate_prime(int bits, int k, mpz_t result){
	mpz_t prime;

	mpz_init(prime);	
	gmp_randstate_t state;
    	gmp_randinit_mt(state);  // Initialize state


	while(1){
     		mpz_urandomb(prime, state, bits);
     		if (!mpz_probab_prime_p(prime, 50))
          		break;
	}
	mpz_set(result, prime);

}

*/


rsakey_t* generateKeys(int bitlength){
	mpz_t p ,q, e, d, n, tmp;

	mpz_inits(n, p, q, e, d, tmp, NULL);
	
	rsakey_t* key;

	generate_prime(bitlength, 50, p);
	generate_prime(bitlength, 50, q);
	
		
	mpz_mul(n, p, q);
	generate_prime(bitlength -1, 50, e);
	
	mpz_invert(d, e, n);
	
	//mpz_out_str (stdout, 10, n);
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
	char* retString = (char*) malloc(sizeof(char)*size+1);
    

	memcpy(retString, string + base, size);
    
	retString[size] = '\0';

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
		sprintf(tmp, "%03d", buff[i]);
		strcat(encoded, tmp);
	}
	return encoded;
}


		
cipher_t* encrypt(rsakey_t* key, char* plaintext){
	unsigned int size, blocksize, j, i =0, blockCount = 0;
	int newBlock;
	mpz_t n, m, e, *blocks, tmp;
	char *encoded, *block; 
	cipher_t* cipher;

	mpz_inits(n, e, NULL);
	mpz_set(n, key->n);
	mpz_set(e, key->e);

	size = strlen(plaintext);
	encoded = encode(plaintext, size);

	blocksize = (int)floor(mpz_sizeinbase(n, 10)/3.32);
	blocks = malloc(sizeof(mpz_t) * size);
		
	cipher = malloc(sizeof(cipher_t));
	
	for (j = 0; j < size-6; j += 6){
		mpz_inits(tmp,m, blocks[i], NULL);

		block = strSplit(encoded, j, j + 6);
		newBlock = atoi(block);
		
		mpz_init_set_ui(m, newBlock);
		mpz_out_str(stdout, 10, m);	
		
		//mpz_set_ui(n, 387);
		mpz_powm(tmp, m, e, n);
		mpz_set(blocks[i], tmp);
	
		mpz_clear(tmp);
		mpz_clear(m);
		blockCount++;
		i++;
		
	}
	cipher->l = blockCount;

	cipher->c = blocks;
	free(encoded);
	return cipher;
}
	


void decrypt(rsakey_t* key, cipher_t* cipher){
	mpz_t n, d, *encrypted, tmp;
	int blocks = 4, i;
	char decoded[256];

	mpz_inits(n,d, NULL);

	encrypted = cipher->c;
	
	
	//d = key->d;
	//n = key->n;

	for (i = 0; i < blocks; i++){
		mpz_inits(tmp, n, NULL);
		mpz_set_ui(n, 387);
		mpz_powm(tmp, encrypted[i], key->d, n);

		mpz_clears(n, tmp, NULL);
	
	}
	//return decoded;
}
		
