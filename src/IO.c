#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utils/types.h"
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/engine.h>

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

/*
void writeKeyToFile(EVP_PKEY* rsakey, char* filebasename){
	if (RSA_get0_e(rsakey)){
		char* filename = strcat(filebasename, "-public.key");
		FILE* keyFile = fopen(filename, "w");
		fprintf(keyFile,"private\n%d\n%s\n%s\n", 10, *RSA_get0_e(key), *RSA_get0_d(key));
		fclose(keyFile);
	}
}


EVP_PKEY* readKeyFromFile(char* filename){
	FILE* inputFile;
	char line[66];
	char** rsa_info = malloc(sizeof(char*) * 5);
	int counter = 0;
	

	EVP_PKEY* rsaKey = (EVP_PKEY*) malloc(sizeof(EVP_PKEY);
	inputFile = fopen(filename, "r");
	
	while(fgets(line, sizeof(char)*65, inputFile) != NULL){
		char* lineSpace = malloc(sizeof(line));
		memcpy(lineSpace, line, sizeof(line));
		memset(line, 0, sizeof(char)*66);
		rsa_info[counter] = lineSpace;
		counter++;
	}
	int bit_len = atoi(rsa_info[1]);	
	if (strcmp((rsa_info[0]), "public") == 0){
		//rsaKey->bit_length = &bit_len;
		rsaKey->e = (rsa_info[2]);
		rsaKey->n = (rsa_info[4]);
			
	}
	else{
		//rsaKey->bit_length = &bit_len; 
		rsaKey->d = (rsa_info[3]);
		rsaKey->n = (rsa_info[4]);	
	}
	free(rsa_info);
	//fclose(inputFile); causes invalid free()
	
	return rsaKey;
}

*/
