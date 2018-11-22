#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "connection.hpp"

bool isFileExist(std::string fileName) {
	struct stat buffer;
	return (stat (fileName.c_str(), &buffer) == 0);
}

void connection::read() {
	if(input.is_open()) {
		std::string msg = "";
		while(true) {
			getline(input, msg);
				if("q" == msg) {
					break;
				}
		//	if("" != msg) {
				recvMessageCallback(this, msg);

			//}
			usleep(100000);
		}
	}
}

void connection::send(std::string message) {
	if(output.is_open()) {
		output << message << std::endl;
	} else {
		std::cout << "cant open output" << std::endl;
	}
}

void connection::setRecvMessageCallback(recvCallback clbk) {
	recvMessageCallback = clbk;
}

connection::connection(std::string in , std::string out) {
	if(! isFileExist(in)) {
		mkfifo(in.c_str(), 0666);
	}

	if(! isFileExist(out)) {
		mkfifo(out.c_str(), 0666);
	}

	input = std::ifstream(in, std::ios::in | std::ios::out);
	output = std::ofstream(out, std::ios::in | std::ios::out);

	input_name = in;
	output_name = out;

	readerThread = std::thread(&connection::read, this);
}
void connection::setId(std::string ID) {
	this->id=ID;
}
std::string connection::getId() {
	return this->id;
}
connection::~connection() {

	readerThread.join();

	input.close();
	output.close();
	if(this->id != "Client")
	{
	std::remove(input_name.c_str());
	std::remove(output_name.c_str());
	}	
}
void user::setFirstName(std::string firstname) {
	this->FirstName = firstname;
}
void user::setLastName(std::string lastname) {
	this->LastName = lastname;
}
void user::setBirthDate(std::string birthdate) {
	this->BirthDate = birthdate;
}
void user::setLogin(std::string login) {
	this->Login = login;
}
void user::setGender(std::string gender) {
	this->Gender = gender;
}
void user::setEmail(std::string email) {
	this->Email = email;
}
void user::setId(std::string id) {
	this->Id = id;
}
std::string user::getFirstName() {
	return this->FirstName;
}
std::string user::getLastName() {
	return this->LastName;
}
std::string user::getBirthDate() {
	return this->BirthDate;
}
std::string user::getLogin() {
	return this->Login;
}
std::string user::getGender() {
	return this->Gender;
}
std::string user::getEmail() {
	return this->Email;
}
std::string user::getId() {
	return this->Id;
}
user::user(std::map<std::string, std::string> userInfo) {
	this->FirstName = userInfo["Firstname"];
	this->LastName = userInfo["Lastname"];
	this->BirthDate = userInfo["BirthDate"];
	this->Login = userInfo["Login"];
	this->Gender = userInfo["Gender"];
	this->Email = userInfo["Email"];
	this->Id = userInfo["ID"];
}
