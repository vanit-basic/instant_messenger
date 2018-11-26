#ifndef USER_HPP
#define USER_HPP

#include <string>

enum gender {
        other = -1,
        male,
        female
};


class user
{
	private: 
		std::string firstName; 
		std::string lastName; 
		gender gen; 
		std::string id; 
		std::string birthDate;
		std::string email; 
		std::string login;

	public:
		void setFirstName (std::string); 
		void setLastName (std::string); 
		void setGender (gender); 
		void setId (std::string); 
		void setBirthDate (std::string); 
		void setEmail (std::string); 
		void setLogin (std::string);

		std::string getFirstName();
                std::string getLastName();
                gender getGen();        
                std::string getId();
                std::string getBirthDate();
                std::string getEmail();
                std::string getLogin();

		user(); 
		~user(); 

};

#endif 
