#include <iostream>
#include <unistd.h>

#include "connection.hpp"

connection* main_connection = NULL;

void recv_message_c(connection* c, std::string message) {
	std::cout << "Sent " << message << " to " << c->getID() << std::endl;
	c->send("Hello!");
}

void recv_message(connection* c, std::string message) {
	std::cout << "Sent " << message << " to " << c->getID() << std::endl;
	size_t pos = message.find(":");
	if(std::string::npos != pos) {
		std::string in = message.substr(0, pos);
		std::string out = message.substr(pos + 1);
		std::cout << in << ":" << out << std::endl;
		main_connection = new connection(in, out);
		main_connection->setRecvMessageCallback(recv_message_c);
		main_connection->setID(message);
		main_connection->send(message);
	}
}


int main () {

	connection binder(std::string("in"), std::string("out"));
	binder.setID("BINDER_CLIENT");
	binder.setRecvMessageCallback(recv_message);
	binder.send("connect");
	while(true) usleep(100000);	
	return 0;
}
