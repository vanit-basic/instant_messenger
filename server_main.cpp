#include <iostream>
#include <list>
#include <unistd.h>
#include "connectionUser.hpp"
#include "valid.hpp"

static std::map<std::string, std::pair<std::string, std::string>> Log_Id_Pass;
static std::map<std::string, user> users;
static std::map<std::string, bool> mail;
static std::map<std::string, bool> joined;
static std::map<std::string, connection*> connections;
static std::map<std::string, std::string> id_connection;
static std::map<std::string, std::string> id_msg;
static std::map<std::string, std::string> id_log;
static int i=0;
static int ID=0;

void reg_valid_log_or_mail(std::string msg, std::string log, std::string email, connection* c)
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

void reg_inf(std::string message, connection* c)
{

	std::string msg = message;
	std::string email = "", log = "", pass = "";
	msg = msg.erase(0, msg.find(":Email:")+7);
	email = msg.substr(0, msg.find(':'));
	msg = msg.erase(0, msg.find(":Login:")+7);
	log = msg.substr(0, msg.find(':'));
	msg = message;
	if((!isValidLogin2(Log_Id_Pass, log)) || (!isValidE_mail2(mail, email)))
	{
		reg_valid_log_or_mail(msg, log, email, c);
	}
	else
	{
		std::map<std::string, std::string> user_inf;
		ID++;
		std::string id;
		id="user_"+std::to_string(ID);
		msg=message + "Id:" + id + ":";
		msg.erase(0,26);
		user_inf=string_to_map(msg);
		log = user_inf["Login"];
		pass = user_inf["Password"];
		Log_Id_Pass.emplace(log, std::make_pair(id, pass));
		id_log.emplace(id, log);
		mail.emplace(email, 0);
		user u(user_inf);
		users.emplace(id, u);
		std::string inf2="";
		inf2 = ":Update_users_data:" + us_inf(users, id);
		id=":YOUR_ID:"+id;
		c->send(id);
		c->send("You allowed three action: registration, login or quit");
		std::map<std::string, connection*>::iterator k=connections.begin();
		for(k=connections.begin(); k!=connections.end();++k)
		{
			(k->second)->send(inf2);
		}
	}
}

void sign_in_Valid(std::string message, connection* c, std::string log, std::string pass)
{
	std::string uid="";
	if(isValidSignIn(Log_Id_Pass, log, pass))
	{
		if(!(isValidJoined(joined, log)))
		{
			c->send("USER WITH THIS LOGIN IS ALREADY LOGGED IN");
			c->send("You allowed three action: registration, login or quit");
		}
		else
		{
			uid = Log_Id_Pass[log].first;
			std::cout<<"joined.emplace  "<<log<<"\n";
			joined.emplace(log, true);
			std::string inf1="";
			std::string inf2="";
			inf1 = ":Your_information" + user_information(users, uid);
			c->send(inf1);
			inf1 = Log_Id_Pass[log].first;
			id_log.emplace(inf1, log);
			std::cout<<"Id_msg   "<<id_msg[inf1]<<"  id  "<<inf1<<"\n";
			id_connection.emplace(inf1, c->getId());
			if(!(id_msg[inf1]==""))
			{
				c->send("You allowed following action:view user data, send message another user, create a new group, send message to group or quit");
				c->send(id_msg[inf1]);
			}
			else
			{
				c->send("You allowed following action:view user data, send message another user, create a new group, send message to group or quit");
			}
		}
	}
	else
	{
		c->send("There is no such combination of login and password");
		c->send("You allowed three action: registration, login or quit");
	}
}

void sign_in(std::string message, connection* c)
{
	std::string msg = message;
	std::string log = "";
	std::string pass = "";
	msg = msg.erase(msg.find(":action:signin:"),msg.find(":action:signin:")+21);
	log = msg.substr(0, msg.find(':'));
	msg = msg.erase(0,msg.find(':')+10);
	pass=msg.substr(0, msg.find(':'));
	sign_in_Valid(message, c, log, pass);
}

void us_send_msg(std::string message, connection* c )
{
	std::string msg = message;
	std::string con_n="", us_id="", key = "", value = "";
	msg = msg.erase(0,26);
	key = msg.substr(0, msg.find(':'));
	msg = msg.erase(0, key.size()+7);
	us_id= msg.substr(0, msg.find(':'));
	msg = msg.erase(0, us_id.size()+9);
	value =":Message_from_user:"+us_inf(users, us_id) + msg.substr(0, msg.find(':')) + ":";
	if(joined[id_log[key]]==true)
	{
	        con_n = id_connection[key];
		connections[con_n]->send(value);
	}
	else
	{
	         if(!(id_msg[key] ==""))
		{
			value = value.erase(0,1);
			id_msg[key] = id_msg[key] + value;
			c->send(":Your_message_sent:");
		}
		else
		{
			id_msg[key] = value;
			c->send(":Your_message_sent:");
		}
	}
}

void update_us_data(std::string message, connection* c)
{
	std::string user_data=":Update_users_data:";
	std::map<std::string, user>::iterator k=users.begin();
	for(; k != users.end(); ++k)
	{
		user_data = user_data + us_inf(users, k->first);
	}
	c->send(user_data);
}

void recv_message(connection* c, std::string message)
{
	std::cout << "From client : "<< c->getId()<<":   " << message << std::endl;
	if(message=="quit")
	{
		c->send("quit");
	}
	else
	{
		if(!(message.find(":registration:information:") == std::string::npos))
		{
			reg_inf(message, c);
		}
		else
		{
			if(!(message.find(":action:signin:")==std::string::npos))
			{
				sign_in(message, c);
			}
			else
			{
				if(!(message.find(":Update_users_data:")))
				{
					update_us_data(message, c);
				}
				else
				{
					if(message==":return1:")
					{c->send("You allowed following action:view user data, send message another user, create a new group, send message to group or quit");  }
					else
					{
						if(!(message.find(":send_message_user:")==std::string::npos))
						{
							us_send_msg(message, c);
						}
						else{}
					}
				}
			}
		}
	}
}


void recv_message_binder(connection* c, std::string message)
{
        if(message=="New Client")
        {
                std::cout << "Client: " << message << std::endl;
                std::string fifo_name1="CLIENT" + std::to_string(i);
                std::string fifo_name2="SERVER" + std::to_string(i);
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

