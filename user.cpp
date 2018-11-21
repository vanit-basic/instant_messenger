#include <iostream>
#include <string>
#include "user.h"

void user::setFirstName(std::string firstname){
	if(nameValid(firstname)){
		this->firstname=firstname;
	}
}
void user::setLastName(std::string lastname){
        if(nameValid(lastname)){
                this->lastname=lastname;
        }
}
void user::setBirthDate(std::string birthdate){
	if(dateValid(birthdate)){
		this->birthdate=birthdate;
	}
}
void user::setGender(std::string gender){
	if(genderValid(gender)){
		this->gender=gender;
	}
}
void user::setLogin(std::string login){
	if(loginValid(login)){
		this->login=login;
	}
}
void user::setId(std::string id){
		this->id=id;		
}
void user::setMail(std::string mail){
	if(mailValid(mail)){
		this->mail=mail;
	}
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
