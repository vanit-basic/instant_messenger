#include "user.hpp"
#include <map>
#include <string>
#include <iostream>
void user::set_login(std::string log)
{
	this->login=log;
}
void user::set_user_id(std::string id)
{
	this->user_id=id;
}
void user::set_name(std::string name)
{
	this->name=name;
}
void user::set_surname(std::string s_name)
{
	this->surname=s_name;
}
void user::set_email(std::string mail)
{
	this->email=mail;
}
void user::set_birthday(std::string birth_day)
{
	this->birthday=birth_day;
}
void user::set_phone(std::string phone_num){
	this->phone=phone_num;
}
void user::set_gender(std::string gen)
{
	this->gender=gen;
}

std::string user::get_login()
{
	return this->login;
}
std::string user::get_user_id()
{
	return this->user_id;
}
std::string user::get_name()
{
	return this->name;
}
std::string user::get_surname()
{
	return this->surname;
}
std::string user::get_email()
{
	return this->email;
}
std::string user::get_birthday()
{
	return this->birthday;
}
std::string user::get_phone()
{
        return this->phone;
}
std::string user::get_gender()
{
	return this->gender;
}
user::user(std::map<std::string,std::string> usermap)
{
	this->name=usermap["name"];
	std::cout<<"aaaaaa::"<<this->name<<std::endl;
	this->surname=usermap["surname"];
	this->email=usermap["email"];
	std::cout<<"mmmmmmm::"<<this->email<<std::endl;
	this->birthday=usermap["birthday"];
	this->phone=usermap["phone"];
	this->gender=usermap["gender"];
	this->login=usermap["login"];
	this->user_id=usermap["user_id"];
}
user::~user()
{
}
