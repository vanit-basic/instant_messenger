#include <iostream>
#include <fstream>

#include <xmlDatabase.hpp>

/*
registerUser(std::string userInfo)
getUserInfo(std::string userID)
loginUser(std::string login, std::string password)
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

static database *db = new xmlDatabase;

std::string xml2string (const char* file) {
	std::ifstream in(file);
	std::string info = "";
	std::string str = "";
	while (!in.eof()) {
		info += str;
		in >> str;
	}
	return info;
}

void test1 () {
	std::string info = xml2string("xmls/register1.xml");
	std::cout << info << std::endl;
	std::string id = db->registerUser(info);
	std::cout << "ID : " << id << std::endl;
	info = db->getUserInfo(id);
	std::cout << info << std::endl;
}

void test2 () {
	std::string info = xml2string("xmls/register2.xml");
	std::cout << info << std::endl;
	std::string id = db->registerUser(info);
	std::cout << db->loginUser(std::string("test2"), std::string("test1234")) << std::endl;
}

void testAll () {
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
}

int main() {
	test1();
	test2();
	return 0;
}
