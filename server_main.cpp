#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <list>
#include "connection.hpp"
#include <unistd.h>
#include <map>
static int i=0;
static std::list<connection*> connections;
static std::map<std::string, std::string> datebase;
void recv_message(connection* c, std::string message) 
{
	std::cout << "from client : "<< c->getId()<<":   " << message << std::endl;
	std::string key = "";
	std::string value = "";
	std::string msg = message;
	msg.erase(0,1);
	while(msg!="")
	{
		key = msg.substr(0, msg.find(':'));
		msg.erase(0, msg.find(':')+1);
		value = msg.substr(0, msg.find(':'));
		msg.erase(0, msg.find(':')+1);
		datebase.emplace(key, value);
	}
/*	std::map<std::string, std::string>::iterator k=datebase.begin();
        for(; k != datebase.end(); ++k)
        {
                std::cout<<k->first<<": "<<k->second<<"\n";
        }
*/
	c->send(message);
}

void recv_message_binder(connection* c, std::string message) 
{
	if(message=="new client")
	{
		std::cout << "client: " << message << std::endl;
		std::string fifo_name1="C" + std::to_string(i);
		std::string fifo_name2="S" + std::to_string(i);
		std::string str;
		i++;
		str = fifo_name1 + ":" + fifo_name2;
		c->send(str);
		c->send("quit");
		connection* s=new connection(fifo_name2, fifo_name1);
		s->setId(fifo_name1);
		s->setRecvMessageCallback(recv_message);
		connections.push_back(s);
	}
}

int main () 
{
	connection binder(std::string("out"), std::string("in"));
	binder.setRecvMessageCallback(recv_message_binder);
	std::list<connection*>::iterator k=connections.begin();
	for(k=connections.begin(); k!=connections.end();++k)
 	{
                delete [](*k);
        }

	return 0;
}
