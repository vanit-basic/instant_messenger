#include "headers.hpp"

#include <iostream>
#include <string>

std::string Connection::getIp() {
        return this->ip;
}

std::string Connection::getPort() {
        return this->port;
}

bool Connection::Send(const std::string& message, int socket_client_fd) {

        const char* msg = message.c_str();
        int length = strlen( msg);
        int total = 0;
        int n = 0;
        //std::cout<<this->socket_client_fd<<" : socket client fd send \n";
        //send (socket_client_fd, &length, sizeof(length), 0);
        while(total < length)
        {
                n = send(socket_client_fd, msg + total, (strlen(msg) - total), 0);
                if (n == -1)
                {
                        break;
                }
                total = total + n;
        }
        return (n==-1 ? false : true);
}

std::string Connection::Recive(int client_fd) {

        char* message;
        int length = 0;
        char buf[1024];
        int m = 0, n = 0;
        memset(buf, 0, 1024);
        //n = recv(client_fd, &length, sizeof(length), 0);
        message = (char*)malloc(2048 );
        //n=1;
        while (1)
        {
                n = recv(client_fd, buf, 1024, 0);
                //std::cout<<"n =  "<<n<<"\n";
                if (n==0)
                        break;
                strcpy(message, buf);
                std::cout<<"message =  "<<message<<"\n";
                memset(buf, 0, 1024);
                //m += n;
        }
        return message;
}

Connection::Connection(const std::string& ip, int port, int n) {

} //(ip, port,listen quantity)

std::list<int> Connection::getSocketClientFd()
{
        return this->socket_client_fd;
}

int Connection::getClientFd()
{
        return this->client_fd;
}

Connection::Connection( const std::string path, int n) //(path, listen quantity)
{
        int quantity = 0;
        const char* p = path.c_str();
        const char* const socket_name = p;
        int socket_fd = 0;
        struct sockaddr_un name;
        socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
        this->socket_server_fd = socket_fd;
        name.sun_family = AF_LOCAL;
        strcpy(name.sun_path, socket_name);
        //Local Client
        if (n == 0)
        {
                connect(socket_fd, (struct sockaddr*)& name, SUN_LEN(&name));
                this->client_fd = socket_fd;
        }
        //Local Server
        else
        {
                bind(socket_fd, (struct sockaddr*) &name, SUN_LEN (&name));
                listen(socket_fd, n);
                struct sockaddr_un client_name;
                socklen_t client_name_len;
                int client_socket_fd;
                while (quantity<n)
                {
                        client_socket_fd = accept(socket_fd, (struct sockaddr*) &client_name, &client_name_len);
                        this->socket_client_fd.push_back(client_socket_fd);
                        quantity++;
                }
        }
}

