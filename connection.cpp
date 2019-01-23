#include "headers.hpp"

#include <iostream>
#include <string>

std::string Connection::getIp() {
	
}

std::string Connection::getPort() {
	
}

bool Connection::send(const std::string& message) {
        const char* msg = message.c_str();
	int length = strlen( msg);
        int total = 0;
        int n = 0;
        std::cout<<"send length\n";
        send (this->fd, &length, sizeof(length), 0);

        while(total < length)
        {
                std::cout<<"send message\n";
                n = send(this->fd, msg + total, (strlen(msg) - total), 0);
                std::cout<< "n = "<<n<<std::endl;
                if (n == -1)
                {
                        break;
                }
                total = total + n;
                std::cout<< "n = "<<n<<std::endl;
                std::cout<< "total = "<< total <<std::endl;
        }
        return (n==-1 ? false : true);

}

std::string Connection::recive() {
        int length = 0;
        char buf[1024];
        char* message;
        int m = 0;
        m = recv(this->fd, &length, sizeof(length), 0);
        std::cout<<"m =  "<<m<<std::endl;
        std::cout<<"length =  "<<length<<std::endl;
        message = (char*)malloc(length);
        m = 0;
        while (m < length)
        {
                m = recv(this->fd, buf, sizeof(buf), 0);
                strcpy(message, buf);
                std::cout<<"result   "<<message<<std::endl;
                memset(buf, 0, 1024);
        }

	return message;
}

Connection::Connection(const std::string& ip, int port, int n) {
	
} //(ip, port,listen quantity)

Connection::Connection(std::string path, int n) {
	const char* p = path.c_str();
	const char* const socket_name = p;
	int socket_fd = 0;
	struct sockaddr_un name;
	socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
	name.sun_family = AF_LOCAL;
	strcpy(name.sun_path, socket_name);
	if (n == 0)//Local client
	{
		connect(socket_fd, (struct sockaddr*)& name, SUN_LEN(&name));
		this->fd = socket_fd;
	}
	else
	{
		bind(socket_fd, (struct sockaddr*) &name, SUN_LEN (&name));
		listen(socket_fd, n);
		struct sockaddr_un client_name;
		socklen_t client_name_len;
		int client_socket_fd;
		client_socket_fd = accept(socket_fd, (struct sockaddr*) &client_name, &client_name_len);

	}

	
} //(path, listen quantity)

Connection::~Connection() {
	
}

