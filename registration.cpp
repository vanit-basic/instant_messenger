#include "verification.hpp"
#include<iostream>
#include<string>
std::string registr()
{
	std::string info=":action:registration";
	std::string msg="";
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






