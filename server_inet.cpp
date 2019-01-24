#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

int send_all(int socket_fd, char* msg)
{
	int length = strlen(msg);
	int total = 0;
	int n = 0;
	std::cout<<"send length\n";
	send(socket_fd, &length, sizeof(length), 0);

	while(total < length) {
		std::cout<<"send message\n";
		n = send(socket_fd, msg + total, (strlen(msg) - total), 0);
		if (n == -1)
		{
			break;
		}
		total = total + n;
	}
	return (n==-1 ? -1 : total);
}

int recv_all(int socket_fd)
{
	int length;
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
	send_all(socket_fd, (char*) "Staca");
	if (!strcmp(message, "quit"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int main()
{
	const char* path = "/home/narek/socket";
	const char* const socket_name = path;
	int socket_fd;
	struct sockaddr_un name;
	int client_sent_quit_message;

	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);

	name.sun_family = AF_LOCAL;
	strcpy(name.sun_path, socket_name);
	bind(socket_fd, (struct sockaddr*) &name, SUN_LEN (&name));
	listen(socket_fd, 6);

	do
	{
		struct sockaddr_un client_name;
		socklen_t client_name_len;
		int client_socket_fd;
		client_socket_fd = accept(socket_fd, (struct sockaddr*) &client_name, &client_name_len);
		client_sent_quit_message = recv_all(client_socket_fd);
		close (client_socket_fd);
	}
	while (!client_sent_quit_message);
	
	//close(socket_fd);
	//unlink(socket_name);
	
	return 0;
}
