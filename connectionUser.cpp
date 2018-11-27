#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "connectionUser.hpp"

bool isFileExist(std::string fileName) {
        struct stat buff;
        return (stat(fileName.c_str(), &buff)==0);
}

void connection::setId(std::string str)
{
        this->id=str;
}
std::string connection::getId()
{
        return this->id;
}
void connection::read() {
        if(input.is_open()) {
                std::string msg = "";
                while(true) {
                        getline(input, msg);
                        if("" != msg) {
                                recvMessageCallback(this, msg);
                                if("quit" == msg) {
                                        break;
                                }
                        }
                        usleep(1000);
                }
        }
}

void connection::send(std::string message) {
        if(output.is_open()) {
                output << message << std::endl;
        } else {
                std::cout << "cant open output" << "\n";
        }
}

void connection::setRecvMessageCallback(recvCallback clbk) {
        recvMessageCallback = clbk;
}

connection::connection(std::string in , std::string out) {
        if(! isFileExist(in)) {
                mkfifo(in.c_str(), 0666);
        }

        if(! isFileExist(out)) {
                mkfifo(out.c_str(), 0666);
        }

        input = std::ifstream(in, std::ios::in | std::ios::out);
        output = std::ofstream(out, std::ios::in | std::ios::out);

        input_name = in;
        output_name = out;

        readerThread = std::thread(&connection::read, this);
}
void connection::stop()
{
        readerThread.detach();
}

connection::~connection() {
 readerThread.join();

        input.close();
        output.close();
        if((this->id) != "Client")
        {
        std::remove(input_name.c_str());
        std::remove(output_name.c_str());
        }
}

void user::set_name(std::string name)
{
        this->name=name;
}
void user::set_surname(std::string surname)
{
        this->surname=surname;
}
void user::set_birthday(std::string birth_day)
{
        this->birthday=birth_day;
}
void user::set_gender(std::string gen)
{
        this->gender=gen;
}
void user::set_email(std::string mail)
{
        this->email=mail;
}
void user::set_login(std::string log)
{
        this->login=log;
}
void user::set_user_id(std::string id)
{
        this->id=id;
}
void user::set_phone(std::string p_num)
{
        this->phone=p_num;
}

std::string user::get_name()
{
return this->name;
}
std::string user::get_surname()
{
return this->surname;
}
std::string user::get_birthday()
{
return this->birthday;
}
std::string user::get_gender()
{
return this->gender;
}
std::string user::get_email()
{
        return this->email;
}
std::string user::get_login()
{
        return this->login;
}
std::string user::get_id()
{
        return this->id;
}
std::string user::get_phone()
{
        return this->phone;
}
user::user(std::map<std::string, std::string> user_inf)
{
        this->name=user_inf["Name"];
        this->surname=user_inf["Surname"];
        this->birthday=user_inf["Birthday"];
        this->gender=user_inf["Gender"];
        this->email=user_inf["Email"];
        this->login=user_inf["Login"];
        this->id=user_inf["User_id"];
        this->phone=user_inf["Phone"];
}
~user()
{}

