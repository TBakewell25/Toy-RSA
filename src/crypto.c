#include <stdlib.h>
#include "../utils/crypto.h"
#include "../utils/types.h"
#include <openssl/rsa.h>
#include <openssl/bn.h>


/*
cipher_t* encrypt(RSA key, char* plaintext);
	RSA* rsaKey = (RSA*) malloc(siezof(RSA));
	rsaKey->	

	if (key.public_key){
		RSA_public_encrypt(int flen, const unsigned char *from,
                       unsigned char *to, RSA *rsa, int padding);
	else{
		
char* decrypt(RSA key, char* cipherText);

*/
