#include <iostream>
#include <fstream>
#include <xmlDatabase.hpp>
#include <IDgenerator.hpp>
#include <libxml/parser.h>
#include <libxml/tree.h>

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
void test_getUserConversation(std::string from_id,std::string to_id) {
	std::cout<<db->getUsersConversation(from_id,to_id)<<std::endl;
	std::cout<<"======================================="<<std::endl;
	std::cout<<db->getUserConversations(from_id)<<std::endl;
}

void test1 () {
	std::string info = xml2string("xmls/register1.xml");
	std::cout << info << std::endl;
	std::string id = db->registerUser(info);
	std::cout << id << std::endl;

	xmlDoc* doc = NULL;
        xmlNode* root = NULL;
        LIBXML_TEST_VERSION;
        const char* inf = id.c_str();
        doc = xmlReadMemory(inf, id.size(), "noname.xml", NULL, 0);
        root = xmlDocGetRootElement(doc);
	id =(char*) xmlNodeGetContent(root);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();


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
	for(int i=0; i<1000; i++)
	{
		std::cout << IDgenerator::getMessageId()<<std::endl;
	}
}
void test_groupFunctional()
{
	std::cout<<"Start Group testing"<<std::endl;
	std::string info = xml2string("xmls/createGroup1.xml");
	std::cout<<"Info = "<<info<<std::endl;	
	std::string id=db->createGroup(info);
	xmlDoc* doc = NULL;
        xmlNode* root = NULL;
        LIBXML_TEST_VERSION;
        const char* inf = id.c_str();
        doc = xmlReadMemory(inf, id.size(), "noname.xml", NULL, 0);
        root = xmlDocGetRootElement(doc);
	id =(char*) xmlNodeGetContent(root);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();
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
	groupId = groupId.substr(5, groupId.rfind("<") - 5);
	std::cout << db->getGroupInfo(groupId) << std::endl;
        info = xml2string("xmls/createGroup2.xml");	
	groupId = db->createGroup(info);
	std::cout << groupId <<std::endl;
	groupId = groupId.substr(5, groupId.rfind("<") - 5);
	std::cout << db->getGroupInfo(groupId) << std::endl;
}
void test_creatGroup_addUserToGroup_getGroupInfo()
{
	std::string inf = "<info><name>VanIt</name><admin>u1</admin><createdate>12.12.2018</createdate></info>";
	std::string gid = db->createGroup(inf);
	std::cout<< gid <<std::endl;
	xmlDoc* doc = NULL;
        xmlNode* root = NULL;
        LIBXML_TEST_VERSION;
        const char* info = gid.c_str();
        doc = xmlReadMemory(info, gid.size(), "noname.xml", NULL, 0);
        root = xmlDocGetRootElement(doc);
	gid =(char*) xmlNodeGetContent(root);
	std::cout<< gid <<std::endl;
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();
	std::cout<<db->getGroupInfo(gid)<<std::endl;
	db->addUserToGroup(gid, "u17");
	std::cout<<db->getGroupInfo(gid)<<std::endl;
	std::cout<<"Update gInfo\tadmin->u24, name-> VanIt-Basic_training\n";
	std::string updInfo = "<info><gId>" + gid + "</gId><name>VanItBasictraining</name><admin>u24</admin></info>";
	std::cout<<"updInfo : "<<updInfo<<std::endl;
	db->updateGroupInfo(updInfo);
	std::cout<<db->getGroupInfo(gid)<<std::endl;
}
void test_addUserMessage()
//USHADRUTYUN ashxatacneluc araj petqa add_message funkciayum dzer popoxutyun@ aneq, mteq xmlDatabase.cpp, gteq bacatrutyun@ te inch@ petqa poxel  ( motavorapes tox 400 - 500 mijakayqum )
{
	std::string info1 = "<registration_information><firstName>Jo</firstName><lastName>Black</lastName><gender>male</gender><birthDate>10.02.1990</birthDate><email>black@gmail.com</email><login>black1990</login><password>JBlack1990</password></registration_information>";
	std::string id1 = db->registerUser(info1);
	std::string info2 = "<registration_information><firstName>Valod</firstName><lastName>Valodyan</lastName><gender>male</gender><birthDate>10.02.1990</birthDate><email>valod@gmail.com</email><login>valod1990</login><password>Val1990</password></registration_information>";
	std::string id2 = db->registerUser(info2);
	std::string info3 = "<registration_information><firstName>Vika</firstName><lastName>Vika</lastName><gender>female</gender><birthDate>10.02.1990</birthDate><email>vika@gmail.com</email><login>vika1990</login><password>Vika1990</password></registration_information>";
	std::string id3 = db->registerUser(info3);
	std::string message1 = "<message><date>14.12.2018</date><body>barev Valod</body></message>";
	std::string message2 = "<message><date>14.12.2018</date><body>barev Jo</body></message>";
	std::string message3 = "<message><date>14.12.2018</date><body> Inch ka?</body></message>";
	std::string message4 = "<message><date>14.12.2018</date><body> Ban chka</body></message>";
	std::string message5 = "<message><date>14.12.2018</date><body> barev Vika</body></message>";
	std::string message6 = "<message><date>14.12.2018</date><body> Vika barev</body></message>";
	std::string message7 = "<message><date>14.12.2018</date><body>barev</body></message>";
	xmlDoc* doc = NULL;
        xmlNode* root = NULL;
        LIBXML_TEST_VERSION;
        const char* i1 = id1.c_str();
        doc = xmlReadMemory(i1, id1.size(), "noname.xml", NULL, 0);
        root = xmlDocGetRootElement(doc);
	id1 =(char*) xmlNodeGetContent(root);
	std::cout<< id1 <<std::endl;
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();
        const char* i2 = id2.c_str();
        doc = xmlReadMemory(i2, id2.size(), "noname.xml", NULL, 0);
        root = xmlDocGetRootElement(doc);
	id2 =(char*) xmlNodeGetContent(root);
	std::cout<< id2 <<std::endl;
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();
        const char* i3 = id3.c_str();
        doc = xmlReadMemory(i3, id3.size(), "noname.xml", NULL, 0);
        root = xmlDocGetRootElement(doc);
	id3 =(char*) xmlNodeGetContent(root);
	std::cout<< id3 <<std::endl;
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();
	db->addUserMessage(id1, id2 , message1);
	db->addUserMessage(id2, id1 , message2);
	db->addUserMessage(id1, id2 , message3);
	db->addUserMessage(id2, id1 , message4);
	db->addUserMessage(id1, id3 , message5);
	db->addUserMessage(id2, id3 , message6);
	db->addUserMessage(id3, id1 , message7);
	db->addUserMessage(id3, id2 , message7);
}

int main() {
//	test1();
//	test2();
//	test_groupFunctional();
//	test_groupFunctional();
//	test_groupFunctional();

//	test2();
//	test_IdGenerator();
//	test_createGroup();
	test_creatGroup_addUserToGroup_getGroupInfo();
//	test_getUserConversation("u100002","u100003");
//	test_addUserMessage();
	return 0;
}
