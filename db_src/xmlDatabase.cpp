#include "xmlDatabase.hpp"
#include <sys/stat.h>
#include <fstream>

static xmlDatabase* sharedDB = NULL;


std::string xmlDatabase::registerUser(std::string userInfo) {
	return std::string("registerUser");
}

std::string xmlDatabase::loginUser(std::string login, std::string password) {
	return std::string("loginUser");
}

bool xmlDatabase::updateUserInfo(std::string userInfo) {
	return true;
}

std::string xmlDatabase::getUserInfo(std::string userID) {
	std::string path = "db_files/users/"+userID;
	const char * p = path.c_str();
	struct stat sb;
	std::string info = "";
	if(stat(p, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		std::string temp = "";
		std::ifstream xml_file("db_files/users/"+userID+"/info.xml");
		if(xml_file.is_open()) {
			while(xml_file >> temp) {
				if(temp.substr(0, 7) == "<login>") {
					info += "</info>";
					break;
				}
				info += temp;
			}
		}
		return info;
	}
	else
		return "Error 404";

}

std::string xmlDatabase::getUserConversations(std::string userID) {
	return std::string("getUserConversations");
}

std::string xmlDatabase::getUsersConversation(std::string fromID, std::string toID) {
	return std::string("getUsersConversation");
}

bool xmlDatabase::addUserMessage(std::string messageInfo) {
	return true;
}

std::string xmlDatabase::getGroupInfo(std::string groupID) {
	return std::string("getGroupInfo");
}

std::string xmlDatabase::getGroupConversation(std::string groupID) {
	return std::string("getGroupConversation");
}

std::string xmlDatabase::updateGroupInfo(std::string groupInfo) {
	return std::string("updateGroupInfo");
}

bool xmlDatabase::addGroupMessage(std::string messageInfo) {
	return true;
}

xmlDatabase* xmlDatabase::getShared() {
	return sharedDB;
}

xmlDatabase::xmlDatabase() {
	if(NULL == sharedDB) sharedDB = this;

}

xmlDatabase::~xmlDatabase() {

}

