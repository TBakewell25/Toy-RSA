#ifndef TYPES_H
#define TYPES_H

typedef struct {
	unsigned int* bit_length;
	char* public_key;
	char* private_key;
	int* modulus;
}rsakey_t;

typedef struct {
	unsigned char* c;
	int l;
	int b;
}cipher_t;




#endif
