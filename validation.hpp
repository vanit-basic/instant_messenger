#ifndef VALIDATION_HPP
#define VALIDATION_HPP


bool valid_name(std::string name);
bool valid_birthdate(std::string date);
bool valid_login(std::string login);
bool valid_gender(std::string gender);
bool valid_mail(std::string mail);
bool valid_password(std::string password);
std::string infos(std::map<std::string, user> m_map, std::string id);

#endif
