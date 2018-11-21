#include <iostream>
#include <unistd.h>
#include <mutex>
#include "connection.hpp"
#include "user.h"
static std::string name1="";
static std::string name2="";
static std::mutex m;
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
		std::cout<<"Register<R>"<<std::endl;
                c.setRecvMessageCallback(recv_message);

	while (true)
	{
		std::string str="";
		std::getline(std::cin,str);
		if(str=="q")
		{
			break;
		}
	if(str=="R" || str=="r"){
	 std::string FirstName;
        std::cout<<"First Name : ";
        std::cin>>FirstName;
        user Fname;

        while(Fname.nameValid(FirstName)==false){
                 std::cout<<"First Name : ";
                 std::cin>>FirstName;

        }
        std::string LastName;
        std::cout<<"Last Name : ";
        std::cin>>LastName;
        user Lname;

        while(Lname.nameValid(LastName)==false){
                std::cout<<"Last Name : ";
                std::cin>>LastName;
        }
        std::string BirthDate;
        std::cout<<"Birth Date : ";
        std::cin>>BirthDate;
        user Bdate;
         while(Bdate.dateValid(BirthDate)==false){
                std::cout<<"Birth Date : ";
                std::cin>>BirthDate;
        }

        std::string Gender;
        std::cout<<"Gender : ";
        std::cin>>Gender;
        user gender;
         while(gender.genderValid(Gender)==false){
                std::cout<<"Gender : ";
                std::cin>>Gender;
        }

        std::string Login;
        std::cout<<"Login : ";
        std::cin>>Login;
        user login;
         while(login.loginValid(Login)==false){
                std::cout<<"Login : ";
                std::cin>>Login;
        }

        std::string Id;

        std::string Mail;
         std::cout<<"Mail : ";
        std::cin>>Mail;
        user mail;
         while(mail.mailValid(Mail)==false){
                std::cout<<"Mail : ";
                std::cin>>Mail;
        }
         user person;
	 std::string history="";
	 history+=":FirstName:"+FirstName+":LastName:"+LastName+":BirtDate:"+BirthDate+":Gender:"+Gender+":Login:"+Login+":Id:"+Id+":Mail:"+Mail+":";
	c.send(history);	 
	}else
	
	c.send(str);
	
	}
	return 0;
}
