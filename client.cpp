#include <iostream>
#include "connection.hpp"
#include <string>
#include <fstream>
#include <unistd.h>
#include <mutex>
#include <thread>
#include "validations.hpp"


std::string clientServer="";
std::string serverClient="";

connection* main1= NULL;
std::string userData ="";
std::string data = ""; 


void recvMessageFromServer(connection* c, std::string message)
{
	int action = 0; 


	if (message == "Hello, for registration enter 1, to sign in enter 2, to quit enter 3")
	{	std::cout << "Hello, for registration enter 1, to sign in enter 2, to quit enter 3" << std::endl; 
		std::cin >> action; 
		while (!(action == 1 || action == 2 || action == 3))
		{
			std::cout << "Please enter valid action" << std::endl; 
			std::cin >> action; 
		}

		if (1 == action)
		{
			std::cout << "Enter your first name" << std::endl; 
			std::cin.ignore(); 
			std::getline(std::cin,data); 
			while(! isValidFirstName(data)){
		//		std::cout<<"data == "<<data<<std::endl;
				std::cout << "Please enter your name correctly" << std::endl; 
				std::getline(std::cin,data);
			}

			
			userData = ":firstName:" + data; 
			std::cout << "Enter your last name" << std::endl; 
			std::getline(std::cin,data); 
			while(!isValidLastName(data))
			{
				std::cout << "Please enter your lastname correctly" << std::endl; 
				std::getline(std::cin, data);
			}
			userData += ":lastName:" + data; 

			std::cout << "Enter your birthday like this dd.mm.yyyy" << std::endl; 
			std::getline(std::cin, data); 
			while(!isValidBirthDate(data))
			{
				std::cout << "Be sure to enter your birthday in correct format like dd.mm.yyyy" << std::endl;
				std::getline(std::cin, data); 	
			}
			userData += ":birthDate:" + data; 

			std::cout << "Enter your gender" << std::endl; 
			std::getline(std::cin, data); 
			while(!isValidGender(data))
			{
				std::cout << "Please enter either male or female" << std::endl; 
				std::getline(std::cin, data); 
			}
			userData += ":gender:" + data;

			std::cout << "Enter your E_mail" << std::endl; 
			std::getline(std::cin, data); 
			while(!isValidEmail(data))
			{
				std::cout << "Be sure to enter a valid E_mail" << std::endl; 
				std::getline(std::cin, data);
			}
			data = ":E-mail:" + data; 

			c->send(data); 

			std::cout << "Enter your login" << std::endl;
			std::getline(std::cin, data);

			while(!isValidLogin(data))
			{
				std::cout << "Please enter another login" << std::endl;
				std::getline(std::cin, data);
			}

			data = ":login:" + data; 
			c->send(data);

			std::cout << "Enter your password" << std::endl;
			std::getline(std::cin, data);
			std::string password = "";
			std::cout << "Confirm your password" << std::endl;
			std::getline(std::cin, password);
			while (data != password || !(isValidPassword(data)))
			{
				std::cout << "password should contain at least one capital letter, and at least one number" << std::endl;
				std::getline(std::cin, data);
				std::string password = "";
				std::cout << "Confirm your password" << std::endl;
				std::getline(std::cin, password);
			}

			userData += ":password:" + data; 
		}
		if (message == "false")
		{
			std::cout << "Please enter other email, this one is already busy" << std::endl; 
			std::getline(std::cin, data);
			while(!email(data))
			{
				std::cout << "Be sure to enter a valid E_mail" << std::endl;
				std::getline(std::cin, data);
			}
			data = ":E_mail:" + data;
			c->send(data);

		}
		if (message == "true") 
		{
			userData += data;
		}


		if (message == "falseLog")
		{
			std::cout << "This login already exists, enter other one" << std::endl; 
			std::getline(std::cin, data);
			while (!login(data))
			{
				std::cout << "login is busy, enter another login" << std::endl;
				std::getline(std::cin, data);
			}
			data = ":login:" + data;
			c->send(data);
		}

		if (message == "trueLog")
		{
			userData += data;
		
userData = ":registrationInfo:" + userData + ":";
		c->send(userData); 
	}

}
}
void recvMessage(connection* c, std::string message)
{
	std::cout<<"client_binder :"<<message<<std::endl;
	if(message!="q" && message!="")
	{

		clientServer=message.substr(0,message.find(":"));
		serverClient=message.substr(message.find(":")+1);
		main1 =new connection(clientServer,serverClient);
		main1->setRecvMessageCallback(recvMessageFromServer);
		main1->send("Hello");
	}
}


int main()
{
	std::ifstream binder_lock("binder.lock");
	if(binder_lock.is_open())
	{
		while (binder_lock.is_open())
		{
			usleep(10);
		}
	}
	else
	{
		connection c(std::string("in"),std::string("out"));
		c.setRecvMessageCallback(recvMessage);
		c.send("new client");
		binder_lock.close();
		remove("binder.lock");
	}


	while(true){}
	return 0;
}


