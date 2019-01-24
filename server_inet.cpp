#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

int send_all(int new_socket, char* msg) {
        int length = strlen(msg);
        int total = 0;
        int num = 0;
        std::cout << "Sending message's length!" << std::endl;
        send(new_socket, &length, sizeof(length), 0);

        while(total < length) {
                std::cout << "Send message" << std::endl;
		num = send(new_socket, msg + total, strlen(msg) - total, 0 );
		if (num == -1) {
                        break;
                }

                total += num;
	}

        return ((n == -1)? -1: total);
}

int recv_all(int new_socket, int buffer) {
	read(new_socket, buffer, 1024);
        int length;
        char buf[1024];
        char* message;
        int num = 0;

	num = read(new_socket, &length, sizeof(length));
        std::cout << "Number of symbols: " << num << std::endl;
        std::cout << "length: " << length << std::endl;
        message = (char*) malloc(length);
        num = 0;

        while (num < length) {
                num = read(new_socket, buffer, sizeof(buffer));
                strcpy(message, buffer);
                std::cout << "Results: " << message << std::endl;
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
	int port = 8080;
	std::cout << "Enter port: ";
	std::cin >> port;

	int server_fd = 0;
       	int new_socket = 0;
       	int valread = 0;

	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char* msg = "";
	std::cout << "Enter message: " << std::endl;
	std::getline(std::cin, msg);

	int n = 0;
	std::cout << "Enter number of clients: " << std::endl;
	std::cin >> n;

	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	}

	// Attaching socket to the port we enter, else 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	// attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)& address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, n) < 0) { 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	}

	new_socket = accept(server_fd, (struct sockaddr*)& address, (socklen_t*)& addrlen);
	if (new_socket < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	int sending = 0;
	valread = recv_all(new_socket, buffer);
	std::cout << "Buffer: " << buffer << std::endl;
	sending = send_all(new_socket, msg);
	std::cout << "Your message sent!" << std::endl;
	return 0;
}

