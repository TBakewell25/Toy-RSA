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

cipher_t* readCipherTextFromFile(char* inputFileName);

void* writeKeyToFile(rsakey_t* key, char* filebasename);

rsakey_t* readKeyFromFile(char* filename);
	
#endif
