#include <iostream>
#include <list>
#include <unistd.h>
#include "connectionAndUser.hpp"
#include "utils.hpp"

static std::map<std::string, std::pair<std::string, std::string>> Log_Id_Pass;
static std::map<std::string, user> users;
static std::map<std::string, bool> mail;
static std::map<std::string, bool> joined;
static std::map<std::string, connection*> connections;
static std::map<std::string, std::string> id_connection;
static int i=0;
static int ID=0;

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
			if(!(message.find(":registration:information:") == std::string::npos))
			{
				msg = msg.erase(0, msg.find(":Email:")+7);
				email = msg.substr(0, msg.find(':'));
				msg = msg.erase(0, msg.find(":Login:")+7);
				log = msg.substr(0, msg.find(':'));
				msg = message;
				if((!isValidLogin2(Log_Id_Pass, log)) || (!isValidE_mail2(mail, email)))
				{
					if(!isValidE_mail2(mail, email))
					{
						msg = msg.erase(msg.find(":Email:"), 7+email.size());
						msg = msg + "Email:INVALID:";
					}
					if(!isValidLogin2(Log_Id_Pass, log))
					{
						msg = msg.erase(msg.find(":Login:"), 7+log.size());
						msg = msg + "Login:INVALID:";
					}
					c->send(msg);
				}
				else
				{
					std::map<std::string, std::string> database;
					ID++;
					id="user_"+std::to_string(ID);
					msg=message + "Id:" + id + ":";
					msg.erase(0,26);
					database=string_to_map(msg);
					log = database["Login"];
					pass = database["Password"];
					Log_Id_Pass.emplace(log, std::make_pair(id, pass));
					mail.emplace(email, 0);
					user u(database);
					users.emplace(id, u);
					id=":your_id:"+id;
					c->send(id);
					c->send("You allowed three action: registration, login or quit");
				}
			}
			else
			{
				if(!(message.find(":action:signin:")==std::string::npos))
				{
					msg = msg.erase(msg.find(":action:signin:"),msg.find(":action:signin:")+21);
					log = msg.substr(0, msg.find(':'));
					msg = msg.erase(0,msg.find(':')+10);
					pass=msg.substr(0, msg.find(':'));
					std::string uid="";
					if(isValidSignIn(Log_Id_Pass, log, pass, uid))
					{
						if(!isValidJoined(joined, log))
						{
							c->send("user with this login is already logged in");
							c->send("You allowed three action: registration, login or quit");
						}
						else
						{
							joined.emplace(log, true);
							std::string inf1="";
							std::string inf2="";
							inf1 = ":your_information" + user_information(users, uid);
							c->send(inf1);
							inf1 = Log_Id_Pass[log].first;
							id_connection.emplace(inf1, c->getId());
							inf2 = ":update_users_data:" + us_inf(users, inf1);
							std::map<std::string, connection*>::iterator k=connections.begin();
							for(k=connections.begin(); k!=connections.end();++k)
							{
								(k->second)->send(inf2);
							}
							c->send("You allowed following action:view user data, send message another user, create a new group, send message to group, update users data or quit");
						}
					}
					else
					{
						c->send("There is no such combination of login and password");
						c->send("You allowed three action: registration, login or quit");
					}
				}
				else
				{
					if(!(message.find(":update_users_data:")))
					{
						std::string user_data=":update_users_data:";
						std::map<std::string, user>::iterator k=users.begin();
						for(; k != users.end(); ++k)
						{
							user_data = user_data + us_inf(users, k->first);
						}
						c->send(user_data);
					}
					else
					{
						if(message==":return1:")
						{c->send("You allowed following action:view user data, send message another user, create a new group, send message to group, update users data or quit");  }
						else
						{
							if(!(message.find(":send_message_user:")==std::string::npos))
							{
								std::string con_n="";
								std::string us_id="";
								msg = msg.erase(0,26);
								key = msg.substr(0, msg.find(':'));
								std::cout<<"user id  "<< key<<std::endl;
								msg = msg.erase(0, key.size()+7);
								us_id= msg.substr(0, msg.find(':'));
								std::cout<<"my id  "<< us_id<<std::endl;
								msg = msg.erase(0, us_id.size()+9);
								value =":message_from_user:"+us_inf(users, us_id)+":"+ msg.substr(0, msg.find(':')) + ":";
								std::cout<<"uxarkvac sms  "<<value<<std::endl;
								con_n = id_connection[key];
								std::cout<<"conention id  "<< con_n<<std::endl;
								connections[con_n]->send(value);
								//connections[con_n]->send("You allowed following action:view user data, send message another user, create a new group, send message to group, update users data or quit");
								//c->send(":Your_message_sent:");
								//c->send("You allowed following action:view user data, send message another user, create a new group, send message to group, update users data or quit");
							}
							else{}
						}
					}
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
		connections.emplace(fifo_name1, s);
        }
}

int main ()
{
        connection binder(std::string("out"), std::string("in"));
        binder.setRecvMessageCallback(recv_message_binder);
        std::map<std::string, connection*>::iterator k=connections.begin();
        for(k=connections.begin(); k!=connections.end();++k)
        {
                delete [](k->second);
        }


        return 0;
}

