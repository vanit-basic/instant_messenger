#include <iostream>
#include <unistd.h>
#include "connection.hpp"
#include "verification.hpp"
#include "input.cpp"
#include <mutex>
#include <string>
#include <thread>
std::string for_login="";
std::string fifo1="";
std::string fifo2="";
connection* mainConnection = NULL;
std::string info="";
std::string log="";

void recv_message_c(connection* c, std::string message) {
	std::string msg1="";
	std::string confmsg="";


	if(message.find(":action:send:")!=std::string::npos)
	{
		message.erase(0,13);
		std::string id=message.substr(0,message.find(":"));
		message.erase(0,message.find(":")+1);
		std::cout<<"ID:"<<id<<" send message: "<<message<<std::endl;
	}

	if(message=="<registration> or <sign in>")
	{
		do
		{
			std::cout<<"For registration enter 'registration' , for login enter 'sign in'\n";
			getline(std::cin,msg1);
			if(msg1!="registration" && msg1!="sign in")
				std::cout<<"Wrong action!\n";
		}
		while(msg1!="registration" && msg1!="sign in" &&  msg1!="send" && msg1!="users");
	}

	if(message=="You allowed following action:view user data, send message another user, create a new group, send message to group or quit")
	{
		std::cout<<message<<std::endl;
		do
		{
			std::cout<<"For view users ID enter 'users' , for send message another user enter 'send' , for creat a new group enter 'group' , for send message to group enter 'send group' , for quit enter 'quit'"<<std::endl;
			getline(std::cin,msg1);

			if(msg1!="users" && msg1!="send" && msg1!="group" && msg1!="send group" && msg1!="quit")
				std::cout<<"\tInvalid action\n";

		}
		while(msg1!="users" && msg1!="send" && msg1!="group" && msg1!="send group" && msg1!="quit");


	}


	if(msg1=="users")
		c->send("show users id");


	if(msg1=="send")
	{
		std::string user_id="";
		std::string text="";
		std::cout<<"Enter user id : ";
		getline(std::cin,user_id);
		std::cout<<"Enter message: ";
		getline(std::cin,text);
		std::string sms=":action:send_message:"+user_id+":"+text;
		c->send(sms);
	}

	if(msg1=="registration" )
	{
		info=registr();
		do
		{
			std::cout<<"Login: ";
			getline(std::cin,log);
			if(!isvalid_login(log))
				std::cout<<"Invalid login!\n";
		}
		while(!isvalid_login(log));
		log="login:"+log;
		c->send(log);
	}

	if(message=="Valid login")
	{
		info+=":login:"+log+ ":";
		c->send(info);

	}
	if(message=="Invalid login")
	{
		std::cout<<message<<"Enter login\nLogin: ";
		do
		{
			std::cout<<"Login: ";
			getline(std::cin,log);
			if(!isvalid_login(log))
				std::cout<<"Invalid login!\n";
		}
		while(!isvalid_login(log));
		log="login:"+log;
		c->send(log);

	}
	if(msg1=="sign in")
	{
		c->send(sign_in());
	}
	if(message.substr(0,8)==":return:")
	{
		message.erase(0,8);
		std::cout<<message<<std::endl;
	}

}

void binder_recv_message(connection* c, std::string message) {
	if(message!="q" && message!="")
	{
		fifo1=message.substr(0,message.find(":"));
		fifo2=message.substr(message.find(":")+1);

		mainConnection = new connection(fifo1,fifo2);
		mainConnection->setRecvMessageCallback(recv_message_c);
		mainConnection->send(":action:help:");
	}
}
int main () {
	std::ifstream busy("busy.lock");
	if(busy.is_open())
	{
		while(busy.is_open())
		{
			usleep(10);
		}
	}
	else
	{
		std::ofstream busy1("busy.lock");

		connection binder(std::string("in"),std::string("out"));
		binder.setRecvMessageCallback(binder_recv_message);
		binder.send("first message");
		busy1.close();
		remove("busy.lock");
	}
	while(true){}
	return 0;

}

