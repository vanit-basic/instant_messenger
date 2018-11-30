#ifndef FUNCTION_SERVER_HPP
#define FUNCTION_SERVER_HPP
#include<string>
#include <map>
#include "connection.hpp"
void recv_message(connection* s1, std::string message);
void binder_recv_message(connection* s, std::string firstMessage);
std::string userToString(std::map<int,user> id_user,int user_id);
std::map<std::string,std::string> stringToMap(std::string str);
void find_email(std::string,connection*);
void find_login(std::string,connection*);
void insert_maps(std::string ,connection*);
void sign_in(connection* ,std::string message);
void all_users(connection*);
std::string message_to_user(std::string message,connection*);
int return_id(std::string message);
#endif

