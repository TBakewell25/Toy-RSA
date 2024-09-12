#ifndef TYPES_H
#define TYPES_H
#include <gmp.h>
typedef struct {
	unsigned int l;
	mpz_t e;
	mpz_t d;
	mpz_t  n;
}rsakey_t;

typedef struct {
	unsigned int* c;
	int l;
	int b;
}cipher_t;




#endif
