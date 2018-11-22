#ifndef USER_HPP
#define USER_HPP
#include<string>
#include<map>
class user
{
        private:
                std::string login;
                std::string user_id;
                std::string name;
                std::string surname;
                std::string email;
                std::string birthday;
		std::string phone;
                std::string gender;
        public:
		void set_login(std::string);
		void set_user_id(std::string);
		void set_name(std::string);
		void set_surname(std::string);
		void set_email(std::string);
		void set_birthday(std::string);
		void set_phone(std::string);
		void set_gender(std::string);

		std::string get_login();
		std::string get_user_id();
		std::string get_name();
		std::string get_surname();
		std::string get_email();
		std::string get_birthday();
		std::string get_phone();
		std::string get_gender();
                user(std::map<std::string,std::string>);
                ~user();
};

#endif
