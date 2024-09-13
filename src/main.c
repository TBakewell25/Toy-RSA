#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/rsa.h"
#include "../utils/IO.h"
//#include "../utils/convert.h"
//#include "../utils/prime.h"
#include "../utils/types.h"

int main(int argc, char** argv){
	int showPandQ, verbose = 0;	
	char* outputFileName = "output.txt";
	char* inputFileName = "input.txt";
	char* keyName = "default";
	
	int i = 1;
	while (i < argc){
		if (strcmp("-verbose", argv[i]) == 0){
			verbose = 1;
		}
		
		if(strcmp("-output", argv[i]) == 0){
			i++;
			outputFileName = argv[i];
		}
		
		if(strcmp("-input", argv[i]) == 0){
			i++;
			inputFileName = argv[i];
		}


		if(strcmp("-key", argv[i]) == 0){
			i++;
			keyName = argv[i];
		}
	
		if(strcmp("-showpandq", argv[i]) == 0)
			showPandQ = 1;
	
		if(strcmp("-keygen", argv[i]) == 0){
			i++;
			int bitLength = atoi(argv[i]);
			rsakey_t* key = generateKeys(bitLength);
			writeKeyToFile (key, keyName);
		}
		if(strcmp("-encrypt", argv[i]) == 0){
			//char* fileName = strcat(keyName, "-public.key");
		
			rsakey_t* key = readKeyFromFile("Name-public.key");
			cipher_t* cipherText = encrypt(key, "hello there, testing an encrypted output");
			writeCipherTextToFile(outputFileName, cipherText->c, cipherText->l);
		}

/*
		if(strcmp("-decrypt", argv[i]) == 0){
			//char* fileName = strcat(keyName, "-public.key");
			rsakey_t* key = readKeyFromFile("Name-private.key");

			cipher_t* cipherText = readCipherTextFromFile("output.txt");
			char* plaintext = decrypt(key, cipherText);
			writeCipherTextToFile("test.txt", plaintext);
		}
	*/	/*	
		if(strcmp("-sign", argv[i]) == 0){
			char* fileName = strcat(keyName, "-private.key");
			//char* key = readKeyFromFile(fileName);
			//char* plaintext = readFile(inputFilename);
			//char* signature = sign(key,plaintext);
			//char* signed = strcat(inputFileName, ".sign");
			//writeCipherTextToFile(signed, signature);
		}	
		if(strcmp("-checksign", argv[i]) == 0){
			char* fileName = strcat(keyName, "-public.key");
			//char* key = readKeyFromFile(fileName);
			//char* plaintext = readFile(inputFileName);
			//char* signed = strcat(inputFileName, ".sign");

			//char* signature = readCipherTextFromFile(signed)
			//char* result = checkSign(key,plaintext,signature)
			//if (!result)
				//printf("Signatures do not match!");
		}
		if(strcmp("-crack", argv[i]) == 0){
			char* fileName = strcat(keyName, "-public.key");
			//char* key = readKeyFromFile(fileName);
			//char* cracked = crack(key);
			//void* crackedFileName = strcat(keyName, "-cracked");
			//writeKeyToFile(cracked, crackedFileName);
		}
	
		if(strcmp("-seed", argv[i]) == 0){
			int seed = atoi(argv[++i]);
			//random.seed(seed); //find c implementation
		}
		
		else{
			printf("Unknown parameter: %s, exiting.", argv[i]);
		*/	

		i++;

	}
	return 0;
}
