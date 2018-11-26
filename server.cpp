#include <list>
#include "connection.hpp"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <map>
#include "validations.hpp"
#include <string>

typedef std::map<std::string, std::string> Map;
static int i = 0;

std::list<connection*> connections;

Map emailId;
Map allData; 
std::map <std::string, std::pair<std::string, std::string>> logPassId;


void recvMessageFromClient (connection* c, std::string message)
{

	if (message == "Hello")
	{
		message == "Hello, for registration enter 1, to sign in enter 2, to quit enter 3 ";	

		c->send(message);
	}

	if (message.find(":login:", 0, 7))
	{
		message.erase(0,7); 
		if(login(message) == false); 
		{
			c->send("false");
		}
		if(login(message) == true)
		{
			c->send("true"); 
		}
	}
	if (message.find(":E_mail:", 0, 8))
			{
			message.erase(0,8); 
			if (email(message) == false)
			{
			c->send("falseLog");
			}
			if (email(message) == true)
			{
			c->send("trueLog");
			}
			}


			if (message.find(":registrationInfo:", 0, 18))	
				{
				message.erase(0,18);
				allData = myMap(message);
				logPassId.emplace(allData["login"],std::make_pair(allData["Id"],allData["password"]));
				emailId.emplace(allData["E_mail"], allData["Id"]);
				}	

		}
void recvMessage (connection* c, std::string message)
				{
				if(message=="new client")
				{
				std::cout << "client: " << message << std::endl;
				std::string clientServer = "Client" + std::to_string(i);  
				std::string serverClient = "Server" + std::to_string(i);

				i++;

				connection* c1 = new connection(serverClient, clientServer);
				c1->setRecvMessageCallback(recvMessageFromClient);
				connections.push_back(c1);
				clientServer = clientServer+":"+serverClient;
				c->send(clientServer);
				c->send("q");
				}
				}

int main () {


	connection binder(std::string("out"),std::string("in"));
	binder.setRecvMessageCallback(recvMessage);

	std::list<connection*>::iterator it=connections.begin();

	for(it=connections.begin(); it!=connections.end();++it)
	{
		delete [](*it);
	}
	return 0;
}

