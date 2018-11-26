#include "user.hpp"
#include <iostream>
#include <regex>

void user::setFirstName (std::string name)
{ 
	this->firstName = name;
}

std::string user::getFirstName()
{
        return this->firstName;
}

void user::setLastName (std::string name)
{
                this->lastName = name;
}

std::string user::getLastName()
{
        return this->lastName;
}

void user::setBirthDate(std::string date)
{
        
        this->birthDate = date;
}

std::string user::getBirthDate()
{
	return this->birthDate;
}

void user::setGender (gender g)
{
	this->gen = g; 
}

gender user::getGen()
{
	return this-> gen; 

}


std::string user::getId()
{
	return this-> id; 
}

void user::setEmail (std::string e)
{
	this->email = e; 
}

std::string user::getEmail()
{
	return this->email; 
}

void user::setLogin (std::string l) 
{
	this->login =l; 

}

std::string user::getLogin()
{
	return this->login; 

}

user::user()
{

}

user::~user()
{

}
