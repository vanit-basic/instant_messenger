#include<fstream>
#include<stdio.h>
#include "xmlDatabase.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
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
	return std::string("getUserInfo");
}

std::string xmlDatabase::getUserConversations(std::string userID) {
	std::string tmp = "";
        std::string fin = "";
        std::ifstream id("db_files/users/"+userID+"/convs/convs_list.xml");
        while(id >> tmp)
                fin = fin +tmp;
        return fin;
}

std::string xmlDatabase::getUsersConversation(std::string fromID, std::string toID) {
	std::string tmp = "";
        std::string fin = "";
        std::ifstream id("db_files/users/"+fromID+"/convs/"+toID);
        while(id >> tmp)
                fin = fin +tmp;
        return fin;
}


bool xmlDatabase::addUserMessage(std::string messageInfo) {
	return true;
}

std::string xmlDatabase::getGroupInfo(std::string groupID) {
	std::string str="";
	std::string res="";
	try{
		std::string groups= "db_files/groups/"+groupID;
		const char* x = groups.c_str();
		struct stat sb;
		if (!(stat(x, &sb) == 0 && S_ISDIR(sb.st_mode)))
			throw 404;

		std::ifstream xml("db_files/groups/"+groupID+"/ginfo.xml");
		while(xml>>str)
			res+=str;
	}
	catch(int x){
		printf("Error %d ! File not exist!",x);
		//std::cout<<"Error "<<x<<"! File not exist!"<<std::endl;
	}
	return res;
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

