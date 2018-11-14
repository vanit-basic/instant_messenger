#include <iostream>
#include <list>
#include <unistd.h>
#include "connection.hpp"

static int clients_count = 0;
std::list<connection*>* connections;
connection* b = NULL;

void create_new_connection(std::string in, std::string out);

void recv_message(connection* c, std::string message);

std::string parse_message(std::string msg) {
	std::string response = "";
	if(msg == "connect") {
		std::string in = "in_";
		in += std::to_string(clients_count);
		response += ":";
		std::string out = "out_";
		out += std::to_string(clients_count);
		response = in + ":" + out;
		create_new_connection(out, in);
		std::cout << "new connection created" << std::endl;
		clients_count++;
	}
	return response;
}
void create_new_connection(std::string in, std::string out) {
	connection *newC = new connection(in, out);
	connections->push_back(newC);
	newC->setID(std::to_string(clients_count));
	newC->setRecvMessageCallback(recv_message);
}

void recv_message(connection* c, std::string message) {
	std::cout << "From " << c->getID() << " " << message << std::endl;
	c->send(c->getID());
}

void recv_message_binder(connection* c, std::string message) {
	std::cout << "From client " << message << std::endl;
	message = parse_message(message);
	c->send(message);
	c->unbind();
}

int main () {

	connection binder(std::string("out"), std::string("in"));
	binder.setID("SERVER_BINDER");
	binder.setRecvMessageCallback(recv_message_binder);
	b = &binder;
	connections = new std::list<connection*>;
	
	return 0;
}
