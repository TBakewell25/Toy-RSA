#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include "../utils/init_ossl.h"
#include <stddef.h>
#include <string.h>
#include "../utils/types.h"



OSSL_PARAM* genParams(unsigned int bits){
	int primes = 3;
	OSSL_PARAM* params = (OSSL_PARAM*) malloc(sizeof(OSSL_PARAM)*3);
	params[0] = (OSSL_PARAM_construct_uint("bits", &bits));
	params[1] = (OSSL_PARAM_construct_uint("primes", &primes));
	params[2] = OSSL_PARAM_construct_end();
	return params;
}

	

EVP_PKEY*  generateKeys(int bitlength){
	EVP_PKEY* pkey = NULL;
	EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_from_name(NULL, "RSA", NULL);

	EVP_PKEY_keygen_init(pctx);
	
	OSSL_PARAM* params = genParams(bitlength);
	EVP_PKEY_CTX_set_params(pctx, params);

	EVP_PKEY_CTX_set_rsa_keygen_bits(pctx, bitlength);
	
	EVP_PKEY_keygen_init(pctx);
	EVP_PKEY_generate(pctx, &pkey);
	return pkey;
}


cipher_t* encrypt(EVP_PKEY* rsaKey, const char* plaintext){
	int len = strlen(plaintext)+1;
	EVP_PKEY_CTX* ctx;
	ENGINE* eng;
	unsigned char out[1000];
	size_t* outl;

	memset(out, 0, sizeof(char) *1000);
	outl = (size_t*) malloc(sizeof(char) * 1000);
	eng  = ENGINE_by_id("Wahoowa");

	ENGINE_init(eng);
	
	ctx= EVP_PKEY_CTX_new(rsaKey, NULL);
	cipher_t* cipher = (cipher_t*) malloc(sizeof(cipher_t));
		
	EVP_PKEY_encrypt_init(ctx);
	EVP_PKEY_encrypt(ctx, out, outl, plaintext, len);
	cipher->c = out;
	return cipher;
}

	

		

