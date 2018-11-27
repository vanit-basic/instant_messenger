#ifndef VALID1_HPP
#define VALID1_HPP

#include "connectionUser.hpp"

void print_map(std::map<std::string, std::string>);
std::string user_information(std::map<std::string, user> , std::string );
std::map<std::string, std::string> string_to_map(std::string);
std::string map_to_string(std::map<std::string, std::string> );
std::string us_inf(std::map<std::string, user> , std::string);
bool isValidSignIn(std::map<std::string, std::pair<std::string, std::string>>, std::string, std::string);
bool isValidJoined(std::map<std::string, bool>, std::string);
bool isValidKey(std::map<std::string, std::string>, std::string);
bool isValidKey1(std::map<std::string, bool>, std::string);
bool isValidUser(std::map<std::string, std::string>, std::string);
size_t string_to_int (std::string str);
bool isValidE_mail1(std::string mail);
bool isValidE_mail2(std::map<std::string, bool>, std::string);
bool isValidName(std::string name);
bool isValidBirthDay(std::string date);
bool isValidLogin1(std::string login);
bool isValidLogin2(std::map<std::string, std::pair<std::string, std::string>>, std::string);
bool isValidGender(std::string gender);
bool isValidPassword(std::string password);
bool test(std::string& str, std::string msg);

#endif

