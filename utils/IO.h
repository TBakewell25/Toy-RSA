#ifndef IO_H
#define IO_H

#include <openssl/rsa.h>
#include <openssl/bn.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "types.h"

void* writeCipherTextToFile(void* outputFileName, const char* cipherText);

char* readCipherTextFromeFile(char* inputFileName);

void* writeKeyToFile(EVP_PKEY* key, char* filebasename);

EVP_PKEY* readKeyFromFile(char* filename);
	
#endif
