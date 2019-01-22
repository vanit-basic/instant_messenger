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
	std::cout<<"Write skizb\n";
	// Write the number of bytes in the string, including NUL-termination. 
	int length = strlen (text) + 1;
	write (socket_fd, &length, sizeof (length));
	// Write the string.
	write (socket_fd, text, length);
	std::cout<<"Write verj\n";
}
int server (int client_socket)
{
        int length;
        if (!(read (client_socket, &length, sizeof (length)) == 0)) {
	std::cout<<"While\n";
                char* text;
                /* First, read the length of the text message from the socket. If
                   read returns zero, the client closed the connection. */
               /* if (read (client_socket, &length, sizeof (length)) == 0)
                {
                        return 0;
                }*/
                /* Allocate a buffer to hold the text.*/
                text = (char*) malloc (length);
                // Read the text itself, and print it.

                read (client_socket, text, length);
                //if(!text=="")
                printf ("%s\n", text);
                /* Free the buffer. */

                /* If the client sent the message "quit," we're all done.*/
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
		// Create the socket. 
		socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
		// Store the server's name in the socket address.
		name.sun_family = AF_LOCAL;
		strcpy (name.sun_path, socket_name);
		// Connect the socket.
		connect (socket_fd, (struct sockaddr*)&name, SUN_LEN (&name));
		// Write the text on the command line to the socket.
		write_text (socket_fd, message);
		server(socket_fd);
		close (socket_fd);
	}
	//remove("/home/narek/Documents/Tnayin/instant_messenger/socket");
	return 0;

}
