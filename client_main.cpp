#include <iostream>
#include <unistd.h>
#include <mutex>
#include "connectionAndUser.hpp"
#include "utils.hpp"

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
	if ("You allowed three action: registration, login or quit"==message)
	{
		std::string act="";
		std::cout<<"for registration enter 1, for login enter 2, for quit enter 3"<<std::endl;
		std::cin>>act;
		while(!(act=="1" ||act=="2" || act=="3"))
		{
			std::cout<<"Invalid action, for registration enter 1, for login enter 2, for quit enter 3"<<std::endl;
			std::cin>>act;
		}
		int act1 = stoi(act);
		switch(act1)
		{
			case 1: c->send(":action:registration:");
				break;
			case 2: c->send(":action:login:");
				break;
			case 3: c->send("quit");
				break;
		}
	}
	else
	{
		if ("Enter your information" == message)
		{
			std::string inf="";
			std::string actual="";
			std::string pass="";
			std::cout<<"Enter your first name, the name must begin with a capital letter and must contain only letters"<<std::endl;
			std::cin>>actual;
			inf = ":FirstName:" + actual;
			std::cout<<"Enter your last name, the name must begin with a capital letter and must contain only letters"<<std::endl;
			std::cin>>actual;
			inf =inf + ":LastName:" + actual;
			std::cout<<"Enter your birth date, date of birth must contain only numbers and character '.'"<<std::endl;
			std::cin>>actual;
			inf = inf + ":BirthDate:" + actual;
			std::cout<<"Enter your gender, male or female"<<std::endl;
			std::cin>>actual;
			inf = inf + ":Gender:" + actual;
			std::cout<<"Enter your E-mail, Email must contain only numbers, letters and characters '@, ., _, -'"<<std::endl;
			std::cin>>actual;
			inf = inf + ":Email:" + actual;
			std::cout<<"Enter login,login must contain only numbers, letters and characters '@, ., _, -'"<<std::endl;
			std::cin>>actual;
			inf = inf + ":Login:" + actual;
			std::cout<<"Choose password, password must contain minimum eight, maximum sixteen numbers or letters and must contain minimum one capital letter, one number and one small leter"<<std::endl;
			std::cin>>actual;
			std::cout<<"Confirm password"<<std::endl;
			std::cin>>pass;
			while(actual!=pass)
			{
				std::cout<<"Password does not match, enter password, password  must contain minimum eight, maximum sixteen numbers or letters and must contain minimum one capital letter, one number and one small leter"<<std::endl;
				std::cin>>actual;
				std::cout<<"Confirm password"<<std::endl;
				std::cin>>pass;
			}
			inf =":registration:information" + inf + ":Password:" + actual + ":";
			c->send(inf);
		}
		else
		{
			if(message.find("INVALID") < 0)
			{
				std::cout<<message<<std::endl;
			}
			else
			{
				if((message.find(":registration:information:"))>=0)
				{
					std::string msg=message;
					msg.erase(0,26);

					while(msg!="")
					{
						std::string key;
						std::string value;
						std::string pass;
						key = msg.substr(0, msg.find(':'));
						msg.erase(0, msg.find(':')+1);
						value = msg.substr(0, msg.find(':'));
						msg.erase(0, msg.find(':')+1);
						if (value=="INVALID")
						{
							std::string attempt="";
							message = message.erase(message.find(key), key.size()+value.size()+2);
							if(key=="Password")
							{
								std::cout<<"INVALID Password, please enter new Password"<<std::endl;
								std::cin>>attempt;
								std::cout<<"Confirm password"<<std::endl;
								std::cin>>pass;
								while(attempt!=pass)
								{
									std::cout<<"Password does not match, enter password"<<std::endl;
									std::cin>>attempt;
									std::cout<<"Confirm password"<<std::endl;
									std::cin>>pass;
								}
							}
							else
							{
								std::cout<<"INVALID "<<key<<", please enter new "<<key<<std::endl;
								std::cin >> attempt;
							}
							message=message + key + ":" + attempt + ":";
						}
					}
					c->send(message);
				}
			}
		}
	}
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

/*
	while (true)
	{

		std::string str="";
		usleep(10000);
		std::cout<<"mutqagreq hraman, cragir@ verjacnelu hamar mutqagreq 'quit'\n";
		std::getline(std::cin,str);
		c.send(str);
		if(str=="quit")
		{
			break;
		}

	}
*/	return 0;
}
