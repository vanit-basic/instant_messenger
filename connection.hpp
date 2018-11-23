#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <fstream>
#include <string>
#include <thread>
#include <map>

class connection;
class user;
typedef void (*recvCallback) (connection*, std::string);

bool valid_name(std::string name);
bool valid_birthdate(std::string date);
bool valid_login(std::string login);
bool valid_gender(std::string gender);
bool valid_mail(std::string mail);
bool valid_password(std::string password);
std::string infos(std::map<std::string, user> m_map, std::string id);

class connection {
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
		void setId(std::string);
		std::string getId();
		void setRecvMessageCallback(recvCallback clbk);

		connection(std::string, std::string);
		~connection();
};

class user {
	private:
		std::string FirstName;
		std::string LastName;
		std::string BirthDate;
		std::string Login;
		std::string Gender;
		std::string Email;
		std::string Id;
	public:
		void setFirstName(std::string);
		void setLastName(std::string);
		void setBirthDate(std::string);
		void setLogin(std::string);
		void setGender(std::string);
		void setEmail(std::string);
		void setId(std::string);
		std::string getFirstName();
		std::string getLastName();
		std::string getBirthDate();
		std::string getLogin();
		std::string getGender();
		std::string getEmail();
		std::string getId();
		user(std::map<std::string, std::string>);
		user(){}
		~user(){}
};
#endif

