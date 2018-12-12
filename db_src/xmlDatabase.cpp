#include<fstream>
#include<stdio.h>
#include "xmlDatabase.hpp"

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
	return std::string("getUserInfo");
}

std::string xmlDatabase::getUserConversations(std::string userID) {
	return std::string("getUserConversations");
}

std::string xmlDatabase::getUsersConversation(std::string fromID, std::string toID) {
	std::string tmp = "";
        std::string fin = "";
        std::ifstream id("db_files/conversation/"+fromID+toID+".xml");

        while(id >> tmp)
                fin = fin +tmp;
        return fin;
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

