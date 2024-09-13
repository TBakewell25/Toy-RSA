#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utils/rsa.h"
#include "../utils/types.h"

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
	unsigned char* myString;
	cipher_t* cipher;

	cipher = (cipher_t*) malloc(sizeof(cipher_t));
	myString = malloc(sizeof(char)*1024);	
	buff_size = 1024;

	inputFile = fopen(inputFileName, "r");
	fgets(myString, 1024, inputFile);
	fclose(inputFile); 
	cipher->c =(int*) myString;	
	free(myString);	
	
	return cipher;
}

void writeKeyToFile(rsakey_t* key, char* filebasename){
	FILE* pubKeyFile = fopen("Name-public.key", "w");
	fprintf(pubKeyFile, "public\n%d\n", key->l);
	
	
	mpz_out_str(pubKeyFile, 10, key->e);
	fprintf(pubKeyFile, "\n");
	mpz_out_str(pubKeyFile, 10, key->n);

	fclose(pubKeyFile);
	
	FILE* privKeyFile = fopen("Name-private.key", "w");
	
	fprintf(privKeyFile, "private\n%d\n", key->l);
	
	mpz_out_str(privKeyFile, 10, key->d);
	fprintf(privKeyFile, "\n");	
	mpz_out_str(privKeyFile, 10, key->n);

	fclose(privKeyFile);
	
	
}


rsakey_t* readKeyFromFile(char* filename){
	FILE* inputFile;
	rsakey_t* key;
	char* text, size[5];
	int j, i =0;
	mpz_t tmp[3];
	
	inputFile = fopen(filename, "r");

	//tmp = (mpz_t*) malloc(sizeof(mpz_t) * 3);
	key =(rsakey_t*) malloc(sizeof(rsakey_t));
	text = (char*) malloc(sizeof(char) * 10);

	fgets(text, 10, inputFile);
	fgets(size, 5, inputFile);
	
	for (j = 0; i < 3; i++){
		mpz_init(tmp[i]);
		mpz_inp_str(tmp[i], inputFile, 10);
		
	}	
	init_key(key);
	fill_key(atoi(size), tmp[0], tmp[1], tmp[2], key);
	
	fclose(inputFile);
	
	return key;
}
