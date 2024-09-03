#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include "../utils/init_ossl.h"
#include <stddef.h>
#include <string.h>
#include "../utils/types.h"


/*
OSSL_PARAM* genParams(unsigned int bits){
	int primes = 3;
	OSSL_PARAM* params = (OSSL_PARAM*) malloc(sizeof(OSSL_PARAM)*3);
	params[0] = (OSSL_PARAM_construct_uint("bits", &bits));
	params[1] = (OSSL_PARAM_construct_uint("primes", &primes));
	params[2] = OSSL_PARAM_construct_end();
	return params;
}

*/
RSA* generateKeys(unsigned int bitlength){
	RSA* rsa;
	BIGNUM* e;
	
	rsa = RSA_new();
	e = BN_new();
	BN_dec2bn(&e, "3");
	
	RSA_generate_key_ex(rsa, bitlength, e, NULL);	
	BN_free(e);
	return rsa;
}

char* encrypt(RSA* rsaKey, const unsigned char* plaintext, unsigned int encryptFlag){
	unsigned int flen, padding = RSA_PKCS1_PADDING;
	
	flen = strlen(plaintext) +1;
	unsigned char* buff = (unsigned char*) malloc(sizeof(char) * 1000);

	if (encryptFlag == 1)
		RSA_public_encrypt(flen, plaintext, buff, rsaKey, padding);
		
	else
		RSA_private_encrypt(flen, plaintext, buff, rsaKey, padding);

	return buff;
}

char* decrypt(RSA* rsaKey, const unsigned char* ciphertext, unsigned int decryptFlag){
	unsigned int flen, padding = RSA_PKCS1_PADDING;
	
	flen = strlen(ciphertext) +1;
	unsigned char* buff = (unsigned char*) malloc(sizeof(char) * 1000);

	if (decryptFlag == 1)
		RSA_public_decrypt(flen, ciphertext, buff, rsaKey, padding);
		
	else
		RSA_private_decrypt(flen, ciphertext, buff, rsaKey, padding);

	return buff;
}

	
/*
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


char* encrypt(EVP_PKEY* rsaKey, const char* plaintext){
	int len = strlen(plaintext)+1;
	EVP_PKEY_CTX* ctx;
	//ENGINE* eng;
	unsigned const char out[10000];
	unsigned const char* buffer;
	size_t* outl;

	buffer = (char*) malloc(sizeof(char)*10000);
	outl = (size_t*) malloc(sizeof(char) * 10000);
	//eng  = ENGINE_by_id("Wahoowa");

	//ENGINE_init(eng);
	
	ctx= EVP_PKEY_CTX_new(rsaKey, NULL);
	//cipher_t* cipher = (cipher_t*) malloc(sizeof(cipher_t));
		
	EVP_PKEY_encrypt_init(ctx);
	EVP_PKEY_encrypt(ctx, out, outl, plaintext, len);
	strcpy(buffer, out);
	free(outl);
	return buffer;
}



char* decrypt(EVP_PKEY* rsaKey, const char* ciphertext){
	int len = strlen(ciphertext)+1;
	EVP_PKEY_CTX* ctx;
	//ENGINE* eng;
	unsigned const char out[10000];
	unsigned const char* buffer;
	size_t* outl;

	
	int EVP_DecryptInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type, const unsigned char *key, const unsigned char *iv);

	buffer = (char*) malloc(sizeof(char)*10000);
	outl = (size_t*) malloc(sizeof(char) * 10000);
	//eng  = ENGINE_by_id("Wahoowa");

	//ENGINE_init(eng);
	
	ctx= EVP_PKEY_CTX_new(rsaKey, NULL);
	//cipher_t* cipher = (cipher_t*) malloc(sizeof(cipher_t));
		
	EVP_PKEY_decrypt_init(ctx);
	EVP_PKEY_decrypt(ctx, out, outl, ciphertext, len);
	strcpy(buffer, out);
	free(outl);
	return buffer;
}

	

		
*/
