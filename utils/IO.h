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

char* readCipherTextFromFile(char* inputFileName);

void* writeKeyToFile(RSA* key, char* filebasename);

RSA* readKeyFromFile(char* filename, unsigned int flag);
	
#endif
