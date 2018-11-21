#ifndef UTILS_HPP
#define UTILS_HPP

#include "connectionAndUser.hpp"
#include <string>
#include <map>

void string_to_map(std::map<std::string, std::string>, std::string);
std::string user_information(std::map<std::string, user*> , std::string );
bool isValidSignIn(std::map<std::string, std::pair<std::string, std::string>*>, std::string, std::string, std::string&);
std::string map_to_string(std::map<std::string, std::string> datebase);
void string_to_map_and_log_pass(std::map<std::string, std::string>&, std::string msg, std::string& log, std::string& pass);
size_t string_to_int (std::string str);
bool isValidE_mail1(std::string mail);
bool isValidE_mail2(std::map<std::string, bool>, std::string);
bool isValidName(std::string name);
bool isValidBirthDate(std::string date);
bool isValidLogin1(std::string login);
bool isValidLogin2(std::map<std::string, std::pair<std::string, std::string>*>, std::string);
bool isValidGender(std::string gender);
bool isValidPassword(std::string password);
bool test(std::string& str, std::string msg);


#endif
