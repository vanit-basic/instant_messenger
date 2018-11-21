#include <iostream>
#include <list>
#include "connectionAndUser.hpp"
#include "utils.hpp"
#include <unistd.h>
#include <map>


static std::map<std::string, std::pair<std::string, std::string>*> Id_Log_Pass;
static std::map<std::string, user*> users;
static std::map<std::string, bool> mail;
static int i=0;
static int ID=0;
static std::list<connection*> connections;

void recv_message(connection* c, std::string message) 
{
	std::cout << "from client : "<< c->getId()<<":   " << message << std::endl;
	std::string key = "";
	std::string value = "";
	std::string log = "";
	std::string email = "";
	std::string pass = "";
	std::string id = "";
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
			c->send("Enter your login end password for sign in");
		}
		else
		{
			if(message=="quit")
			{
				c->send("quit");
			}
			else
			{
				if((message.find(":registration:information:")>=0)&&(message.find(":registration:information:")<message.size()))
				{
					msg = msg.erase(0, msg.find(":Email:")+7);
					email = msg.substr(0, msg.find(':'));
					msg = msg.erase(0, msg.find(":Login:")+7);
					log = msg.substr(0, msg.find(':'));
					if(!(isValidLogin2(Id_Log_Pass, log) || isValidE_mail2(mail, email)))
					{
						if(!isValidLogin2(Id_Log_Pass, log))
						{
							msg = message;
							msg = msg.erase(msg.find(":Login:"), 7+log.size());
							msg = msg + "Login:INVALID:";
						}
						if(!isValidE_mail2(mail, email))
						{
							msg = message;
							msg = msg.erase(msg.find(":Email:"), 7+log.size());
							msg = msg + "Email:INVALID:";
						}
						c->send(msg);
					}
					else
					{
						std::map<std::string, std::string> datebase;
						ID++;
						id="user_"+std::to_string(ID);
						msg=message + "Id:" + id + ":user_connection:" +(c->getId()) + ":";
						msg.erase(0,26);
						string_to_map_and_log_pass(datebase, msg, log, pass);
						std::pair<std::string,std::string>* p=new std::pair<std::string,std::string>(id, pass);
						Id_Log_Pass.emplace(log,p);
						mail.emplace(email, 0);
						user* u = new user(datebase);
						users.emplace(id, u);
						id=":your_id:"+id;
						c->send(id);
						c->send("You allowed three action: registration, login or quit");
					}
				}
				else
				{
					if((message.find(":action:signin:")>=0)&&(message.find(":action:signin:")<message.size()))
					{
						msg = msg.erase(msg.find(":action:signin:"),msg.find(":action:signin:")+21);
						log = msg.substr(0, msg.find(':'));
						msg = msg.erase(0,msg.find(':')+10);
						pass=msg.substr(0, msg.find(':'));
						std::string uid="";
						if(isValidSignIn(Id_Log_Pass, log, pass, uid))
						{
							std::string in="";
							in = ":your_information" + user_information(users, uid);
							c->send(in);
							c->send("You allowed following action: send message another user, create a new group, send message to group or quit");
						}
						else
						{
							c->send("There is no such combination of login and password");
							c->send("You allowed three action: registration, login or quit");
						}
					}
					else
					{}
				}

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
