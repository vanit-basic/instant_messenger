#include <iostream>
#include <unistd.h>
#include "connection.hpp"
#include "validation.hpp"
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
//		mainConnection -> send("Hello");
	}
	int a = 0;
	std::cout << "For login enter 1, for registration enter 2" << "\n";
	std::cin >> a;
	if(a == 2) {
		std::string info = "";
		std::string temp = "";
		while(true) {
			std::cout << "Enter Firstname(Valod) : " << "\n";
			std::cin >> temp;
			if(valid_name(temp) == true) {
				info = ":FirstName:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter Lastname(Valodyan) : " << "\n";
			std::cin >> temp;
			if(valid_name(temp)) {
				info = info + ":LastName:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter Gender(male or female) : " << "\n";
			std::cin >> temp;
			if(valid_gender(temp)) {
				info = info + ":Gender:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter Birthdate(25-12-1999) : " << "\n";
			std::cin >> temp;
			if(valid_birthdate(temp)) {
				info = info + ":BirthDate:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter email : " << "\n";
			std::cin >> temp;
			if(valid_mail(temp)) {
				info = info + ":Email:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter login : " << "\n";
			std::cin >> temp;
			if(valid_login(temp)) {
				info = info + ":Login:" + temp;
				break;
			}

		}
		c->send(info);
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
