#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

/* Read text from the socket and print it out. Continue until the
   socket closes. Return nonzero if the client sent a "quit"
   message, zero otherwise. */
void write_text (int socket_fd)
{
	const char* text = "Staca";
        // Write the number of bytes in the string, including NUL-termination.
        int length = strlen (text) + 1;
        write (socket_fd, &length, sizeof (length));
        // Write the string.
        write (socket_fd, text, length);
}

int server (int client_socket)
{
	while (1) {
		int length;
		char* text;
		
		if (read (client_socket, &length, sizeof (length)) == 0)
		{
			return 0;
		}
		text = (char*) malloc (length);

		read (client_socket, text, length);
		printf ("%s\n", text);
		write_text(client_socket);

		if (!strcmp(text, "quit"))
		{
			free (text);
			return 1;
		}
		free (text);
	}
}
int main ()
{
	const char* p= "/home/narek/Documents/Tnayin/instant_messenger/socket";
	const char* const socket_name = p;
	int socket_fd;
	struct sockaddr_un name;
	int client_sent_quit_message;

	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);

	name.sun_family = AF_LOCAL;
	strcpy (name.sun_path, socket_name);
	bind (socket_fd,(struct sockaddr*) &name, SUN_LEN (&name));

	listen (socket_fd, 5);
	
	do {
		struct sockaddr_un client_name;
		socklen_t client_name_len;
		int client_socket_fd;

		client_socket_fd = accept (socket_fd, (struct sockaddr*) &client_name, &client_name_len);

		client_sent_quit_message = server (client_socket_fd);

		close (client_socket_fd);
	}
	while (!client_sent_quit_message);
	close (socket_fd);
	unlink (socket_name);
	return 0;
}
