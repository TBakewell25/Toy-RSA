#ifndef CRYPTO_H
#define CRYPTO_H

#include "types.h"
#include <openssl/rsa.h>
#include <openssl/bn.h>

cipher_t* encrypt(RSA* key, char* plaintext);

char* decrypt(RSA* key, char* cipherText);

#endif
