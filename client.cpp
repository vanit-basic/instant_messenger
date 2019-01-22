#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <string>
// Write TEXT to the socket given by file descriptor SOCKET_FD.

void write_text (int socket_fd, const char* text)
{
	// Write the number of bytes in the string, including NUL-termination. 
	int length = strlen (text) + 1;
	write (socket_fd, &length, sizeof (length));
	// Write the string.
	write (socket_fd, text, length);
}
int server (int client_socket)
{
        int length;
        if (!(read (client_socket, &length, sizeof (length)) == 0)) {
                char* text;
                text = (char*) malloc (length);

                read (client_socket, text, length);
                printf ("%s\n", text);

                if (!strcmp(text, "quit"))
                {
                        free (text);
                        return 1;
                }
                free (text);
        }
}

int main (/*int argc, char* const argv[]*/)
{
	const char* p = "/home/narek/Documents/Tnayin/instant_messenger/socket";
	const char* const socket_name = p;
	std::string  m="";
	while (! (m == "quit"))
	{
		std::cout<<"Mutqagreq uxarkvox informacian\n";
		std::cin>>m;
		const char* message = m.c_str();
		int socket_fd;
		struct sockaddr_un name;
		socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
		name.sun_family = AF_LOCAL;
		strcpy (name.sun_path, socket_name);
		connect (socket_fd, (struct sockaddr*)&name, SUN_LEN (&name));
		write_text (socket_fd, message);
		server(socket_fd);
		close (socket_fd);
	}
	return 0;

}
