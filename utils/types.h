#ifndef TYPES_H
#define TYPES_H

typedef struct {
	unsigned int l;
	unsigned int e;
	unsigned int d;
	unsigned long n;
}rsakey_t;

typedef struct {
	unsigned int* c;
	int l;
	int b;
}cipher_t;




#endif
