#include <iostream>
#include <unistd.h>
#include <mutex>
#include "connection.hpp"

static std::string fifo_name1="";
static std::string fifo_name2="";
static std::mutex m;
void recv_message_binder(connection* c, std::string message)
{
	if(message!="quit" && message !="")
	{
		m.lock();
		fifo_name1=message.substr(0, message.find(':'));
		fifo_name2=message.substr((message.find(':')+1), message.find(':'));
		m.unlock();
	}
}

void recv_message(connection* c, std::string message)
{
	std::cout << "from server : " << message << std::endl;
}

int main () 
{
	std::ifstream busy("busy.lock");
	if(busy.is_open())
	{
		while(busy.is_open())
		{
			usleep(1000);
		}
	}
	else
	{
		usleep(1000);
		std::ofstream busy1("busy.lock");
		connection binder(std::string("in"), std::string("out"));
		binder.setId("Client");
		binder.send("new client");
		binder.setRecvMessageCallback(recv_message_binder);

		busy1.close();
		remove("busy.lock");
	}
                m.lock();
		connection c(fifo_name1, fifo_name2);
                c.setId(fifo_name1);
                m.unlock();
		std::cout<<"Id: "<<c.getId()<<"\n";
                c.setRecvMessageCallback(recv_message);


	while (true)
	{
		std::string str="";
		std::cout<<"mutqagreq hraman, cragir@ verjacnelu hamar mutqagreq 'quit'\n";
		std::getline(std::cin,str);
		c.send(str);
		if(str=="quit")
		{
			break;
		}
		usleep(1000);
	}
	return 0;
}
