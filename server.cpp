#include "connection.hpp"
#include "verification.hpp"
#include "user.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
static int value=0;
std::list<connection*> connections;
static int id=9;
std::map<std::string,std::string> current_user;
std::map<std::string,std::pair<std::string,std::string>> user_info;
std::map<int,user> id_ob;
std::map<int,connection*> id_con;
std::string show_id()
{
	std::string id="Show id : ";
	std::map<int,user>::iterator it;
	for(it=id_ob.begin();it!=id_ob.end();++it)
		id+=it->first + " ";
	return id;

}
bool search_log(std::string log)
{
	std::map<std::string,std::pair<std::string,std::string>>::iterator it;
	for(it=user_info.begin();it!=user_info.end();it++)
		if(it->first==log)
			return false;
	return true;
}
bool search_log_passw(std::string str)
{
	std::string log=str.substr(0,str.find(":"));
	std::string passw=str.substr(str.find(":")+1);
	std::cout<<"login: "<<log<<"Password: "<<passw<<std::endl;
	if(user_info[log].second==passw)
		return true;
	return false;


}
void recieve(connection* c, std::string msg)
{
	std::cout << "from client : " << msg << std::endl;
	if(":action:help:"==msg)
	{
		c->send("<registration> or <sign in>");
		return;
	}
	if(msg=="show users id")
	{
		c->send(show_id());
		c->send("action");
		return;
	}
	if(msg.substr(0,21)==":action:send_message:")
	{
		msg.erase(0,21);
		int id=std::stoi(msg.substr(0,msg.find(":")));
		std::string sms=msg.substr(msg.find(":")+1);
		if(id_con.find(id)==id_con.end())
		{
			c->send("Error id");
			c->send("action");
			return;
		}
		else
		{
			std::string send=":action:send:"+std::to_string(id)+":"+sms;
			id_con[id]->send(send);
			c->send(":return:Message sent");
			c->send("action");
			return;
		}
	}
	if(msg.substr(0,7)==":login:")
	{
		if(search_log(msg.substr(7)))
			c->send("Valid login");
		else
			c->send("Invalid login");
		return;
	}
	if(msg.substr(0,20)==":action:registration")
	{
		msg.erase(0,20);
		current_user=string_to_map(msg);
		++id;
		current_user.insert(std::pair<std::string,std::string>("id",std::to_string(id)));
		user ob(current_user);
		id_ob.insert(std::pair<int,user>(id,ob));
		user_info.emplace(current_user["login"],std::make_pair(std::to_string(id),current_user["password"]));
		id_con.emplace(id,c);
		std::string str=":return:your id : "+ std::to_string(id);
		c->send(str);
		c->send("action");
		return;
	}
	if(msg.find(":action:sign_in")!=std::string::npos)
	{
		msg.erase(0,16);
		if(!search_log_passw(msg))
		{
			c->send(":return:There is no such combination of login and password!");
			c->send("<registration> or <sign in>");
		}
		else
		{
			//informacian geterov petqa uxarkvi
			std::string s=":return:your information "+ map_to_string(current_user);
			c->send(s);
			c->send("action");
		}
		return;
	}
	if(msg=="quit")
	{
		//hanel online userneri cucakic
		c->send("return 0");
		return;
	}

}

void binder_recieve(connection* c, std::string msg)
{
	if(msg=="first message")
	{
		value++;
		std::string fifo1="C"+std::to_string(value);
		std::string fifo2="S"+std::to_string(value);
		connection* s=new connection(fifo1,fifo2);
		s->setRecvMessageCallback(recieve);
		connections.push_back(s);
		fifo2=fifo2+":"+fifo1;
		c->send(fifo2);
		c->send("q");
	}
}

int main()
{
	connection binder(std::string("out"),std::string("in"));
	binder.setRecvMessageCallback(binder_recieve);
	remove("busy.lock");

	return 0;

}

