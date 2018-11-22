#ifndef 
#define

#include <iostream>
#include <map>
#include <string>

class user {
	private:
		std::string name;
		std::string surname;
		std::string birthdate;
		std::string gender;
		std::string id;
		std::string login;
		std::string mail;
	
	public:
		std::string getName(std::string name);
		std::string getSurname(std::string surname);
		std::string getBirthdate(std::string birthdate);
		std::string getGender(std::string gender);
		std::string getID(std::string id);
		std::string getLogin(std::string login);
		std::string getMail(std::string mail);
		
		void setName(std::string name);
		void setSurname(std::string surname);
		void setBirthdate(std::string birthdate);
		void setGender(std::string gender);
		void setID(std::string id);
		void setLogin(std::string login);
		void setMail(std::string mail);

		user(std::map);
		~user();
};

#endif
