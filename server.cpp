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
#include <algorithm>
std::map<std::string,std::list<std::string>> users_mess;
std::map<std::string,bool> busy_user;
static int value=0;
std::list<connection*> connections;
static int id=9;
std::map<std::string,std::string> current_user;
std::map<std::string,std::pair<int,std::string>> user_info;
std::map<int,user> id_ob;
std::map<int,connection*> id_con;
std::string list_to_string(std::list<std::string> l)
{
	std::string str="";
	std::list<std::string>::iterator it;
	for(it=l.begin();it!=l.end();++it)
		str+=*it;
	return str;

}
std::string ret_info(std::string log)
{
	int user_id=user_info[log].first;
	user u=id_ob[user_id];
	std::string str=":Name:"+u.get_firstname()+":Surname:"+u.get_lastname()+":Email:"+u.get_mail()+":Birth Date:"+u.get_birth_date()+":Gender:"+u.get_gender()+":Login:"+u.get_login()+":Id:"+std::to_string(u.get_id())+":";
	return str;

}
std::string show_id()
{
	std::string id=":return:Show id : ";
	std::map<int,user>::iterator it;
	for(it=id_ob.begin();it!=id_ob.end();++it)
		id+=std::to_string(it->first) + " : ";
	return id;
}
bool search_log(std::string log)
{
	std::map<std::string,std::pair<int,std::string>>::iterator it;
	for(it=user_info.begin();it!=user_info.end();it++)
		if(it->first==log)
			return false;
	return true;
}
bool search_log_passw(std::string str)
{
	std::string log=str.substr(0,str.find(":"));
	std::string passw=str.substr(str.find(":")+1);
	if(user_info[log].second==passw)
		return true;
	return false;
}
/////////////////////////
void sign_in(std::string str,connection* c)
{
	str.erase(0,16);
	std::string log=str.substr(0,str.find(":"));
	if(!search_log_passw(str))
	{
		c->send(":return:There is no such combination of login and password!");
		c->send("<registration> or <sign in>");
	}
	else
	{
		busy_user[std::to_string(user_info[log].first)]=true;
		std::string s="myinfo"+ret_info(str.substr(0,str.find(":")));
		c->send(s);
		s=":return:your information "+ret_info(str.substr(0,str.find(":")));
		c->send(s);
		c->send(":return:"+list_to_string(users_mess[std::to_string(user_info[log].first)]));
		users_mess[std::to_string(user_info[log].first)].clear();
		c->send("action");
	}
}
void registr(std::string msg,connection* c)
{
		msg.erase(0,20);
                current_user=string_to_map(msg);
                ++id;
                current_user.insert(std::pair<std::string,std::string>("id",std::to_string(id)));
                user ob(current_user);
                id_ob.insert(std::pair<int,user>(id,ob));
                user_info.emplace(current_user["login"],std::make_pair(id,current_user["password"]));
                id_con.emplace(id,c);
                busy_user.emplace(std::to_string(id),true);
                std::string s="myinfo"+ret_info(current_user["login"]);
                c->send(s);
                s=":return:your information " + ret_info(current_user["login"]);
                c->send(s);
                c->send("action");
}
void send_mess(std::string msg,connection* c)
{
		msg.erase(0,21);
                int id_rec=std::stoi(msg.substr(0,msg.find(":")));
                msg.erase(0,msg.find(":")+1);
                int id_send=std::stoi(msg.substr(0,msg.find(":")));
                std::string sms=msg.substr(msg.find(":")+1);
                if(id_con.find(id_send)==id_con.end())
                {
                        c->send(":return:Error id");
                        c->send("action");
                }
                if(busy_user[std::to_string(id_send)]==false)
                {
                        users_mess[std::to_string(id_send)].push_back("ID:"+std::to_string(id_rec)+" send message: "+sms+"\n");
                        c->send(":return:Message sent");
                        c->send("action");
                }
                if(id_con.find(id_send)!=id_con.end())
                {
                        std::string send=":action:send:"+std::to_string(id_rec)+":"+sms;
                        id_con[id_send]->send(send);
                        c->send(":return:Message sent");
                        c->send("action");
                }
}
void recieve(connection* c, std::string msg)
{
	if(":action:help:"==msg)
		c->send("<registration> or <sign in>");
	if(msg=="show users id")
	{
		c->send(show_id());
		c->send("action");
	}
	if(msg.substr(0,21)==":action:send_message:")
		send_mess(msg,c);
	if(msg.substr(0,7)==":login:")
	{
		if(search_log(msg.substr(7)))
			c->send("Valid login");
		else
			c->send("Invalid login");
	}
	if(msg.substr(0,20)==":action:registration")
		registr(msg,c);
	if(msg.find(":action:sign_in:")!=std::string::npos)
		sign_in(msg,c);
	if(msg.substr(0,4)=="quit")
	{
		busy_user[msg.substr(4)]=false;
		c->send("return 0");
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

