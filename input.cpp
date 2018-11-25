#include "verification.hpp"
#include<iostream>
#include<string>
std::string registr()
{
	std::string info=":action:registration";
	std::string msg="";
	std::string confmsg="";
	std::cout<<"Enter your information\n";

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
	return info;
}
std::string sign_in()
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
	return sign;
}
void input(connection* c)
{
        std::string msg1="";
        std::cout<<"You allowed following action:view user data, send message another user, create a new group, send message to group or quit"<<std::endl;
        do
        {
                std::cout<<"For view users ID enter 'users' , for send message another user enter 'send' , for creat a new group enter 'group' , for send message to group enter 'send group' , for quit enter 'quit'"<<std::endl;
                getline(std::cin,msg1);
                if(msg1!="users" && msg1!="send" && msg1!="group" && msg1!="send group" && msg1!="quit")
                        std::cout<<"\tInvalid action\n";
        }
        while(msg1!="users" && msg1!="send" && msg1!="group" && msg1!="send group" && msg1!="quit");


        if(msg1=="users")
                c->send("show users id");

        if(msg1=="send")
        {
                std::string user_id="";
                std::string text="";
                std::cout<<"Enter user id : ";
                getline(std::cin,user_id);
                std::cout<<"Enter message: ";
                getline(std::cin,text);
                std::string sms=":action:send_message:"+user_id+":"+text;
                c->send(sms);
        }
        if(msg1=="group")
                c->send("create group");
        if(msg1=="send group")
        {
                //kisat
                c->send(msg1);
        }
        if(msg1=="quit")
        {
                c->send(msg1);
        }

}

