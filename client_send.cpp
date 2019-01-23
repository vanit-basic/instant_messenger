#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

int send_all(int socket_fd, const char* msg)
{
        int length = strlen(msg);
        int total = 0;
        int n = 0;
        std::cout<<"send length\n";
        send (socket_fd, &length, sizeof(length), 0);

        while(total < length)
        {
                std::cout<<"send message\n";
                n = send(socket_fd, msg + total, (strlen(msg) - total), 0);
		std::cout<< "n = "<<n<<std::endl;
		if (n == -1)
                {
                        break;
                }
                total = total + n;
		std::cout<< "n = "<<n<<std::endl;
		std::cout<< "total = "<< total <<std::endl;
        }
        return (n==-1 ? -1 : total);
}

int recv_all(int socket_fd)
{
        int length = 0;
        char buf[256];
        char* message;
        int m = 0;
        m = recv(socket_fd, &length, sizeof(length), 0);
        std::cout<<"m =  "<<m<<std::endl;
        std::cout<<"length =  "<<length<<std::endl;
        message = (char*)malloc(length);
        m = 0;
        while (m < length)
        {
                m = recv(socket_fd, buf, sizeof(buf), 0);
                strcpy(message, buf);
                std::cout<<"result   "<<message<<std::endl;
                memset(buf, 0 , 256);
        }
        std::cout<<"Whileic heto result = "<<message<<std::endl;
        //send_all(socket_fd, "Staca");
        if (!strcmp(message, "quit"))
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

int main() {
	const char* path = "/home/narek/socket";
	const char* const socket_name = path;
	std::string msg = "";
	while (!(msg == "quit")) {
		std::cout << "Enter the message:" << std::endl;
		std::getline(std::cin, msg);
		const char* message = msg.c_str();
		int socket_fd = 0;
		struct sockaddr_un name;
		socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
		name.sun_family = AF_LOCAL;
		strcpy(name.sun_path, socket_name);
		connect(socket_fd, (struct sockaddr*)& name, SUN_LEN(&name));
		std::cout << "send all)" << std::endl;
		std::cout << send_all(socket_fd, message) << std::endl;
		recv_all(socket_fd);
		//close(socket_fd);
	}

	return 0;


}
