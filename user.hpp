#ifndef USER_HPP
#define USER_HPP
#include<string>
#include<map>
class user
{
        private:
                int id;
                std::string firstname;
                std::string lastname;
                std::string mail;
                std::string birth_date;
                std::string gender;
                std::string login;
        public:
		void set_id(int);
		void set_firstname(std::string);
		void set_lastname(std::string);
		void set_mail(std::string);
		void set_birth_date(std::string);
		void set_gender(std::string);
		void set_login(std::string);

		int get_id();
		std::string get_firstname();
		std::string get_lastname();
		std::string get_mail();
		std::string get_birth_date();
		std::string get_gender();
		std::string get_login();
		user(){}
                user(std::map<std::string,std::string>);
                ~user();
};

#endif
