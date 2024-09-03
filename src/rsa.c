#include <stddef.h>
#include <string.h>
#include "../utils/types.h"

rsakey_t* denerateKeys(const unsigned int bitlength){
	unsigned int p, q, n = 0, e;
	rsakey_t* key;
	size_t block_length;

	p = generate_prime(bitlength, 10);
	q = generate_prime(bitlength, 10);

	while(n+1 > (n  - 10)){
		n = generate_prime(bitlength, 20);
	}
	e = n;

	if (key = malloc(sizeof(rsakey_t)) != 0){
		printf("BAD MALLOC");
		return NULL;
	}

	key->bit_length = &bitlength;
	key->public_key = &e;
	key->private_key = &d;
	key->modulus = &n;
	
	return key;
}
	

	

	

	

