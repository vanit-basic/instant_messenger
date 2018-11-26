#include "connection.hpp"

#include <iostream>
#include <unistd.h>

connection* mainConnection = NULL;
std::string info = ":action:registration";
std::string temp = "";

void recv_message(connection* c, std::string message)  {
	int a = 0;
	std::cout<<"Server : "<< message <<std::endl;
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
	if(message == "Ok") {
		c->send("help");
	}
	if(message == "Enter login and password") {
		std::string forPass = "";
		std::string forLoginPass = "";
		std::cout << "Login : ";
		std::cin >> temp;
		std::cout << "Password : ";
		std::cin >> forPass;
		forLoginPass = "Sign-in:" + temp + ":" + forPass;
		c->send(forLoginPass);	

	}
	if(message == "Enter your info") {
		while(true) {
			std::cout << "Enter Firstname(Valod) : ";
			std::cin >> temp;
			if(valid_name(temp) == true) {
				info = info +  ":FirstName:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter Lastname(Valodyan) : ";
			std::cin >> temp;
			if(valid_name(temp)) {
				info = info + ":LastName:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter Gender(male or female) : ";
			std::cin >> temp;
			if(valid_gender(temp)) {
				info = info + ":Gender:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter Birthdate(25-12-1999) : ";
			std::cin >> temp;
			if(valid_birthdate(temp)) {
				info = info + ":BirthDate:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter email : ";
			std::cin >> temp;
			if(valid_mail(temp)) {
				info = info + ":Email:" + temp;
				break;
			}
		}
		std::string examp = "";
		while(true) {
			std::cout << "Enter password : ";
			std::cin >> examp;
			if(valid_password(examp)) {
				break;
			}
		}
		while(true) {
			std::cout << "Enter password : ";
			std::cin >> temp;
			if(valid_password(temp) && temp == examp) {
				info = info + ":Password:" + temp;
				break;
			}
		}
		while(true) {
			std::cout << "Enter login : ";
			std::cin >> temp;
			if(valid_login(temp)) {
				std::string stri = ":Login:" + temp;
				c->send(stri);	
				break;
			}
		}
	}
	std::string stri="";
	if(message == "Invalid_Login") {
		do
		{
			std::cout << "Enter login : ";
			std::cin >> temp;
			stri = ":Login:" + temp;
		}
		while(!valid_login(temp));
		c->send(stri);

	}
	if(message == "Valid_Login") {
		info = info + ":Login:" + temp + ":";
		c->send(info);
	}
	if(message == "For send message to user enter 3, for create new group enter 4, for send message to group enter 5") {
		std::string s1 = "";
		std::cin >> s1;
		c->send(s1);
	}
	if(message.substr(0,4) ==":Id:" ) {
			std::string mess = "";
			std::cout << " Sent message -> User Id:Message" << "\n";
			std::cin >> mess;
			c->send(mess);
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
