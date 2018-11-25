#ifndef USER_HPP
#define USER_HPP
#include <map>

class user {

        std::string firstname;
        std::string lastname;
        std::string birth_date;
        std::string gender;
        std::string mail;
        std::string id;
        std::string login;

        public:
        void setFirstname(std::string firstname);
        void setLastname(std::string Lastname);
        void setBirth_date(std::string birth_date);
        void setGender(std::string gender);
        void setMail(std::string mail);
        void setId(std::string id);
        void setLogin(std::string login);

        std::string getFirstname();
        std::string getLastname();
        std::string getBirth_date();
        std::string getGender();
        std::string getMail();
        std::string getId();
        std::string getLogin();


        user(std::map<std::string, std::string> m_map);
        user(){}
        ~user(){}
};

#endif
