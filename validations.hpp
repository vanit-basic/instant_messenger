#ifndef VALIDATIONS_HPP 
#define VALIDATIONS_HPP 

#include <string>
#include <map>
typedef std::map<std::string, std::string> Map;


bool isValidFirstName(std::string); 
bool isValidLastName(std::string); 
bool isValidEmail(std::string); 
bool isValidGender(std::string); 
bool isValidBirthDate(std::string); 
bool isValidPassword(std::string); 
std::string userInfo (std::string); 
Map myMap(std::string userInfo);
std::string userInformation (Map infoMap);
bool email(std::string mail);
bool login(std::string login);



#endif
