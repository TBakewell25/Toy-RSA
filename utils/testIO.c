#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"
#include "types.h"

int main(int argc, char** argv){
	char* fileName = argv[1];
	struct key_t* killme = readKeyFromFile(fileName);
	
	return 0;
}
	
