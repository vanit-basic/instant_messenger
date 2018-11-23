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

static int id = 0;
static int user_id = 0;
std::list<connection*> connections;
std::map<std::string,std::pair<int,std::string>> logIdPass;
std::map<int,user> id_user;
std::map<std::string,std::string> mail;
std::map<std::string,std::string> user_info;
std::map<std::string,std::pair<int,std::string>>::iterator itr;
std::map<std::string,std::string>::iterator itrMail;
std::map<int,user>::iterator itrUser;
std::string userToString(std::map<int,user> id_user,int user_id){
	std::string client_back = "";
	client_back ="Login:"+id_user[user_id].get_login()+ "Name:"+id_user[user_id].get_name()+"Surname:"+id_user[user_id].get_surname()+"Email:"+id_user[user_id].get_email()+"Birthday:"+id_user[user_id].get_birthday()+"Phone:"+ id_user[user_id].get_phone()+"Gender:"+id_user[user_id].get_gender()+"User_id:"+id_user[user_id].get_user_id();
	return client_back;

}
		
std::map<std::string,std::string> stringToMap(std::string keyValue1){
std::map<std::string,std::string> myMap;
       	int size1 = keyValue1.size();
        if(keyValue1[0]==':'){
                keyValue1 = keyValue1.substr(1,size1-1);
        int size1 = keyValue1.size();
        }
                std::string key = keyValue1.substr(0,keyValue1.find(":"));
                std::string mnacac = keyValue1.substr(keyValue1.find(":")+1);
                std::string value = mnacac.substr(0,mnacac.find(":"));
                std::string mnacac1 = mnacac.substr(mnacac.find(":")+1);
                myMap.insert(std::pair<std::string, std::string>(key, value));
                if(size1 !=0)
                stringToMap(mnacac1);


        return myMap;
}

void recv_message(connection* s1, std::string message) {
        std::cout <<"CLIENT " << message <<std::endl;
        std::string profInfo="";
	std::string keylog,value_pass,email;
        if(message == "barev"){
        s1->send("FOR REGISTRATION ENTER R::FOR LOGIN ENTER L::FOR QUIT ENTER Q");
        }
        if(message == "R"){
                s1->send("Profile information");

        }
        if(message.find("email1:") != std::string::npos){
		email = message.substr(message.find(":")+1,message.size()-message.find(":")-2);
		for(itrMail = mail.begin();itrMail !=mail.end();++itrMail){
			if((*itrMail).first == email){
				s1->send("YOUR EMAIL IS BUSY,PLEASE ENTER ANOTHER EMAIL");
				break;
				
	}
		}
	}
        if(message.find("login1:") != std::string::npos){
		keylog =message.substr(message.find(":")+1,message.size()-message.find(":")-2);
		if(keylog =="")
			keylog = email;
		for(itr=logIdPass.begin();itr !=logIdPass.end();++itr){
			if((*itr).first == keylog){
				s1->send("YOUR LOGIN IS BUSY,PLEASE ENTER ANOTHER LOGIN");
				break;
	}
	}
	}
        if(message.find("password2:") != std::string::npos){
		value_pass = message.substr(message.find(":")+1,message.size()-message.find(":")-2);
	}
        if(message.find("allinformation:") != std::string::npos){
		profInfo = message.substr(message.find(":")+1);
		logIdPass.emplace(keylog,std::make_pair(user_id,value_pass));
		mail.insert(std::pair<std::string,std::string>(email,""));
		profInfo = profInfo+"user_id:"+std::to_string(user_id)+":";
		user_info = stringToMap(profInfo);
		user us(user_info);
		id_user.insert(std::pair<int,user>(user_id,us));


                std::string ok = "THANK YOU FOR REGISTRATION,YOUR ID IS "+std::to_string(user_id);
                s1->send(ok);
		user_id++;
        }
	if(message == "L"){
		s1->send("ENTER YOUR LOGIN AND PASSWORD");
	}
	if(message.find("sign_in:") != std::string::npos){
		std::string log_pass = message.substr(message.find(":")+1);
		std::string wrong_log = log_pass.substr(0,log_pass.find(":"));
		std::string wrong_pass= log_pass.substr(log_pass.find(":")+1);
		std::cout<<wrong_log<<"::::::::::::::"<<wrong_pass<<std::endl;
		for(itr=logIdPass.begin();itr !=logIdPass.end();++itr){
                        if(itr->first == wrong_log){
				if(itr->second.second ==wrong_pass){
					for(itrUser = id_user.begin();itrUser !=id_user.end();++itrUser){
						if(itr->second.first = (*itrUser).first){
							break;
						}
						std::string back ="Your information:"+ userToString(id_user,(*itrUser).first);
						s1->send(back);
					}
					}
				else{
				s1->send("YOUR LOGIN OR PASSWORD ARE NOT WRONG,PLEASE ENTER RIGHT INFORMATION");
				}

				}
			else{
				s1->send("YOUR LOGIN OR PASSWORD ARE NOT WRONG,PLEASE ENTER RIGHT INFORMATION");

	}
}
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

int main () {
        std::ifstream busy("busy.lock");
                if(busy.is_open()){
                        while(busy.is_open()){
                        usleep(100);
                        }
 }
                else{
                        std::ofstream busy1("busy.lock");

                        connection binder(std::string("out"), std::string("in"));
                        binder.setRecvMessageCallback(binder_recv_message);
                        busy1.close();
                        remove("busy.lock");
                }


        return 0;
}
