#ifndef FUNCTION_CLIENT_HPP
#define FUNCTION_CLIENT_HPP
#include<string>
#include "connection.hpp"
void recv_message(connection* c1,std::string message);
void binder_recv_message(connection* c, std::string firstMessage);
void r_l_q(connection*);
std::string reg_email(connection*);
std::string reg_login(connection*);
std::string reg_name();
std::string reg_surname();
std::string reg_birthday();
std::string reg_gender();
std::string reg_phone();
void reg_password();
std::string reg_password1(connection*);
void all_information(connection*);
std::string email_busy(connection*);
std::string login_busy(connection*);
void login_password(connection*);
std::string sign_in(connection*);
std::string send_message();

#endif
