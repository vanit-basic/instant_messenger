#include <string.h>
#include <openssl/sha.h>
#include <iostream>

bool simpleSHA256(void* input, unsigned long length, unsigned char* md)
{
    SHA256_CTX context;
    if(!SHA256_Init(&context))
        return false;

    if(!SHA256_Update(&context, (unsigned char*)input, length))
        return false;

    if(!SHA256_Final(md, &context))
        return false;

    for (int i = 0; i < 32; i++) {
	    printf("%02x", md[i]);
    }
    return true;
}

int main (int argc , char** argv) {
	if(argc < 2) {
		std::cout << "Invalid arguments\n";
		return -1;
	}
	unsigned char md[SHA256_DIGEST_LENGTH]; // 32 bytes
	if(!simpleSHA256(argv[1], strlen(argv[1]), md))
	{
		// handle error
	}

	return 0;
}
