#include <iostream>
#include <unistd.h>
#include "connection.hpp"
#include <mutex>
#include <string>
std::string fifo1="";
std::string fifo2="";
connection* mainConnection = NULL;

void recv_message_c(connection* c, std::string message) {
	std::cout << "From server : " << message << std::endl;
	std::cout<<"Nermuceq hraman\n";
	std::getline(std::cin,message);	
	std::string msg=":action:user:name:Valod:email:valod_valodyan@mail.ru:gender:male:";
	c->send(msg);
}

void binder_recv_message(connection* c, std::string message) {
	std::cout<<message<<"\n";
	if(message!="q" && message!="")
	{
	fifo1=message.substr(0,message.find(":"));
	fifo2=message.substr(message.find(":")+1);
	std::cout<<fifo1<<"  "<<fifo2<<"\n";

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
