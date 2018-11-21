#ifndef VERIFICATION_HPP
#define VERIFICATION_HPP
#include<string>
#include<map>
bool isvalid_firstname(std::string);
bool isvalid_lastname(std::string);
bool isvalid_mail(std::string);
bool isvalid_gender(std::string);
bool isvalid_birth_date(std::string);
bool isvalid_login(std::string);
bool isvalid_password(std::string);
std::string global(std::map<std::string,std::string>);
#endif
