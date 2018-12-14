#include <iostream>
#include <regex>
#include <list>
#include <map>
#include <string>
#include <iterator>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "connection.hpp"
#include "user.hpp"
#include "function_server.hpp"

static int id = 0;
static int user_id = 0;
std::list<connection*> connections;
std::map<std::string,std::pair<int,std::string>> logIdPass;
std::map<int,user> id_user;
std::map<int,connection*> for_message;
std::map<std::string,std::string> mail;
std::map<std::string,std::string> user_info;
std::map<std::string,std::pair<int,std::string>>::iterator itr;
std::map<std::string,std::string>::iterator itrMail;
std::map<int,user>::iterator itrUser;
std::string keylog,value_pass,email,profInfo;
void recv_message(connection* s1, std::string message) {
	std::cout <<"CLIENT " << message <<std::endl;
	if(message == "barev")
		s1->send("REGISTRATION->R::LOGIN->L::QUIT->Q");
	if(message.find("1email:") != std::string::npos)
		find_email(message,s1);
	if(message.find("1login:") != std::string::npos)
		find_login(message,s1);
	if(message.find("password2:") != std::string::npos)
		value_pass = message.substr(message.find(":")+1,message.size()-message.find(":")-2);
	if(message.find("allinformation:") != std::string::npos)
		insert_maps(message,s1);
	if(message.find("sign_in:") != std::string::npos){
		 sign_in(s1,message);
	}
	if(message == "Q")
		s1->send("q");
	if(message == "all users"){
		all_users(s1);
		}
	if(message.find("from user:") !=std::string::npos){
		message_to_user(message,s1);
		}

	
	if(message == "esc"){
		s1->send("ALL USERS->all users:::SEND MESSAGE->send message:::LOGOUT->logout");

	}
	if(message == "logout"){
		s1->send("REGISTRATION->R::LOGIN->L::QUIT->Q");
	}
}
void binder_recv_message(connection* s, std::string firstMessage) {
	std::cout <<"CLIENT:BINDER " << firstMessage <<std::endl;
	if("connect" == firstMessage) {
		std::string pipe1="in"+std::to_string(id);
		std::string pipe2="out"+std::to_string(id);
		std::string pipe_name = pipe1 + ":" + pipe2 + "." + std::to_string(id++);
		s->send(pipe_name);
		connection* c = new connection(pipe2, pipe1);
		c->setRecvMessageCallback(recv_message);
		connections.push_back(c);
		s->send("q");
	}

}
std::string userToString(std::map<int,user> id_user,int user_id){
	std::string client_back = "";
	client_back ="Login:"+id_user[user_id].get_login()+":"+ "Name:"+id_user[user_id].get_name()+":"+"Surname:"+id_user[user_id].get_surname()+":"+"Email:"+id_user[user_id].get_email()+":"+"Birthday:"+id_user[user_id].get_birthday()+":"+"Phone:"+ id_user[user_id].get_phone()+":"+"Gender:"+id_user[user_id].get_gender()+":"+"User_id:"+id_user[user_id].get_user_id();
	std::cout<<"User_to_string: "<<client_back<<std::endl;
	return client_back;

}
std::map<std::string,std::string> stringToMap(std::string str){
	std::map<std::string,std::string> mymap;
	str.erase(0,1);
	std::string first="";
	std::string second="";
	while(str!="")
	{
		first=str.substr(0,str.find(":"));
		str.erase(0,str.find(":")+1);
		second=str.substr(0,str.find(":"));
		str.erase(0,str.find(":")+1);
		mymap.insert ( std::pair<std::string,std::string>(first,second));
	}
	return mymap;

}
void find_email(std::string message,connection* s1){
	if(message.find("1email:") != std::string::npos){
		email = message.substr(message.find(":")+1,message.size()-message.find(":")-2);
		for(itrMail = mail.begin();itrMail !=mail.end();++itrMail){
			if((*itrMail).first == email)
			s1->send("YOUR EMAIL IS BUSY,PLEASE ENTER ANOTHER EMAIL");	
		}
	}
}
void find_login(std::string message,connection* s1){
	if(message.find("1login:") != std::string::npos){
		keylog =message.substr(message.find(":")+1,message.size()-message.find(":")-2);
		if(keylog =="")
			keylog = email;
		for(itr=logIdPass.begin();itr !=logIdPass.end();++itr){
			if(itr->first == keylog)
			s1->send("YOUR LOGIN IS BUSY,PLEASE ENTER ANOTHER LOGIN");	
		}
	}
}
void insert_maps(std::string message,connection* s1){
	profInfo = message.substr(message.find(":"));
	logIdPass.emplace(keylog,std::make_pair(user_id,value_pass));
	mail.insert(std::pair<std::string,std::string>(email,""));
	profInfo = profInfo+"user_id:"+std::to_string(user_id)+":";
	std::cout<<"PROF;"<<profInfo<<std::endl;
	user_info = stringToMap(profInfo);
	user us(user_info);
	id_user.insert(std::pair<int,user>(user_id,us));
	std::string ok = "THANK YOU FOR REGISTRATION,YOUR ID IS "+std::to_string(user_id);
	s1->send(ok);
	usleep(1000);
	s1->send("REGISTRATION->R::LOGIN->L::QUIT->Q");
	user_id++;	
}
void sign_in(connection* s1,std::string message){
	std::string log_pass = message.substr(message.find(":")+1);
	std::string wrong_log = log_pass.substr(0,log_pass.find(":"));
	std::string wrong_pass= log_pass.substr(log_pass.find(":")+1);
	if(logIdPass[wrong_log].second == wrong_pass ){
		std::string back ="Your information:"+ userToString(id_user,logIdPass[wrong_log].first);
		s1->send(back);
		s1->send("ALL USERS->all users:::SEND MESSAGE->send message:::LOGOUT->logout");
		for_message.insert(std::pair<int,connection*>(logIdPass[wrong_log].first,s1));
	}
	else{
		std::string str = "YOUR LOGIN OR PASSWORD ARE WRONG,PLEASE ENTER RIGHT INFORMATION";
		s1->send(str);
		s1->send("REGISTRATION->R::LOGIN->L::QUIT->Q");
	}

}
void all_users(connection* s1){
	std::string all_ids ="";
	for(itrUser = id_user.begin();itrUser !=id_user.end();++itrUser){
		std::string str_id = std::to_string(itrUser->first);
		all_ids = all_ids + str_id +":";

	}
		s1->send(all_ids);
		usleep(10000);
		s1->send("ALL USERS->all users:::SEND MESSAGE->send message:::LOGOUT->logout");
}
std::string message_to_user(std::string message,connection* s1){
	std::string from_id = message.substr(0,message.rfind(":"));
	std::string for_id = message.substr(message.rfind(":")+1);
	int rider_id = stoi(for_id);
	if(for_message.find(rider_id)!=for_message.end())
			for_message.find(return_id(message))->second->send(from_id);
	

	else{
		std::string str =  "THIS USER NOT FOUND,PLEASE WRITE RIGHT ID";
		s1->send(str);
		s1->send("ALL USERS->all users:::SEND MESSAGE->send message:::LOGOUT->logout");
	}

}
int return_id(std::string message){
	std::string for_id = message.substr(message.rfind(":")+1);
	return stoi(for_id);

}
