#include "user.hpp"
#include <map>
#include <string>
void user::set_id(int id)
{
	this->id=id;
}
void user::set_firstname(std::string fname)
{
	this->firstname=fname;
}
void user::set_lastname(std::string lname)
{
	this->lastname=lname;
}
void user::set_mail(std::string mail)
{
	this->mail=mail;
}
void user::set_birth_date(std::string birth_date)
{
	this->birth_date=birth_date;
}
void user::set_gender(std::string gen)
{
	this->gender=gen;
}
void user::set_login(std::string log)
{
	this->login=log;
}

int user::get_id()
{
	return this->id;
}
std::string user::get_firstname()
{
	return this->firstname;
}
std::string user::get_lastname()
{
	return this->lastname;
}
std::string user::get_mail()
{
	return this->mail;
}
std::string user::get_birth_date()
{
	return this->birth_date;
}
std::string user::get_gender()
{
	return this->gender;
}
std::string user::get_login()
{
	return this->login;
}
user::user(std::map<std::string,std::string> mymap)
{
	this->firstname=mymap["firstname"];
	this->lastname=mymap["lastname"];
	this->mail=mymap["mail"];
	this->birth_date=mymap["birth_date"];
	this->gender=mymap["gender"];
	this->login=mymap["login"];
	this->id=stoi(mymap["id"]);
}
user::~user()
{
}
