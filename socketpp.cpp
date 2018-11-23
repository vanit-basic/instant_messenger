#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#include "socketpp.hpp"

extern "C" {
	ssize_t read(int fd, void *buf, size_t count);
	int inet_pton(int af, const char *src, void *dst);
	int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	int close (int filedes);
}

socketpp::socketpp(int port, socketType type) {
	this->port = port;
	this->type = type;
	if ((this->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
	}
}

socketpp::~socketpp() {
	close(this->fd);
}

bool socketpp::sconnect() {
	struct sockaddr_in serv_addr; 
	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(this->port); 

	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return false; 
	} 

	if (connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return false; 
	}
	return true;
}

int socketpp::ssend(std::string message) {
	return send(this->fd , message.c_str() , strlen(message.c_str()) , 0 ); 
}

std::string socketpp::sread () {
	int valread = 0;
	std::string result = "";
	char buffer[1024] = {0};
	do {	
		valread = read( this->fd , buffer, 1024);
		if(valread) {
			result.append(buffer, valread);
		}
	} while (valread);
	return result;
}
