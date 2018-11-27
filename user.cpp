#include "connectionUser.h"

#include <string>
#include <iostream>
#include <map>

std::string User::getName() {
    return this->name;
}

std::string User::getSurname() {
    return this->surname;
}

std::string User::getBirthdate() {
    return this->birthdate;
}

std::string User::getGender() {
    return this->gender;
}

std::string User::getID() {
    return this->id;
}

std::string User::getLogin() {
    return this->login;
}

std::string User::getMail() {
    return this->mail;
}

void User::setName(std::string name) {
    this->name = name;
}

void User::setSurname(std::string surname) {
    this->surname = surname;
}

void User::setBirthdate(std::string birthdate) {
    this->birthdate = birthdate;
}

void User::setGender(std::string gender) {
    this->gender = gender;
}

void User::setID(std::string id) {
    this->id = id;
}

void User::setLogin(std::string login) {
    this->login = login;
}

void User::setMail(std::string mail) {
    this->mail = mail;
}

User::User(std::map<std::string, std::string> myMap) {
    int n = myMap.size();
    for (auto iter = myMap.begin(); iter != myMap.end(); ++iter) {
        if (iter->first == name) {
            setName(iter->second);
        } else if (iter->first == surname) {
            setSurname(iter->second);
        } else if (iter->first == birthdate) {
            setBirthdate(iter->second);
        } else if (iter->first == gender) {
            setGender(iter->second);
        } else if (iter->first == id) {
            setID(iter->second);
        } else if (iter->first == login) {
            setLogin(iter->second);
        } else if (iter->first == mail) {
            setMail(iter->second);
        }
    }
}

User::~User() {}
