#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utils/types.h"
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include <openssl/evp.h>

void writeCipherTextToFile(char* outputFileName, const char* cipherText){
	FILE* outputFile = fopen(outputFileName, "w");
	fprintf(outputFile, cipherText);
	fclose(outputFile);
}


char* readCipherTextFromFile(char* inputFileName){
	FILE* inputFile;
	size_t buff_size;
	char* myString;

	myString = (char*) malloc(sizeof(char)*1024);	
	buff_size = 1024;

	inputFile = fopen(inputFileName, "r");
	fgets(myString, 1024, inputFile);
	fclose(inputFile); 
	
	return myString;
}

void writeKeyToFile(rsakey_t* key, char* filebasename){
	FILE* pubKeyFile = fopen("Name-public.key", "w");
	fprintf(pubKeyFile, "public\n%d\n%d\n%ld\n",key->l, key->e, key->n);
	fclose(pubKeyFile);
	
	FILE* privKeyFile = fopen("Name-private.key", "w");
	fprintf(privKeyFile, "private\n%ld\n%d\n%ld\n",key->l, key->d, key->n);
	fclose(privKeyFile);
	
	
}



RSA* readKeyFromFile(char* filename, unsigned int flag){
	FILE* inputFile;
	RSA* key = RSA_new();
	
	inputFile = fopen(filename, "r");
	
	if (flag)	
		PEM_read_RSAPublicKey(inputFile, &key, NULL, NULL);
	else
		PEM_read_RSAPrivateKey(inputFile, &key, NULL, NULL);
	fclose(inputFile);
	return key;
}

