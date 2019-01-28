#ifndef HEADERS_PORC_HPP
#define HEADERS_PORC_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <list>
#include <thread>

class Connection {
        private:
                std::string ip;
                std::string port;
                int socket_server_fd;
                int client_fd;
		std::list<int> socket_client_fd;
		std::thread accp;
        public:
		void Accept(int socket_fd, struct sockaddr* x, socklen_t client_name_len, int n);
		void threadJoin();
                std::string getIp();
                std::string getPort();
		int getClientFd();
		std::list<int> getSocketClientFd();
                bool Send(const std::string&, int);
                std::string Recive(int x);
                Connection(const std::string path,int quantity);//LocalServer,if(quantity == 0) => client,esle => server
                Connection(const std::string& ip, int port, int quantity); //InetServer,if(quantity == 0) => client,esle => server
                Connection(){}
                ~Connection(){}
};

#endif
