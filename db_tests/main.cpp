#include <iostream>

#include <xmlDatabase.hpp>
/*
registerUser(std::string userInfo)
loginUser(std::string login, std::string password)
getUserInfo(std::string userID)
getUserConversations(std::string userID)
getUsersConversation(std::string fromID, std::string toID)
createGroup(std::string groupInfo)
getGroupInfo(std::string groupID)
getGroupConversation(std::string groupID)
updateGroupInfo(std::string groupInfo)
updateUserInfo(std::string userInfo)
addUserMessage(std::string messageInfo)
deleteGroup(std::string groupID)
addUserToGroup(std::string groupID, std::string userID)
removeFromGroup(std::string groupID, std::string userID)
removeMessage(std::string messageInfo)
removeGroupConversation(std::string groupInfo)
addGroupMessage(std::string messageInfo)
*/

void registerLoginTest () {

}

int main() {
	
	database *db = new xmlDatabase;
	
	std::cout << db->registerUser(std::string("user info xml")) << std::endl;
	
	std::cout << db->loginUser(std::string("test1"), std::string("pass1234")) << std::endl;
	
	std::cout << db->updateUserInfo(std::string("user info xml")) << std::endl;
	
	std::cout << db->getUserInfo(std::string("u100000")) << std::endl;
	
	std::cout << db->getUserConversations(std::string("u100000")) << std::endl;
	
	std::cout << db->getUsersConversation(std::string("u100000"), std::string("u100001")) << std::endl;
	
	std::cout << db->addUserMessage(std::string("message xml")) << std::endl;
	
	std::cout << db->getGroupInfo(std::string("g5")) << std::endl;
	
	std::cout << db->getGroupConversation(std::string("g67")) << std::endl;
	
	std::cout << db->updateGroupInfo(std::string("group info xml")) << std::endl;
	
	std::cout << db->addGroupMessage(std::string("message xml")) << std::endl;

	return 0;
}
