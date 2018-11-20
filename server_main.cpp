#include <iostream>
#include <list>
#include "connectionAndUser.hpp"
#include "utils.hpp"
#include <unistd.h>
#include <map>

static std::map<std::string, std::string> datebase;
static std::map<std::string, std::string> LogAndPass;
static std::map<std::string, user*> users;
static int i=0;
static int ID=0;
static std::list<connection*> connections;

void recv_message(connection* c, std::string message) 
{
	std::cout << "from client : "<< c->getId()<<":   " << message << std::endl;
	std::string key = "";
	std::string value = "";
	std::string msg = message;
	std::string tests=message;
	if (message==":action:registration:")
	{
		c->send("Enter your information");
	}
	else
	{
		if (message==":action:login:")
		{
		}
		else
		{
			if(message=="quit")
			{
				c->send("quit");
			}
			else
			{
				if((message.find(":registration:information:"))>=0)
				{

					msg.erase(0,1);
					if (test(tests, msg)==true)
					{
						ID++;
						std::string log="";
						std::string pass="";
						msg=message + "Id:" + "user_" + std::to_string(ID) + ":";
						msg.erase(0,26);
						string_to_map_and_log_pass(datebase, msg, log, pass);
						LogAndPass.emplace(log, pass);
						user* u = new user(datebase);
						users.emplace(std::to_string(ID), u);
						c->send("OK");
					}
					else
					{
						c->send(tests);
					}
				}
				else
				{}

			}
		}
	}
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
		s->send("You allowed three action: registration, login or quit");
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
