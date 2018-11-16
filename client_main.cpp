#include <iostream>
#include <string>
#include <unistd.h>
#include <mutex>
#include "connection.hpp"

static std::mutex mt;
static std::string c_pipe = "";
static std::string s_pipe = "";

void recv_message_binder(connection* c, std::string message) {
	std::cout << "Sent " << message << std::endl;
	if (("q" != message) &&  ("" != message)) {
		mt.lock();
		c_pipe = message.substr(0, message.find(":"));
		s_pipe = message.substr(message.find(":") + 1);
		std::cout << c_pipe << "  " << s_pipe << "\n";
		mt.unlock();
	}
}

void recv_message(connection* c, std::string message) {
	std::cout << "The server sent: " << message << std::endl;
}

int main () {
	
	std::ifstream access_possibility("access.lock");
        if (access_possibility.is_open()) {
                while (access_possibility.is_open())
                        usleep(100);
        }
        else {
		usleep(1000);
                std::ofstream access_posibility("access.lock");
		connection binder(std::string("in"), std::string("out"));
		binder.setID("Client");
		binder.send("New client");
		binder.setRecvMessageCallback(recv_message_binder);
		access_possibility.close();
		remove("access.lock");
	}

	mt.lock();
	connection client(c_pipe, s_pipe);
	client.setID(c_pipe);
	std::cout << "ID " << client.getID() << std::endl;
	client.setRecvMessageCallback(recv_message);
	mt.unlock();

	while (true) {
		std::string command;
		std::cout << "Enter the command (q - for quit)\n";
		getline(std::cin, command);
		client.send(command);
		if ("q" == command) {
			break;
		}
		usleep(1000);
	}
	return 0;
}
