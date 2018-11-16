#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <list>
#include "connection.hpp"
#include <unistd.h>
static int i=0;
static std::list<connection*> connections;// connection-ner parunakox list vortex pahvelu en clientnerin hamapatasxan stexcvac connectionner@

void recv_message(connection* c, std::string message) 
//kardalu hamar te ardyoq client@ inch vor hraman uxarkela te voch nor stexcvac(amen clienti hamar ir) fifo fileri mijocov ev patasxanum e
{
	std::cout << "from client : "<< c->getId()<<":   " << message << std::endl;
	c->send(message);
}

void recv_message_binder(connection* c, std::string message) 
//uxarkuma nor clientin ira hamar sarqac fifo fileri annunner@, ogtagorcvuma binderi poxaren
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
		connection* s=new connection(fifo_name2, fifo_name1);//nor connection-i stexcum@ client avelanalu depqum
		s->setId(fifo_name1);//clientin veragrum e id
		s->setRecvMessageCallback(recv_message);//ashxatacnum e nor clienti hamar stexcvac connection@
		connections.push_back(s);//nor stexcvac connection@ gcum e listi mej
		//uxarkuma "quit", vorpesi client@ haskana vor binder connection@ avartela ira gorc@ ev clienti mot jnji binder connection@
		//qani vor connection.cpp-i mej read() funkciayi nkaragrutyan mej while(true) averj ciklic durs e galis erb handipum e "q"
	}
}

int main () 
{
	connection binder(std::string("out"), std::string("in"));
	binder.setRecvMessageCallback(recv_message_binder);
	std::list<connection*>::iterator k=connections.begin();
	for(k=connections.begin(); k!=connections.end();++k)//cragri verjum jnjum enq stexcvac new connectionner@
        {
                delete [](*k);
        }

	return 0;
}
