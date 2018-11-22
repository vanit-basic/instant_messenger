#ifndef CONNECTIONANDUSER_HPP
#define CONNECTIONANDUSER_HPP

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
                std::string FirstName;
                std::string LastName;
                std::string BirthDate;
                std::string gender;
                std::string login;
                std::string email;
                std::string id;
                std::string user_connection;
        public:
                void setFirstName(std::string);
                std::string getFirstName();
                void setLastName(std::string);
                std::string getLastName();
                void setBirthDate(std::string);
                std::string getBirthDate();
                void setGender(std::string);
                std::string getGender();
                void setLogin(std::string);
                std::string getLogin();
                void setEmail(std::string);
                std::string getEmail();
                void setId(std::string);
                std::string getId();
                void setUser_connection(std::string);
                std::string getUser_connection();
                user(std::map<std::string, std::string>);
                user(){}
                ~user(){}
};

#endif
