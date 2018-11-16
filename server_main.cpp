#include <iostream>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/stat.h>
#include "connection.hpp"

static int i = 1;
static std::string str = "";
static std::list<connection*> c_list;

void recv_message(connection* c, std::string message) {
        std::cout << "The client sent (" << c->getID() << ") " << message << std::endl;
        c->send(message);
}

void recv_message_binder(connection* c, std::string message) {
	if ("New client" == message) {
		std::cout << "Client: " << message << std::endl;
		std::string c_pipe = "C" + std::to_string(i);
		std::string s_pipe = "S" + std::to_string(i);
		i++;
		std::cout<<c_pipe<<"   "<<s_pipe<<"\n";

		str = c_pipe + ":" + s_pipe;
		c->send(str);
		c->send("q");

		connection * connect = new connection(s_pipe, c_pipe);
		connect->setID(c_pipe);
		connect->setRecvMessageCallback(recv_message);
		c_list.push_back(connect);

	}
}

int main () {
	connection binder(std::string("out"), std::string("in"));
	binder.setRecvMessageCallback(recv_message_binder);
	std::list<connection*>::iterator it = c_list.begin();
	for (it = c_list.begin(); it != c_list.end(); ++it) {
		delete [] (*it);
	}
	return 0;
}
