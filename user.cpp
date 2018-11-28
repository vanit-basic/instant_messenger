#include <iostream>
#include <string>
#include "user.h"

void user::setFirstName(std::string firstname){
		this->firstname=firstname;
}
void user::setLastName(std::string lastname){
                this->lastname=lastname;
}
void user::setBirthDate(std::string birthdate){
		this->birthdate=birthdate;
}
void user::setGender(std::string gender){
		this->gender=gender;
}
void user::setLogin(std::string login){
		this->login=login;
}
void user::setId(std::string id){
		this->id=id;		
}
void user::setMail(std::string mail){
		this->mail=mail;
}
std::string user::getFirstName(){
	return firstname;
}
std::string user::getLastName(){
        return lastname;
}
std::string user::getBirthDate(){
        return birthdate;
}
std::string user::getGender(){
        return gender;
}
std::string user::getLogin(){
        return login;
}
std::string user::getId(){
        return id;
}
std::string user::getMail(){
        return mail;
}
std::string user::getDetails(){
	std::string info = "";
	info += "ID : " + this->getId() + "\n";
	info += "firstname : " + this->getFirstName() + "\n";
	info += "lastname : " + this->getLastName() + "\n";
	info += "gender : " + this->getGender() + "\n";
	info += "birth date : " + this->getBirthDate() + "\n";
	info += "mail : " + this->getMail() + "\n";
	info += "login : " + this->getLogin() + "\n";
	return info;
}

user::user(std::map<std::string,std::string> datebase){
	this->firstname = datebase["FirstName"];
        this->lastname = datebase["LastName"];
        this->birthdate = datebase["BirthDate"];
        this->gender = datebase["Gender"];
        this->login = datebase["Login"];
        this->mail = datebase["Mail"];
        this->id = datebase["Id"];
}

