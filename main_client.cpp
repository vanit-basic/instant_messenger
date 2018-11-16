#include <iostream>
#include <unistd.h>
#include "connection.hpp"
connection* mainConnection = NULL;
void recv_message(connection* c, std::string message)  {
	std::cout << "Sent : " << message  << std::endl;
	std::string command;
	std::cin >> command;
	c -> send(command);
}

void binder_recv_message(connection* c, std::string message) {
	size_t pos = message.find(":");
	std::cout << "Sent : " << message  << std::endl;
	if(message != "q" && message != "")
	{
		std::string name1 = message.substr(0, message.find(":"));

		std::string name2 = message.substr(message.find(":")+1);

		mainConnection = new connection(name1, name2);
		mainConnection -> setRecvMessageCallback(recv_message);
		mainConnection -> send("Hello");
	}
}

int main () {
	std::ifstream busy("busy.lock");
	if(busy.is_open())
	{
		while (busy.is_open())
		{
			usleep(10);
		}
	}
	else
	{
		std::ofstream busy1("busy.lock");
		connection binder(std::string("in"),std::string("out"));
		binder.setId("Client");
		binder.setRecvMessageCallback(binder_recv_message);
		binder.send("new_client");
		busy1.close();
		remove("busy.lock");
	}
	while(true){}
	return 0;
}
