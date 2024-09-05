#ifndef RSA_H
#define RSA_H

#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include "types.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#define OPENSSL_API_COMPAT 30000
#define OPENSSL_NO_DEPRECATED

rsakey_t* generateKeys(int bitlength);

unsigned char* encrypt(rsakey_t* rsaKey, const unsigned char* plaintext);

unsigned char* decrypt(rsakey_t* rsaKey, const unsigned char* ciphertext);

#endif
