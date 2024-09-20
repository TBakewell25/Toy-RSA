#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include "../utils/rsa.h"
#include "../utils/types.h"

void writeCipherTextToFile(char* outputFileName, mpz_t* cipherText, unsigned int blocksize){
	int i = 0;

	FILE* outputFile = fopen(outputFileName, "w");
	
	while (i < blocksize){
		mpz_out_str(outputFile,10, cipherText[i]);
		fprintf(outputFile, "\n");
		i++;
	}
	fclose(outputFile);
}

cipher_t* readCipherTextFromFile(char* inputFileName){
	FILE* inputFile;
	size_t buff_size;
	int i = 0;
	mpz_t encrypted[10];
	cipher_t* cipher;

	cipher = (cipher_t*) malloc(sizeof(cipher_t));
	inputFile = fopen(inputFileName, "r");

	for (int i = 0; i < 5; i++){
		mpz_init(encrypted[i]);
		mpz_inp_str(encrypted[i], inputFile, 10);
		i++;
	}

	fclose(inputFile); 
	cipher->c = encrypted;	
	
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
	
	init_key(key);

	if (strcmp(text, "public") == 0){
		for (j = 0; i < 3; i++){
			mpz_init(tmp[i]);
			mpz_inp_str(tmp[i], inputFile, 10);
		}
		fill_key(atoi(size), NULL, tmp[0], tmp[1], key);

	}

	else{
		for (j = 0; i < 2; i++){
			mpz_init(tmp[i]);
			mpz_inp_str(tmp[i], inputFile, 10);
		}
		fill_key(atoi(size), tmp[0], NULL, tmp[1], key);

	}
		
			
	fclose(inputFile);
	
	return key;
}
