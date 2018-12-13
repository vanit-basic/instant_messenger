#include <iostream>
#include <fstream>
#include <xmlDatabase.hpp>
#include <IDgenerator.hpp>

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
	id = id.erase(0, 4);
	id = id.substr(0, id.find("</id>"));
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
void test_IdGenerator()
{
	for(int i=0; i<1000; i++)
	{
		std::cout << IDgenerator::getUserId()<<std::endl;
	}
	for(int i=0; i<1000; i++)
	{
		std::cout << IDgenerator::getGroupId()<<std::endl;
	}
}
void test_groupFunctional()
{
	std::cout<<"Start Group testing"<<std::endl;
	std::string info = xml2string("xmls/createGroup1.xml");
	std::cout<<"Info = "<<info<<std::endl;	
	std::string id=db->createGroup(info);
	id = id.erase(0, 4);
        id = id.substr(0, id.find("</id>"));
	std::cout<<"Group ID = "<<id<<std::endl;
	std::cout<<"Group Info : ";
	std::cout<<db->getGroupInfo(id)<<std::endl;
	std::cout<<"********************************"<<std::endl;
	std::cout<<"Add usertogroup : "<<db->addUserToGroup("g1","u100003")<<std::endl;
	std::cout<<"Get groupinfo : "<<db->getGroupInfo("g1")<<std::endl;
	std::cout<<"Remove form group : "<<db->removeFromGroup("g1","u10003")<<std::endl;
	std::cout<<"Remove form group : "<<db->removeFromGroup("g6","u10003")<<std::endl;
	std::cout<<"Remove form group : "<<db->removeFromGroup("g1","u40004")<<std::endl;
	std::cout<<"Get groupinfo : "<<db->getGroupInfo("g1")<<std::endl;
	std::cout<<"End Group testing"<<std::endl;
	
}

void test_createGroup() {
	std::string info = xml2string("xmls/createGroup1.xml");
	std::string groupId = db->createGroup(info);
	std::cout << groupId << std::endl;
	groupId = groupId.substr(4, groupId.rfind("<") - 4);
	std::cout << db->getGroupInfo(groupId) << std::endl;
        info = xml2string("xmls/createGroup2.xml");	
	groupId = db->createGroup(info);
	std::cout << groupId <<std::endl;
	groupId = groupId.substr(4, groupId.rfind("<") - 4);
	std::cout << db->getGroupInfo(groupId) << std::endl;
}
void test_creatGroup_addUserToGroup_getGroupInfo()
{
	std::string inf = "<info><name>VanIt</name><admin>u1</admin><createdate>12.12.2018</createdate></info>";
	std::string gid = db->createGroup(inf);
	std::cout<< gid <<std::endl;
	gid = gid.erase(0, 4);
	gid = gid.substr(0, gid.find("</id>"));
	std::cout<<db->getGroupInfo(gid)<<std::endl;
	db->addUserToGroup(gid, "u17");
	std::cout<<db->getGroupInfo(gid)<<std::endl;
}

int main() {
	test1();
//	test1();
//	test_groupFunctional();
//	test_groupFunctional();
//	test_groupFunctional();

//	test2();
//	test_IdGenerator();
//	test_createGroup();
	test_creatGroup_addUserToGroup_getGroupInfo();
	return 0;
}
