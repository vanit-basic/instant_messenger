#include <iostream>
#include <unistd.h>
#include <mutex>
#include "connectionAndUser.hpp"
#include "utils.hpp"

static std::map<std::string, std::string> my_information;
static std::string fifo_name1="";
static std::string fifo_name2="";
static std::string id="";
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
		std::getline(std::cin, act);
		while(!(act=="1" ||act=="2" || act=="3"))
		{
			std::cout<<"Invalid action, for registration enter 1, for login enter 2, for quit enter 3"<<std::endl;
			std::cin>>act;
		}
		int act1 = stoi(act);
		switch(act1)
		{
			case 1: 
			{
				std::string inf="";
				std::string actual="";
				std::string pass="";
				std::string mail="";
				std::cout<<"Enter your first name, the name must begin with a capital letter and must contain only letters"<<std::endl;
				std::getline(std::cin, actual);
				while(!isValidName(actual))
				{
					std::cout<<"Invalid first name, please enter new name, the name must begin with a capital letter and must contain only letters"<<std::endl;
					std::getline(std::cin, actual);
				}
				inf = ":FirstName:" + actual;
				std::cout<<"Enter your last name, the name must begin with a capital letter and must contain only letters"<<std::endl;
				std::getline(std::cin, actual);
				while(!isValidName(actual))
				{
					std::cout<<"Invalid last name, please enter new name, the name must begin with a capital letter and must contain only letters"<<std::endl;
					std::getline(std::cin, actual);
				}
				inf =inf + ":LastName:" + actual;
				std::cout<<"Enter your birth date, date of birth must contain only numbers and character '.'(xx.xx.xxxx)"<<std::endl;
				std::getline(std::cin, actual);
				while(!isValidBirthDate(actual))
				{
					std::cout<<"Invalid birth date,please enter new birth date xx.xx.xxxx"<<std::endl;
					std::getline(std::cin, actual);
				}
				inf = inf + ":BirthDate:" + actual;
				std::cout<<"Enter your gender, male or female"<<std::endl;
				std::getline(std::cin, actual);
				while(!isValidGender(actual))
				{
					std::cout<<"Invalid gender, enter male or female"<<std::endl;
					std::getline(std::cin, actual);
				}
				inf = inf + ":Gender:" + actual;
				std::cout<<"Enter your E-mail, Email must contain only numbers, letters and characters '@, ., _, -'"<<std::endl;
				std::getline(std::cin, mail);
				while(!isValidE_mail1(mail))
				{
					std::cout<<"Invalid Email, please enter new Email"<<std::endl;
					std::getline(std::cin, mail);
				}
				inf = inf + ":Email:" + actual;
				std::cout<<"Enter login,login must contain only numbers, letters and characters '@, ., _, -'"<<std::endl;
				std::getline(std::cin, actual);
				if(actual =="")
				{
					actual=mail;
				}
				while (!isValidLogin1(actual))
				{
					std::cout<<"Enter login,login must contain only numbers, letters and characters '@, ., _, -'"<<std::endl;
					std::getline(std::cin, actual);
				}
				inf = inf + ":Login:" + actual;
				std::cout<<"Choose password, password must contain minimum eight, maximum sixteen numbers or letters and must contain minimum one capital letter, one number and one small leter"<<std::endl;
				std::getline(std::cin, actual);
				std::cout<<"Confirm password"<<std::endl;
				std::getline(std::cin, pass);
				while(actual!=pass || (!isValidPassword(actual)))
				{
					std::cout<<"Invalid Password, enter password, password  must contain minimum eight, maximum sixteen numbers or letters and must contain minimum one capital letter, one number and one small leter"<<std::endl;
					std::getline(std::cin, actual);
					std::cout<<"Confirm password"<<std::endl;
					std::getline(std::cin, pass);
				}
				inf =":registration:information" + inf + ":Password:" + actual + ":";
				c->send(inf);
				break;
			}
			case 2:	
			{
				std::string str="";
				std::string msg="";
				std::cout<<"Enter your login"<<std::endl;
				std::getline(std::cin, str);
				msg = ":action:signin:login:" + str + ":";
				std::cout<<"Enter your password"<<std::endl;
				std::getline(std::cin, str);
				msg = msg +"Password:" + str + ":";
				c->send(msg);
				break;
			}
			case 3:
			{	c->send("quit");
				break;
			}
		}
	}
	else
	{
		if((message.find(":Login:INVALID:") >= 0) && (message.find(":Login:INVALID:") < message.size()))
		{
			message = message.erase(message.find(":Login:INVALID:"),15);
			std::string l2="";
			std::cout<<"Such login already exists, enter another login"<<std::endl;
			std::getline(std::cin, l2);
			message=message  + ":Login:" + l2 +":";
			std::cout<<message<<std::endl;
			c->send(message);
		}
		else
		{
			if((message.find(":Email:INVALID:") >= 0) && (message.find(":Email:INVALID:") < message.size()))
			{
				message = message.erase(message.find(":Email:INVALID:"),15);
				std::string l2="";
				std::cout<<"Such Email already exists, enter another Email"<<std::endl;
				std::getline(std::cin, l2);
				message=message  + ":Email:" + l2 +":";
				std::cout<<message<<std::endl;
				c->send(message);
			}

			else
			{
				if((message.find(":your_information:")>=0)&&(message.find(":your_information:")<message.size()))
				{
					std::string msg = message;
					msg = msg.erase(0, 18);
					string_to_map(my_information, msg);
				}

				else
				{
					if(message == "You allowed following action: send message another user, create a new group, send message to group or quit")
					{
						std::string act="";
						std::cout<<"for send message another user enter 1, for creat a new group enter 2,for send message to group enter 3 for quit enter 4"<<std::endl;
						std::getline(std::cin, act);
						while(!(act=="1" ||act=="2" || act=="3" || act=="4"))
						{
							std::cout<<"for send message another user enter 1, for creat a new group enter 2,for send message to group enter 3 for quit enter 4"<<std::endl;
							std::cin>>act;
						}
						int act1 = stoi(act);
						switch(act1)
						{
							case 1: c->send(":action:send_message_anoter_user:");
								break;
							case 2: c->send(":action:creat_a_new_group:");
								break;
							case 3: c->send(":action:send_message_to_group:");
								break;
							case 4:c->send("quit");
							       break;
						}
					}
					else
					{}


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
