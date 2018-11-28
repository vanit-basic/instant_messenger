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
static std::map<std::string, std::string> my;
static std::map<std::string, std::string> mails;
static std::map<std::string, connection*> us_con_mess;
static std::list<std::string> signins;

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
	
        my.insert(std::pair<std::string,std::string>("Id" , std::to_string(iduser)));
	user us(my);
	userMap.insert(std::pair<std::string, user>(us.getId(), us));
	loginMap.emplace(my["Login"],std::make_pair(std::to_string(iduser),my["Password"]));
        mails.emplace(my["Login"],my["Mail"]);
	for(auto it=mails.begin();it !=mails.end();it++){
		std::cout<<it->first<<it->second<<std::endl;
		
	}
	iduser++;
}


void recv_message(connection* c, std::string message) 
{
	std::map<std::string, std::string> myMap;
	std::cout << "from client : "<< c->getId()<<":   " << message << std::endl;
	myMap = StringtoMap(message);
	bool mi_hat_flag=true;
	bool erku_hat_flag=true;
	if(myMap["action"] == "register"){
		for(auto it = loginMap.begin();it !=loginMap.end();++it){
			if(it->first == myMap["Login"]){
				mi_hat_flag=false;
			}
		}
		for(auto it = mails.begin();it != mails.end();++it){
			if(it->second == myMap["Mail"]){
				erku_hat_flag=false;
			}
		}
		if(mi_hat_flag==true && erku_hat_flag==true){
			usercreater(myMap);
		}
		else if(mi_hat_flag == false || erku_hat_flag == false){
			if(erku_hat_flag == false && mi_hat_flag == false){
				message = "login and mail is busy";		
				c->send(message);
			}

			else if(erku_hat_flag == false){
				message = "mail is busy";		
				c->send(message);
			}
			else{
				message = "login is busy";	
				c->send(message);
			}
		}
	}
	if(myMap["action"] == "signin"){
		bool log = true;
		for (std::list<std::string>::iterator it = signins.begin(); it != signins.end(); it++){
			if(myMap["Login"] == *it){
				log = false;
			}	
		}		
		if(log){		
			for(auto it = loginMap.begin();it !=loginMap.end();++it){
				if(it->first == myMap["Login"]){
					if(it->second.second == myMap["Password"]){
						signins.push_back(it->second.first);
						user us = userMap[it->second.first];
						c->send("Login OK\n" + us.getDetails());
						us_con_mess.emplace(it->second.first, c);					
					}
				}
			}
		}
	}

	if(myMap["action"] == "message"){
		for (std::list<std::string>::iterator it = signins.begin(); it != signins.end(); it++){
			if(myMap["id"] == *it){
				connection* second_user = us_con_mess[myMap["id"]];
				second_user->send(myMap["text"]);				
			}	
		}
	}
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
