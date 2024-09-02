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


char* readCipherTextFromeFile(char* inputFileName){
	FILE* inputFile;
	
	inputFile = fopen(inputFileName, "r");
	char* myString = malloc(sizeof(char) * 100);
	fgets(myString, 100, inputFile);
	fclose(inputFile); 
	
	return myString;
}

void writeKeyToFile(EVP_PKEY* rsaKey, char* filebasename){
	//char* filename = strcat(filebasename, "-public.key");
	FILE* keyFile = fopen("Output.pem", "w");
	PEM_write_PUBKEY(keyFile, rsaKey);
	fclose(keyFile);
}



EVP_PKEY* readKeyFromFile(char* filename){
	FILE* inputFile;
	EVP_PKEY* key = EVP_PKEY_new();
	inputFile = fopen(filename, "r");
	
	PEM_read_PUBKEY(inputFile, &key, NULL, NULL);	
	fclose(inputFile);
	return key;
}

