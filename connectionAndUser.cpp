#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "connectionAndUser.hpp"


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
void user::setFirstName(std::string first_name)
{
        this->FirstName = first_name;
}

std::string user::getFirstName()
{
        return this -> FirstName;
}
void user::setLastName(std::string last_name)
{
        this->LastName = last_name;
}
std::string user::getLastName()
{
        return this -> LastName;
}
void user::setBirthDate(std::string b_d)
{
        this -> BirthDate = b_d;
}
std::string user::getBirthDate()
{
        return this -> BirthDate;
}
void user::setGender(std::string gen)
{
        this -> gender = gen;
}
std::string user::getGender()
{
        return this -> gender;
}
void user::setLogin(std::string log)
{
        this -> login = log;
}
std::string user::getLogin()
{
        return this -> login;
}
void user::setEmail(std::string mail)
{
        this -> email = mail;
}
std::string user::getEmail()
{
        return this -> email;
}
void user::setId(std::string ID)
{
        this -> id = ID;
}
std::string user::getId()
{
        return this -> id;
}
void user::setUser_connection(std::string con)
{
        this-> user_connection = con;
}
std::string user::getUser_connection()
{
        return this->user_connection;
}

user::user(std::map<std::string, std::string> datebase)
{
        this->FirstName = datebase["FirstName"];
        this->LastName = datebase["LastName"];
        this->BirthDate = datebase["BirhDate"];
        this->gender = datebase["Gender"];
        this->login = datebase["Login"];
        this->email = datebase["Email"];
        this->id = datebase["Id"];
        this->user_connection = datebase["user_connection"];
}
