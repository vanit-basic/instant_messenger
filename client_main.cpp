#include <iostream>
#include <unistd.h>
#include <mutex>
#include "connection.hpp"

static std::string fifo_name1="";
static std::string fifo_name2="";
static std::mutex m;
void recv_message_binder(connection* c, std::string message)//funkcian kardum e serveri sarqac ev uxarkac fifo fileri anunner@
{
	if(message!="quit" && message !="")
	{
		m.lock();
		//ktrum enq stacvac message qani vor server@ stexcvac erku fileri anunner@ uxarkum e miasin
		fifo_name1=message.substr(0, message.find(':'));
		fifo_name2=message.substr((message.find(':')+1), message.find(':'));
		m.unlock();
	}
}

void recv_message(connection* c, std::string message)
//nor stexcvac connectioni hamar grvac funkcian e, vor@ kardum e serveri koxmic uxarkvac patasxan@
{
	std::cout << "from server : " << message << std::endl;
}

int main () 
{
	std::ifstream busy("busy.lock");//stexcum enq lock file vorpesi konflikt chlini erku clienti miajamanak mianalu jamanak
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
		std::ofstream busy1("busy.lock");//ete chka urish client arden kpac serverin stexcum enq lock file
		connection binder(std::string("in"), std::string("out"));
		//binder connectionn e vor@ serverin texekacnume e vor nor client e avelacel
		binder.setId("Client");
		binder.send("new client");
		binder.setRecvMessageCallback(recv_message_binder);

		busy1.close();
		remove("busy.lock");// jnjum enq lock file-@ vorpesi myus clientner@ hnaravorutyun stanan mianalu serverin
	}
		//stexcum enq nor connection arden stacac concret ays clienti hamar fifo fileri mijocov
                m.lock();
		connection c(fifo_name1, fifo_name2);
                c.setId(fifo_name1);//veragrum enq clientin hamapatasxan id-in
                m.unlock();
		std::cout<<"Id: "<<c.getId()<<"\n";
                c.setRecvMessageCallback(recv_message);//ashxatecnum enq nor stexcvac connection@


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
