#include <iostream>
#include <unistd.h>
#include "connection.hpp"
#include "validation.hpp"

connection* mainConnection = NULL;
std::string info = ":action:registration";
std::string temp = "";

void recv_message(connection* c, std::string message)  {
	int a = 0;
	if(message == "Sign in(Enter 1) or Registration(Enter 2)") {
		std::string s1 = "";
		while(true){
		std::cin >> s1;
		if(s1 == "1" || s1 == "2") {
			c->send(s1);
			break;
		}
	}
	}
	if(message == "Enter your info") {
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
			std::cout << "Enter password : " << "\n";
			std::cin >> temp;
			if(valid_password(temp)) {
				info = info + ":Password:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter login : " << "\n";
			std::cin >> temp;
			if(valid_login(temp)) {
				std::string stri = ":Login:" + temp;
				c->send(temp);	
				break;
			}
		}
	}
		if(message == "Invalid_Login") {
			while(!valid_login(temp)) {
                        std::cout << "Enter login : " << "\n";
                        std::cin >> temp;
			c->send(temp);
			}
		}
		if(message == "Valid_Login") {
			info = info + ":Login:" + temp;
			c->send(info);
		}
}

void binder_recv_message(connection* c, std::string message) {
	size_t pos = message.find(":");
	static int Id = 0;
	std::cout << "Sent : " << message  << std::endl;
	if(message != "q" && message != "")
	{
		std::string name1 = message.substr(0, message.find(":"));

		std::string name2 = message.substr(message.find(":")+1);

		mainConnection = new connection(name1, name2);
		mainConnection -> setRecvMessageCallback(recv_message);
		mainConnection -> send("help");
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
