#include <iostream>
#include <regex>
#include <string>
#include <map>
#include "user.hpp"
std::string replace_before_at (std::string mail);
std::string replace_after_at (std::string mail);
bool firstname_valid (std::string firstname);
bool lastname_valid (std::string lastname);
bool gender_valid (std::string gender);
bool birth_date_valid (std::string birth_date);
bool email_valid (std::string email);
bool email_valid2(std::map<std::string, bool>, std::string);
bool login_valid (std::string login);
bool login_valid2 (std::map<std::string, std::pair<std::string, std::string>>, std::string);
bool password_valid (std::string password);
std::string global_validation (std::map<std::string,std::string> m_map);
std::map<std::string, std::string> strToMap (std::string map_conv);
std::string mapToStr (std::map<std::string, std::string> m_map);
std::string info(std::map<std::string, user> m_map, std::string id);
bool join_valid (std::map<std::string, bool> join, std::string login);
bool sign_in_valid (std::map<std::string, std::pair<std::string, std::string>> m_map, std::string login, std::string user_id, std::string password);
