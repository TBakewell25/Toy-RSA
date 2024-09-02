#ifndef RSA_H
#define RSA_H

#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include "types.h"
#include <stddef.h>


#define OPENSSL_API_COMPAT 30000
#define OPENSSL_NO_DEPRECATED

EVP_PKEY* generateKeys(int bitlength);

cipher_t* encrypt(EVP_PKEY* rsaKey, const char* plaintext);
	
#endif
