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

void writeKeyToFile(RSA* rsaKey, char* filebasename){
	//char* filename = strcat(filebasename, "-public.key");
	
	FILE* pubKeyFile = fopen("OutputPub.pem", "w");
	PEM_write_RSAPublicKey(pubKeyFile, rsaKey);
	fclose(pubKeyFile);
		
	FILE* privKeyFile = fopen("OutputPriv.pem", "w");
	PEM_write_RSAPrivateKey(privKeyFile, rsaKey, NULL,
                            NULL, 0,
         		    NULL , NULL);
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

