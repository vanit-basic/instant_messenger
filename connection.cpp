#include "headers.hpp"

#include <iostream>
#include <string>

std::string Connection::getIp() {
	return this->ip;
}

std::string Connection::getPort() {
	return this->port;
}

bool Connection::Send(const std::string& message) {
        const char* msg = message.c_str();
	int length = strlen( msg);
        int total = 0;
        int n = 0;
	std::cout<<this->socket_client_fd<<" : socket client fd send \n";
	std::cout<<send (this->socket_client_fd, &length, sizeof(length), 0)<<"\n";
        while(total < length)
        {
                n = send(this->socket_client_fd, msg + total, (strlen(msg) - total), 0);
                if (n == -1)
                {
                        break;
                }
                total = total + n;
        }
        return (n==-1 ? false : true);
}

std::string Connection::Recive() {
	int length = 0;
	char buf[1024];
	memset(buf, 0, 1024);
	char* message;
	int m = 0, n = 0;
	n = recv(this->socket_client_fd, &length, sizeof(length), 0);
	message = (char*)malloc(length + 1);
	while (m < length)
	{
		m = recv(this->socket_client_fd, buf, 1024, 0);
		strcpy(message, buf);
		memset(buf, 0, 1024);
		m = m + n;
	}
	return message;
}

Connection::Connection(const std::string& ip, int port, int n) {
	
} //(ip, port,listen quantity)

Connection::Connection( const std::string path, int n) //(path, listen quantity)
{
	const char* p = path.c_str();
	const char* const socket_name = p;
	int socket_fd = 0;
	struct sockaddr_un name;
	socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
	name.sun_family = AF_LOCAL;
	strcpy(name.sun_path, socket_name);
	//Local Client
	if (n == 0)
	{
		connect(socket_fd, (struct sockaddr*)& name, SUN_LEN(&name));
		this->socket_client_fd = socket_fd;
	}
	//Local Server
	else
	{
		bind(socket_fd, (struct sockaddr*) &name, SUN_LEN (&name));
		listen(socket_fd, n);
		struct sockaddr_un client_name;
		socklen_t client_name_len;
		int client_socket_fd;
		client_socket_fd = accept(socket_fd, (struct sockaddr*) &client_name, &client_name_len);
		this->socket_client_fd = client_socket_fd;
		this->socket_server_fd = socket_fd;
	}
} 
