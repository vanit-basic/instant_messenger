#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <list>
#include "connection.hpp"
#include <unistd.h>
#include <map>
#include "user.h"
#include <iterator>

static int idclient=0;
static int iduser=100000;
static std::string name1;
static std::string name2;
static std::string name3;
static std::list<connection*> connections;
static std::map<std::string, std::pair<std::string, std::string>> loginMap;
static std::map<std::string, user> userMap;
static std::map<std::string, std::pair<std::string, std::string>>::iterator it;
static std::list<std::string>::iterator itr;
static std::list<std::string>::iterator iter;
static std::map<std::string, std::string> my;
std::map<std::string,std::string> StringtoMap (std::string str){
        str.erase(0,1);
        std::map<std::string,std::string>myMap;
        while(str.length() != 0){
        int pos=str.find(':');
        std::string key="";
        key=str.substr(0,pos);
        str.erase(0,pos+1);
        pos=str.find(':');
        std::string value="";
        value=str.substr(0,pos);
        str.erase(0,pos+1);
        myMap.insert(std::pair<std::string,std::string>(key,value));
        }

        return myMap;

}

void usercreater(std::map<std::string, std::string> my){
	
        user us;
        us.setFirstName(my.find("firstname")->second);
        us.setLastName(my.find("lastname")->second);
        us.setBirthDate(my.find("birthdate")->second);
        us.setMail(my.find("mail")->second);
        us.setLogin(my.find("login")->second);
        us.setId(std::to_string(iduser));
        us.setGender(my.find("gender")->second);
	userMap.insert(std::pair<std::string, user>(us.getId(), us));
	loginMap.emplace(my["Login"],std::make_pair(std::to_string(iduser),my["Password"]));
	for(auto it=loginMap.begin();it !=loginMap.end();it++){
		std::cout<<it->first<<it->second.first<<it->second.second<<std::endl;
		std::list<std::string> mylist ={it -> first};
		for(auto itr=mylist.begin();itr !=mylist.end();itr++){
			//for(auto iter=mylist.begin();iter !=mylist.end();iter++){
					
				std::cout<<(*itr)<<std::endl;
				//std::cout<<(*iter)<<std::endl;
			//}
		}
	}
	iduser++;
}


void recv_message(connection* c, std::string message) 
{
	std::map<std::string, std::string> myMap;
	std::cout << "from client : "<< c->getId()<<":   " << message << std::endl;
	myMap = StringtoMap(message);
	bool mi_hat_flag=true;
		std::cout<<myMap.find("action")->second<<std::endl;
	if(myMap.find("action")->second == "register"){
			std::cout<<"Barevvv ::::: "<<std::endl;
		for(auto it = loginMap.begin();it !=loginMap.end();++it){
			if(it->first != myMap.find("Login")->second){
				mi_hat_flag=false;
				message = "login is busy";	
				c->send(message);
			}
		}
	}

	usercreater(myMap);
}

void recv_message_binder(connection* c, std::string message) 
{
	if(message=="new client")
	{
		std::cout << "client: " << message << std::endl;
		name1="C" + std::to_string(idclient);
		name2="S" + std::to_string(idclient);
		name3= name1 + ":" +name2;
		idclient++;
		c->send(name3);
		c->send("q");
		connection* s=new connection(name2,name1);
		s->setId(name1);
		s->setRecvMessageCallback(recv_message);
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
