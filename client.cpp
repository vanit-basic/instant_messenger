#include <iostream>
#include <unistd.h>
#include "connection.hpp"
#include "verification.hpp"
#include "input.cpp"
#include <mutex>
#include <string>
#include <thread>
#include <map>
std::string for_login="";
std::string fifo1="";
std::string fifo2="";
connection* mainConnection = NULL;
std::string info="";
std::string log="";
std::string quit="";
std::map<std::string,std::string> my_info;
std::string reg_sign_in()
{
	std::string msg1="";
	do
	{
		std::cout<<"For registration enter 'registration' , for login enter 'sign in'\n";
		getline(std::cin,msg1);
		if(msg1!="registration" && msg1!="sign in")
			std::cout<<"Wrong action!\n";
	}
	while(msg1!="registration" && msg1!="sign in");
	return msg1;
}
void registration(connection* c)
{
	do
	{
		std::cout<<"Login: ";
		getline(std::cin,log);
		if(!isvalid_login(log))
			std::cout<<"Invalid login!\n";
	}
	while(!isvalid_login(log));
	log=":login:"+log;
	c->send(log);
}
void action_send(std::string message)
{
	message.erase(0,13);
	std::string id=message.substr(0,message.find(":"));
	message.erase(0,message.find(":")+1);
	std::cout<<"ID:"<<id<<" send message: "<<message<<std::endl;
}
void invalid_login(std::string message,connection* c)
{
	std::cout<<message<<" Enter login\n";
	do
	{
		std::cout<<"Login: ";
		getline(std::cin,log);
		if(!isvalid_login(log))
			std::cout<<"Invalid login!\n";
	}
	while(!isvalid_login(log));
	log=":login:"+log;
	c->send(log);
}
void recv_message_c(connection* c, std::string message) {
	std::string msg1="";
	std::string confmsg="";
	if(message.find(":action:send:")!=std::string::npos)
		action_send(message);

	if(message=="<registration> or <sign in>")
		msg1=reg_sign_in();

	if(message=="action")
		std::thread* t=new std::thread(input,c);

	if(message=="Valid login")
		c->send(info+log+":");

	if(message=="Invalid login")
		invalid_login(message,c);

	if(message.substr(0,8)==":return:")
	{
		message.erase(0,8);
		std::cout<<message<<std::endl;
	}
	if(message.substr(0,6)=="myinfo")
	{
		message.erase(0,6);
		my_info=string_to_map(message);
		setmap(my_info);
	}

	if(message=="return 0")
		quit="quit";

	if(msg1=="sign in")
		c->send(sign_in());

	if(msg1=="registration" )
	{
		info=registr();
		registration(c);
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
	while(true)
	{
		if(quit=="quit")
			return 0;
	}
	return 0;

}

