#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <map>

void string_to_map(std::map<std::string, std::string>, std::string msg);
std::string map_to_string(std::map<std::string, std::string> datebase);
void string_to_map_and_log_pass(std::map<std::string, std::string>, std::string msg, std::string& log, std::string& pass);
size_t string_to_int (std::string str);
bool isValidE_mail(std::string mail);
bool isValidName(std::string name);
bool isValidBirthDate(std::string date);
bool isValidLogin(std::string login);
bool isValidGender(std::string gender);
bool isValidPassword(std::string password);
bool test(std::string& str, std::string msg);


#endif
