#include <iostream>
#include <unistd.h>
#include <mutex>
#include "connection.hpp"
#include "user.h"
static std::string name1="";
static std::string name2="";
static std::mutex m;
static bool log = false;
void recv_message_binder(connection* c, std::string message)
{
	if(message!="q" && message !="")
	{
		m.lock();
		int pos = message.find(':'); 
		int end = message.length() - pos - 1;
		name1 = message.substr(0, pos);
		name2 = message.substr(pos+1 , end);
		m.unlock();
	}
}

std::string regist(){
	std::string FirstName;
	std::cout<<"First Name : ";
	std::cin>>FirstName;

	while(!nameValid(FirstName)){
		std::cout<<"First Name : ";
		std::cin>>FirstName;

	}
	std::string LastName;
	std::cout<<"Last Name : ";
	std::cin>>LastName;

	while(!nameValid(LastName)){
		std::cout<<"Last Name : ";
		std::cin>>LastName;
	}
	std::string BirthDate;
	std::cout<<"Birth Date : ";
	std::cin>>BirthDate;
	while(!dateValid(BirthDate)){
		std::cout<<"Birth Date : ";
		std::cin>>BirthDate;
	}

	std::string Gender;
	std::cout<<"Gender : ";
	std::cin>>Gender;
	while(!genderValid(Gender)){
		std::cout<<"Gender : ";
		std::cin>>Gender;
	}

	std::string Login;
	std::cout<<"Login : ";
	std::cin>>Login;
	while(!loginValid(Login)){
		std::cout<<"Login : ";
		std::cin>>Login;
	}

	std::string Mail;
	std::cout<<"Mail : ";
	std::cin>>Mail;
	while(!mailValid(Mail)){
		std::cout<<"Mail : ";
		std::cin>>Mail;
	}
	std::string Password;
	std::cout<<"password : ";
	std::cin>>Password;
	while(!passValid(Password)){
		std::cout<<"password : ";
		std::cin>>Password;
	}
	std::string passdef;
	std::cout<<"password definition : ";
	std::cin>>passdef;
	while(Password != passdef){
		std::cout<<"password definition : ";
		std::cin>>passdef;
	}

	std::string history="";

	history+=":action:register:FirstName:"+FirstName+":LastName:"+LastName+":BirthDate:"+BirthDate+":Gender:"+Gender+":Login:"+Login+":Mail:"+Mail+":Password:"+Password+":";
	
	return history;	 
}

std::string id_text(){
	std::string id="";
	std::string gen;
	std::cout<<"ID : ";
	getline(std::cin,id);
	//std::cin>>id;

	std::string text;
	std::cout<<"text : ";
	getline(std::cin,text);

	gen =":action:message:id:"+id+":text:"+text+":";
	return gen;

}

std::string login(){
	std::string logpas="";
	std::string Log;
	std::cout<<"Login : ";
	std::cin>>Log;

	std::string Pass;
	std::cout<<"Password : ";
	std::cin>>Pass;

	logpas+=":action:signin:Login:"+Log+":Password:"+Pass+":";
	return logpas;

}

void recv_message(connection* c, std::string message)
{
	std::cout << "from server : " << message << std::endl;
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
		connection c(name1,name2);
                c.setId(name1);
                m.unlock();
                c.setRecvMessageCallback(recv_message);

		while (true)
		{
			std::string str="";
			if(!log){
				std::cout<<"Register<R>:Login<L>:Logout<q>"<<std::endl;
				std::getline(std::cin,str);
				if(str=="q")
				{
					break;
				}
				if(str=="L" || str=="l"){
					log = true;
					std::string logpas = login();
					std::cout<<logpas<<std::endl;
					c.send(logpas);
				}

				if(str=="R" || str=="r"){
					std::string reg = regist();
					std::cout<<reg<<std::endl;
					c.send(reg);
				}
			}
			else{
				std::cout<<"message<M>:quit<q>"<<std::endl;
				std::getline(std::cin,str);
				if(str=="q")
				{
					break;
				}
				if((str=="M" || str=="m")){
					std::string text;
					text = id_text();	
					c.send(text);

				}	
			}
		}
	return 0;
		
}
