#include <iostream>
#include <unistd.h>
#include <mutex>
#include <list>
#include <iterator>
#include "connectionAndUser.hpp"
#include "utils.hpp"

static std::map<std::string, std::string> my_information;
static std::map<std::string, std::string> users_inf;
static std::list<std::thread*> threads;
static std::string fifo_name1="";
static std::string fifo_name2="";
static std::string id="";
static std::mutex m;
static std::mutex m1;
void registration (connection* c)
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
	std::cout<<"Enter your birth date, date of birth must contain only numbers and character '.'(dd.mm.yyyy)"<<std::endl;
	std::getline(std::cin, actual);
	while(!isValidBirthDate(actual))
	{
		std::cout<<"Invalid birth date,please enter new birth date dd.mm.yyyy"<<std::endl;
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
	inf = inf + ":Email:" + mail;
	std::cout<<"Enter login,login must contain only numbers, letters and characters '@, ., _, -'"<<std::endl;
	std::getline(std::cin, actual);
	if(actual =="")
	{
		actual=mail;
	}
	while (!isValidLogin1(actual))
	{
		std::cout<<"Invalid login,login must contain only numbers, letters and characters '@,., _, -'"<<std::endl;
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
}
void login(connection* c)
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
}
void reg_login_quit(connection* c)
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
			{ registration(c);
				break;
			}
		case 2:
			{	login(c);
				break;
			}
		case 3:
			{       c->send("quit");
				break;
			}
	}
}
void sender(connection* c)
{
	m1.lock();
	std::string act="";
	std::cout<<"for view users data enter 1 for send message another user enter 2, for creat a new group enter 3,for send message to group enter 4, for quit enter 5"<<std::endl;
	std::getline(std::cin, act);
	while(!(act=="1" ||act=="2" || act=="3" || act=="4" || act=="5" || act == "6"))
	{
		std::cout<<"for view users data enter 1 for send message another user enter 2, for creat a new group enter 3,for send message to group enter 4, for quit enter 5"<<std::endl;
		std::cin>>act;
	}
	int act1 = stoi(act);
	switch(act1)
	{
		case 1:{
			if(!users_inf.empty())
			{
				print_map(users_inf);
			}
			else
			{std::cout<<"No users logged in yet"<<std::endl;}
			c->send(":return1:");
			break;
		       }

		case 2:{
			if(!users_inf.empty())
			{
			       std::string us_id="";
			       std::string us_msg="";
			       std::cout<<"Enter the User Id to whom you want to send a message, or q for cancel"<<std::endl;
			       print_map(users_inf);
			       std::getline(std::cin, us_id);
			       while(!(isValidUser(users_inf, us_id) || us_id =="q"))
			       {
				       std::cout<<"Invalid User, enter the User Id from the list"<<std::endl;
				       print_map(users_inf);
				       std::getline(std::cin, us_id);
			       }
			       if(us_id == "q")
			       {
			       		c->send("return1");
			       }
			       else
			       {
			       std::cout<<"Enter the message"<<std::endl;
			       std::getline(std::cin, us_msg);
			       us_msg=":send_message_user:userId:" + us_id +":my_Id:" +my_information["Id"] + ":message:" + us_msg + ":";
			       c->send(us_msg);
			       }
			}
			else
			{std::cout<<"No users logged in yet, update users data"<<std::endl;
			c->send(":return1:");
			}
			break;
		       }
		case 3:{
			c->send(":action:creat_a_new_group:");
			break;
		       }
		case 4:{
			       c->send(":action:send_message_to_group:");
			       break;
		       }
		case 5:{
			       c->send("quit");
			       break;
		       }
	}
m1.unlock();
}
void update_users_data(std::string message, connection* c)
{
	std::string us_inf = message;
	std::string us_name = "";
	std::string us_id = "";
	us_inf = us_inf.erase(0, 19);
	while(!(us_inf==""))
	{
		us_inf = us_inf.erase(0, 5);
		us_name = us_inf.substr(0, us_inf.find(':'));
		us_inf = us_inf.erase(0, us_inf.find(':')+4);
		us_id = us_inf.substr(0, us_inf.find(':'));
		us_inf = us_inf.erase(0, us_id.size()+1);
		users_inf.emplace(us_id, us_name);
	}
	c->send(":return1:");
}
void invalidEmailOrLogin(std::string message, connection* c)
{
	std::string msg = message;
	std::string l2="";
	if(!(message.find(":Email:INVALID:") == std::string::npos))
	{
		msg = msg.erase(msg.find(":Email:INVALID:")+1,14);
		std::cout<<"Such Email already exists, enter another Email"<<std::endl;
		std::getline(std::cin, l2);
		while(!isValidE_mail1(l2))
		{
			std::cout<<"Invalid E-mail, enter new Email, Email must contain only numbers, letters and characters '@, ., _, -'"<<std::endl;
			std::getline(std::cin, l2);
		}

		msg=msg  + "Email:" + l2 +":";
	}
	if(!(message.find(":Login:INVALID:") == std::string::npos))
	{
		msg = msg.erase(msg.find(":Login:INVALID:")+1,14);
		std::cout<<"Such login already exists, enter another login"<<std::endl;
		std::getline(std::cin, l2);
		while(!isValidLogin1(l2))
		{
			std::cout<<"Invalid login, enter new login, login must contain only numbers, letters and characters '@,., _, -'"<<std::endl;
			std::getline(std::cin, l2);
		}

		msg = msg  + "Login:" + l2 +":";
	}
	c->send(msg);
}
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
	if ("You allowed three action: registration, login or quit"==message)
	{
		reg_login_quit(c);
	}
	else
	{
		if(!((message.find(":Email:INVALID:") == std::string::npos) || (message.find(":Login:INVALID:") == std::string::npos)))
		{
			invalidEmailOrLogin(message, c);
		}
		else
		{
			if(!(message.find(":your_information:") == std::string::npos))
			{
				std::cout << "from server : " << message << std::endl;
				std::string msg = message;
				msg = msg.erase(0, 18);
				my_information = string_to_map(msg);
				c->send(":update_users_data:");
			}
			else
			{
				if(message == "You allowed following action:view user data, send message another user, create a new group, send message to group or quit")
				{ std::thread* t = new std::thread(sender, c);
				  threads.push_back(t);
				}
				else
				{
					if(!(message.find(":update_users_data:")==std::string::npos))
					{
						update_users_data (message, c);
					}
					else
					{
						if(!(message.find(":message_from_user:")==std::string::npos))
						{
							std::cout << "from server:  " << message << std::endl;
							c->send(":return1:");
						}
						else
						{
							if(message == "There is no such combination of login and password")
							{std::cout << "from server:  " << message << std::endl;}
							else
							{
								if(message == ":Your_message_sent:")
								{c->send(":return1:");}
								else
								{
									if(message == ":registration was successful:")
										{
											std::cout << "from server:  " << message << std::endl;
										}
									else
									{}
								}
							}
						}
					}
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
	std::list<std::thread*>::iterator it = threads.begin();
	for(; it != threads.end(); ++it)
	{
		delete[](*it);
	}

	return 0;
}

