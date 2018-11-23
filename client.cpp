#include <stdio.h> 

#include "socketpp.hpp"

int main(int argc, char const *argv[]) 
{ 
	char *hello = "Hello from client"; 
	socketpp soc;
	soc.sconnect();
	soc.ssend(std::string(hello));
	printf("Hello message sent\n"); 
	std::string res = soc.sread();
	printf("%s\n", res.c_str()); 
	return 0; 
} 
