#include <openssl/evp.h>
#include <openssl/core.h>

OSSL_PARAM* init_ossl(void* args){
	OSSL_PARAM* params = malloc(sizeof(OSSL_PARAM));
	
	params->key = NULL;  // Example parameter
	params->data_type = OSSL_PARAM_UTF8_STRING;
	params->data = NULL;  // Set this to NULL for automatic allocation
	params->data_size = 0; 

	return params;
}
