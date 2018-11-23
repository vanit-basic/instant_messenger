#include <iostream>
#include <unistd.h>
#include "connection.hpp"
#include "verification.hpp"
#include <mutex>
#include <string>
std::string for_login="";
std::string fifo1="";
std::string fifo2="";
connection* mainConnection = NULL;


void recv_message_c(connection* c, std::string message) {
	std::string msg1="";
	std::string info=":action:registration";
	std::string confmsg="";
	std::string msg="";
	if(message.find(":action:send:")!=std::string::npos)
	{
		message.erase(0,13);
		std::string id=message.substr(0,message.find(":"));
		message.erase(0,message.find(":")+1);
		std::cout<<"ID:"<<id<<" send message: "<<message<<std::endl;
		message="You allowed following action: send message another user, create a new group, send message to group or quit";
	}
	std::cout << "From server : " << message << std::endl;
	if(message=="<registration> or <sign in>" || message=="You allowed following action: send message another user, create a new group, send message to group or quit" || message=="There is no such combination of login and password!" )

	{
		do
		{
			std::cout<<"Enter action!\n";
			getline(std::cin,msg1);
			if(msg1!="registration" && msg1!="sign in" && msg1!="send" && msg1!="users")
				std::cout<<"Wrong action!";
		}
		while(msg1!="registration" && msg1!="sign in" &&  msg1!="send" && msg1!="users");
	}
	
	if(msg1=="users")
		c->send("show users id");

	std::string user_id="";
	std::string text="";
	if(msg1=="send" || message=="Error id")
	{
			std::cout<<"Enter user id : ";
			getline(std::cin,user_id);
		std::cout<<"Enter message: ";
		getline(std::cin,text);
		std::string sms=":action:send_message:"+user_id+":"+text;
		c->send(sms);
	}
	


	
	if(msg1=="registration" || message=="Login is busy!")
	{

		do
		{
			std::cout<<"Firstname: ";
			getline(std::cin,msg);
			if(!isvalid_firstname(msg))
				std::cout<<"Invalid firstname!\n";
		}
		while(!isvalid_firstname(msg));
		info+=":firstname:"+msg;

		do
		{
			std::cout<<"Lastname: ";
			getline(std::cin,msg);
			if(!isvalid_lastname(msg))
				std::cout<<"Invalid lastname!\n";
		}
		while(!isvalid_lastname(msg));
		info+=":lastname:"+msg;

		do
		{
			std::cout<<"Mail: ";
			getline(std::cin,msg);
			if(!isvalid_mail(msg))
				std::cout<<"Invalid mail!\n";
		}
		while(!isvalid_mail(msg));
		info+=":mail:"+msg;

		do
		{
			std::cout<<"Birth date: ";
			getline(std::cin,msg);
			if(!isvalid_birth_date(msg))
				std::cout<<"Invalid birth date!\n";
		}
		while(!isvalid_birth_date(msg));
		info+=":birth_date:"+msg;

		do
		{
			std::cout<<"Gender: ";
			getline(std::cin,msg);
			if(!isvalid_gender(msg))
				std::cout<<"Invalid gender!\n";
		}
		while(!isvalid_gender(msg));
		info+=":gender:"+msg;

		do
		{
			do
			{
				std::cout<<"Password: ";
				getline(std::cin,msg);
				if(!isvalid_password(msg))
					std::cout<<"Invalid password!\n";
			}
			while(!isvalid_password(msg));

			std::cout<<"Confirm password: ";
			getline(std::cin,confmsg);
		}
		while(msg!=confmsg);
		info+=":password:"+msg;

		do
		{
			std::cout<<"Login: ";
			getline(std::cin,msg);
			if(!isvalid_login(msg))
				std::cout<<"Invalid login!\n";
		}
		while(!isvalid_login(msg));
		info+=":login:"+msg+ ":";
		c->send(info);
}

///////
if(msg1=="sign in")
{
	std::string log="";
	std::string pass="";
	do
	{
		std::cout<<"Login: ";
		getline(std::cin,log);
		if(!isvalid_login(log))
			std::cout<<"Invalid login!\n";
	}
	while(!isvalid_login(log));
	do
	{
		std::cout<<"Password: ";
		getline(std::cin,pass);
		if(!isvalid_password(pass))
			std::cout<<"Invalid password!\n";
	}
	while(!isvalid_password(pass));
	std::string sign=":action:sign_in:"+log+":"+pass;
	c->send(sign);
}

	
}

void binder_recv_message(connection* c, std::string message) {
        if(message!="q" && message!="")
        {
        fifo1=message.substr(0,message.find(":"));
        fifo2=message.substr(message.find(":")+1);

        mainConnection = new connection(fifo1,fifo2);
        mainConnection->setRecvMessageCallback(recv_message_c);
        mainConnection->send(":action:help:");
        }
}
int main () {
        std::ifstream busy("busy.lock");
        if(busy.is_open())
        {
                while(busy.is_open())
                {
                        usleep(10);
                }
        }
        else
        {
                std::ofstream busy1("busy.lock");

                connection binder(std::string("in"),std::string("out"));
                binder.setRecvMessageCallback(binder_recv_message);
                binder.send("first message");
                busy1.close();
                remove("busy.lock");
        }
        while(true){}
        return 0;

}

