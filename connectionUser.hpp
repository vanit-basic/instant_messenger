#ifndef CONNECTIONUSER_HPP
#define CONNECTIONUSER_HPP

#include <fstream>
#include <string>
#include <thread>
#include <map>

class connection;
class user;
typedef void (*recvCallback) (connection*, std::string);

class connection
{
        private:
                std::string id;
                std::string input_name;
                std::string output_name;
                std::ifstream input;
                std::ofstream output;
                recvCallback recvMessageCallback;

                std::thread readerThread;

                void read();

        public:
                void send(std::string message);
                void stop();
                void setRecvMessageCallback(recvCallback clbk);
                void setId(std::string);
                std::string getId();
                connection(std::string, std::string);
                ~connection();
};

class user
{
        private:
                std::string name;
                std::string surname;
                std::string birthday;
                std::string gender;
                std::string email;
                std::string login;
                std::string id;
                std::string phone;
        public:
                void set_name(std::string);
                void set_surname(std::string);
                void set_birthday(std::string);
                void set_gender(std::string);
                void set_email(std::string);
                void set_login(std::string);
                void set_id(std::string);
                void set_phone(std::string);

                std::string get_name();
                std::string get_surname();
                std::string get_birthday();
                std::string get_gender();
                std::string get_email();
                std::string get_login();
                std::string get_id();
                std::string get_phone();

                user(){}
                user(std::map<std::string, std::string>);
                ~user();
};

#endif

