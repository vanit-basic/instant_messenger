#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <list>
#include "connection.hpp"
#include <unistd.h>
#include <map>
#include "user.h"
static int id=0;
static std::string name1;
static std::string name2;
static std::string name3;
static std::list<connection*> connections;

std::map<std::string,std::string> StringtoMap (std::string str){
        str.erase(0,1);
         std::map<std::string,std::string>myMap;
        while(str.length() != 0){
        int pos=str.find(':');
        std::string key="";
        key=str.substr(0,pos);
        str.erase(0,pos+1);
        pos=str.find(':');
        std::string value="";
        value=str.substr(0,pos);
        str.erase(0,pos+1);
        myMap.insert(std::pair<std::string,std::string>(key,value));
        }

        return myMap;

}

void recv_message(connection* c, std::string message) 
{
	std::map<std::string, std::string> myMap;
	std::cout << "from client : "<< c->getId()<<":   " << message << std::endl;
	myMap = StringtoMap(message);
	for(auto  it=myMap.begin();it!=myMap.end();it++){
                std::cout<<it->first<<" : "<<it->second<<std::endl;
        }
	c->send(message);
}

void recv_message_binder(connection* c, std::string message) 
{
	if(message=="new client")
	{
		std::cout << "client: " << message << std::endl;
		name1="C" + std::to_string(id);
		name2="S" + std::to_string(id);
		name3= name1 + ":" +name2;
		id++;
		c->send(name3);
		c->send("q");
		connection* s=new connection(name2,name1);
		s->setId(name1);
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
