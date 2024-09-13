#ifndef RSA_H
#define RSA_H

#include "types.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>


void init_key(rsakey_t* key);


void fill_key(unsigned long l, mpz_t e, mpz_t d, mpz_t n, rsakey_t* key);


void generate_prime(int bits, int k, mpz_t result);

rsakey_t* generateKeys(int bitlength);

cipher_t* encrypt(rsakey_t* rsaKey, const unsigned char* plaintext);

unsigned char* decrypt(rsakey_t* rsaKey, cipher_t* cipher);

#endif
