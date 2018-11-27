#ifndef CONNECTIONUSER_H
#define CONNECTIONUSER_H

#include <mutex>
#include <iostream>
#include <fstream>
#include <map>
#include <thread>
#include <string>

class connection;

typedef void (*recvCallback) (connection*, std::string);


void recv_message_client(connection*, std::string);
void recv_message(connection*, std::string);

std::string regist(std::string, std::string);
void recv_message_server(connection*, std::string);
void recv_message(connection*, std::string);
bool isValidName(std::string);
bool isValidSurname(std::string);
bool isValidBirthdate(std::string);
bool isValidGender(std::string);
bool isValidLogin(std::string);
bool isValidPass(std::string);
bool isValidMail(std::string mail);

class connection {
    private:
        std::string id;
        std::string input_name;
        std::string output_name;

        std::fstream input;
        std::fstream output;

        recvCallback recvMessageCallback;
        std::thread readerThread;

        void read();

    public:
        void setID(std::string id);
        std::string getID();
        void send(std::string message);

        void setRecvMessageCallback(recvCallback clbk);

        connection(std::string, std::string);
        ~connection();
};

class User {
    private:
        std::string name;
        std::string surname;
        std::string birthdate;
        std::string gender;
        std::string id;
        std::string login;
        std::string mail;

    public:
        std::string getName();
        std::string getSurname();
        std::string getBirthdate();
        std::string getGender();
        std::string getID();
        std::string getLogin();
        std::string getMail();

        void setName(std::string name);
        void setSurname(std::string surname);
        void setBirthdate(std::string birthdate);
        void setGender(std::string gender);
        void setID(std::string id);
        void setLogin(std::string login);
        void setMail(std::string mail);

        User(std::map<std::string, std::string>);
        ~User();
};

#endif
