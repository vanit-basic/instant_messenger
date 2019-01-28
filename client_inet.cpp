#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

int sendAll (int& sock, char* &msg) {
	int length = strlen(msg);
        int total = 0;
        int num = 0;
	num = send(sock, &msg, sizeof(length), 0);
        std::cout << "send length"<<num<< std::endl;

        while(total < length) {
		num = send(sock, msg + total, strlen(msg) - total, 0);
                std::cout << "number of sending symbols: " << num << std::endl;
                if (num == -1){
                        break;
                }

                total = total + num;
                std::cout<< "number of sending symbols: " << num << std::endl;
                std::cout<< "total: "<< total << std::endl;
        }

        return ((num == -1)? -1: total);
}

int recvAll(int sock, char* buffer) {
        int length = 0;
        char buf[1024];
        char* message;
        int num = 0;

        num = read(sock, buffer, 1024);
        std::cout << "number of symbols: " << num << std::endl;
        std::cout << "length:  " << length << std::endl;
        message = (char*) malloc(length);
        num = 0;

        while (num < length) {
        	num = read(sock, buffer, 1024);
                strcpy(message, buffer);
                std::cout << "result: " << message << std::endl;
                memset(buffer, 0 , 1024);
        }

        std::cout << "Finaly results: " << message << std::endl;
        if (!strcmp(message, "quit")) {
                return 1;
        } else {
		return 0;
        }
}

int main(int argc, char const *argv[]) {
	struct sockaddr_in address;
       	int valread = 0;
	struct sockaddr_in serv_addr;

	char buffer[1024] = {0};
	int port = 8080;
//	std::cout << "Enter port number:" << std::endl;
//	std::cin >> port;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		std::cout << "Socket creation error!" << std::endl;
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		std::cout << "Invalid address or Address not supported!!!";
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "Connection Failed!!!" << std::endl;
		return -1;
	}

	std::string msg = "";
	std::string quit = "quit";
	while (!(strcmp(msg.c_str(), quit.c_str()) == 0)) {
		std::cout << "Enter message!" << std::endl;
		std::getline(std::cin, msg);
		char* message = (char*)msg.c_str();
		while (sendAll(sock, message) == -1) {
			std::cout << "Sending..." << std::endl;
		}
		std::cout << "Your message sent!!!" << std::endl;
		
		valread = recvAll(sock, buffer);
		if (valread == 0) {
			std::cout << "Buffer: " << buffer << std::endl;
			return 0;
		}
	}
}
