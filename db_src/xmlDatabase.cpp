#include<fstream>
#include<stdio.h>
#include "xmlDatabase.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

static xmlDatabase* sharedDB = NULL;

std::string xmlDatabase::registerUser(std::string userInfo) {
	return std::string("registerUser");
}

std::string xmlDatabase::loginUser(std::string login, std::string password) {
	// Open directory with login name
    	DIR* loginDir = opendir(login.c_str());
    if (!loginDir) {
        // If there is not directory with such name then login and / or password is not available
        std::cout << "Your login and / or password is not available! Please, try again!" << std::endl;
    } else {
        // Open pass.txt
        std::string path = "./" + login + "/pass.txt";
        std::ifstream passFile(path.c_str());
        if (passFile.is_open()) {
            std::string tempPass;
            // If password matches print user id
            if (std::getline(passFile, tempPass)) {
                if (password.compare(tempPass) == 0) {
                    std::string id = "";
                    if (std::getline(passFile, id)) {
                        return id;
                    }
            } else {
                // Login and / or pass is not available
                std::cout << "Your login and / or password is not aveilable! Please, try again!" << std::endl;
            }
        }
        passFile.close();
    } else {
        std::cout << "Error 404 not found" << std::endl;
    }
}
    closedir(loginDir);
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
	std::ifstream xml("db_files/groups/"+groupID+"/ginfo.xml");
	while(xml>>str)
		res+=str;
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

std::string xmlDatabase::createGroup(std::string groupInfo) {
	return std::string("groupID");
}

bool xmlDatabase::deleteGroup(std::string groupInfo) {
	return true;
}

bool removeFromGroup(std::string groupID) {
	return true;
}

bool removeMessage(std::string messageInfo) {
	return true;
}

bool removeGroupConversation(std::string groupInfo) {
	return true;
}

xmlDatabase::xmlDatabase() {
	if(NULL == sharedDB) sharedDB = this;
}

xmlDatabase::~xmlDatabase() { }

