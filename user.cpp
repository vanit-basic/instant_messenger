#include "user.hpp"

void user::setFirstname(std::string firstname) {
        this->firstname = firstname;
}
void user::setLastname(std::string lastname) {
        this->lastname = lastname;
}
void user::setBirth_date(std::string birth_date) {
        this->birth_date = birth_date;
}
void user::setGender(std::string gender) {
        this->gender = gender;
}
void user::setMail(std::string mail) {
        this->mail = mail;
}
void user::setId(std::string id) {
        this->id = id;
}
void user::setLogin(std::string login) {
        this->login = login;
}


std::string user::getFirstname() {
        return this->firstname;
}
std::string user::getLastname() {
        return this->lastname;
}
std::string user::getBirth_date() {
        return this->birth_date;
}
std::string user::getGender() {
        return this->gender;
}
std::string user::getMail() {
        return this->mail;
}
std::string user::getId() {
        return this->id;
}
std::string user::getLogin() {
        return this->login;
}


user::user(std::map<std::string, std::string> m_map) {
        this->firstname = m_map["firstname"];
        this->lastname = m_map["lastname"];
        this->birth_date = m_map["birth_date"];
        this->gender = m_map["gender"];
        this->mail = m_map["mail"];
        this->id = m_map["id"];
}
