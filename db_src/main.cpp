#include <iostream>

#include "xmlDatabase.hpp"

int main () {
	
	database *db = new xmlDatabase;
	
	std::cout << db->registerUser(std::string("user info xml")) << std::endl;
	
	std::cout << db->loginUser(std::string("test1"), std::string("pass1234")) << std::endl;
	
	std::cout << db->updateUserInfo(std::string("user info xml")) << std::endl;
	
	std::cout << db->getUserInfo(std::string("u2")) << std::endl;
	
	std::cout << db->getUserConversations(std::string("u89")) << std::endl;
	
	std::cout << db->getUsersConversation(std::string("u23"), std::string("u567")) << std::endl;
	
	std::cout << db->addUserMessage(std::string("message xml")) << std::endl;
	
	std::cout << db->getGroupInfo(std::string("g5")) << std::endl;
	
	std::cout << db->getGroupConversation(std::string("g67")) << std::endl;
	
	std::cout << db->updateGroupInfo(std::string("group info xml")) << std::endl;
	
	std::cout << db->addGroupMessage(std::string("message xml")) << std::endl;

	return 0;
}
