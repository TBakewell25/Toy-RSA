#ifndef RSA_H
#define RSA_H

#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include "types.h"
#include <stddef.h>


#define OPENSSL_API_COMPAT 30000
#define OPENSSL_NO_DEPRECATED

RSA* generateKeys(int bitlength);

char* encrypt(RSA* rsaKey, const char* plaintext, const unsigned int flag);

char* decrypt(RSA* rsaKey, const char* ciphertext);

#endif
