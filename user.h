#ifndef user_h
#define user_h

class user{
	private:
		std::string firstname;
		std::string lastname;
		std::string birthdate;
		std::string gender;
		std::string login;
		std::string id;
		std::string mail;
	public:
		void setFirstName(std::string);
		void setLastName (std::string);
		void setBirthDate(std::string);
		void setGender   (std::string);
		void setLogin    (std::string);
		void setId       (std::string);
		void setMail     (std::string);
		std::string getFirstName();
		std::string getLastName ();
		std::string getBirthDate();
		std::string getGender   ();
		std::string getLogin	();
		std::string getId	();
		std::string getMail	();
		std::string getDetails  ();
		user(){};
		~user(){};
};
		
bool nameValid  (std::string);
bool dateValid  (std::string);
bool genderValid(std::string);
bool loginValid (std::string);
bool mailValid  (std::string);	

std::string rba(std::string mail);
std::string raa(std::string mail);
#endif
