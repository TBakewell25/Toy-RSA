#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utils/types.h"
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/engine.h>

void writeCipherTextToFile(char* outputFileName, int* cipherText, unsigned int blocksize){
	int i = 0;
	char* letter, buff[50];
	FILE* outputFile = fopen(outputFileName, "w");
	while (i < blocksize-1){
		sprintf(buff, "%d", cipherText[i]);
		fprintf(outputFile, "%s ", buff);
		i++;
	}
	fclose(outputFile);
}

cipher_t* readCipherTextFromFile(char* inputFileName){
	FILE* inputFile;
	size_t buff_size;
	unsigned int* myString;
	cipher_t* cipher;

	cipher = (cipher_t*) malloc(sizeof(cipher_t));
	myString = (int*) malloc(sizeof(int)*1024);	
	buff_size = 1024;

	inputFile = fopen(inputFileName, "r");
	fgets((unsigned char*)myString, 1024, inputFile);
	fclose(inputFile); 
	cipher->c = myString;	
	free(myString);	
	
	return cipher;
}

void writeKeyToFile(rsakey_t* key, char* filebasename){
	FILE* pubKeyFile = fopen("Name-public.key", "w");
	fprintf(pubKeyFile, "public\n%d\n%d\n%ld\n",key->l, key->e, key->n);
	fclose(pubKeyFile);
	
	FILE* privKeyFile = fopen("Name-private.key", "w");
	fprintf(privKeyFile, "private\n%ld\n%d\n%ld\n",key->l, key->d, key->n);
	fclose(privKeyFile);
	
	
}



rsakey_t* readKeyFromFile(char* filename, unsigned int flag){
	FILE* inputFile;
	rsakey_t* key;
	char* text[4];
	int i = 0, j;
	
	inputFile = fopen(filename, "r");
	key =(rsakey_t*) malloc(sizeof(rsakey_t));
	for (j = 0; i < 4; i++){
		text[i] = (char*) malloc(sizeof(char));	
		fgets(text[i], 100, inputFile);
		text[i][strcspn(text[i], "\n")] = 0;
	}	
	
	if (!(strcmp((char*)text[0], "public")))
		key->e = atoi(text[2]);
	
	if (!(strcmp((char*)text[0], "private")))
		key->d = atoi(text[2]);

	key->l = atoi(text[1]);
	key->n = atoi(text[3]);
	
	fclose(inputFile);
	
	return key;
}

