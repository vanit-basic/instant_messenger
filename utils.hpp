#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

size_t string_to_int (std::string str);
bool isValidE_mail(std::string mail);
bool isValidName(std::string name);
bool isValidBirthDate(std::string date);
bool isValidLogin(std::string login);
bool isValidGender(std::string gender);
bool isValidPassword(std::string password);
bool test(std::string& str, std::string msg);


#endif
