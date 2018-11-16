#include <iostream>
#include <unistd.h>
#include <mutex>
#include "connection.hpp"

static std::string name1="";
static std::string name2="";
static std::mutex m;
void recv_message_binder(connection* c, std::string message)
{
	if(message!="q" && message !="")
	{
		m.lock();
		int pos = message.find(':'); 
		int end = message.length() - pos - 1;
		name1 = message.substr(0, pos);
		name2 = message.substr(pos+1 , end);
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
		connection c(name1,name2);
                c.setId(name1);
                m.unlock();
		std::cout<<"Id: "<<c.getId()<<std::endl;
                c.setRecvMessageCallback(recv_message);


	while (true)
	{
		std::string str="";
		std::getline(std::cin,str);
		c.send(str);
		if(str=="q")
		{
			break;
		}
		usleep(1000);
	}
	return 0;
}
