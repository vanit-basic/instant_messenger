#include <iostream>
#include <fstream>
#include <xmlDatabase.hpp>
#include <IDgenerator.hpp>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
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
bool getId (std::string &id)
{
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	const char* inf = id.c_str();
	doc = xmlReadMemory(inf, id.size(), "noname.xml", NULL, 0);
	root = xmlDocGetRootElement(doc);
	xmlChar* buf = xmlNodeGetContent(root);
	id =(char*) buf;
	xmlFree(buf);
	if(0 == strcmp((char*)root->name, "error"))
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		xmlMemoryDump();
		return false;
	}
	else
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		xmlMemoryDump();
		return true;
	}
}
void test_getUserConversation(std::string from_id,std::string to_id) {
	std::cout<<db->getUsersConversation(from_id,to_id)<<std::endl;
//	std::cout<<"*****************************************************"<<std::endl;
//	std::cout<<"*****************************************************"<<std::endl;
//	std::cout<<"*****************************************************"<<std::endl;
//	std::cout<<db->getUserConversations(from_id)<<std::endl;
}
void test_delete_message(){
		std::cout<<db->getUsersConversation("u100000","u100003")<<std::endl;
	std::string delete_mess_test = "<delete_message><fromId>u100000</fromId><toId>u100003</toId><messageId>m1</messageId><remove_status>0</remove_status></delete_message>";
	if(db->removeMessage(delete_mess_test)){
		std::cout<<db->getUsersConversation("u100000","u100003")<<std::endl;
	}
	else
		std::cout<<"error";
}
void test1 () {
	std::string info = xml2string("xmls/register1.xml");
	std::cout << info << std::endl;
	std::string id = db->registerUser(info);
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	LIBXML_TEST_VERSION;
	if (!getId(id))
	{
		std::cout<<"Such login or email is already in use\n";
	}
	else
	{
		std::cout << "ID : " << id << std::endl;
		info = db->getUserInfo(id);
		std::cout << info << std::endl;
		std::cout<<"Update userInfo\n";
		std::string updInfo = "<info><uId>" + id + "</uId><firstname>Miqo</firstname><lastname>Aslikyan</lastname><login>Miqo1101</login><gender>male</gender></info>";
		db->updateUserInfo(updInfo);
		std::cout<<db->getUserInfo(id)<<std::endl;
	}
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
	std::cout<<"Add usertogroup : "<<db->addUserToGroup(id,"u100003")<<std::endl;
	std::cout<<"Add usertogroup : "<<db->addUserToGroup(id,"u100008")<<std::endl;
	std::cout<<"Get groupinfo : "<<db->getGroupInfo(id)<<std::endl;
	std::cout<<"Remove form group : "<<db->removeFromGroup(id,"u100003")<<std::endl;
	std::cout<<"Remove form group : "<<db->removeFromGroup(id,"u10003")<<std::endl;
	std::cout<<"Remove form group : "<<db->removeFromGroup(id,"u40004")<<std::endl;
	std::cout<<"Get groupinfo : "<<db->getGroupInfo(id)<<std::endl;
	std::cout<<"End Group testing"<<std::endl;
	
}

void test_createGroup() {
	std::string info = xml2string("xmls/createGroup1.xml");
	std::string groupId = db->createGroup(info);
	std::cout << groupId << std::endl;
        LIBXML_TEST_VERSION;
        xmlDoc* doc = NULL;
        xmlNode* root = NULL;
	const char* Id = groupId.c_str();
	doc = xmlReadMemory(Id, groupId.size(), "noname.xml", NULL, 0);
        root = xmlDocGetRootElement(doc);
	groupId = (char*) xmlNodeGetContent(root); 
	std::cout << groupId << "\n";
	std::cout << db->getGroupInfo(groupId) << std::endl;
        std::cout << db->getUserShortInfo("u100000") << "\n"; 
	info = xml2string("xmls/createGroup2.xml");	
	groupId = db->createGroup(info);
	std::cout << groupId <<std::endl;
	Id = groupId.c_str();
	doc = xmlReadMemory(Id, groupId.size(), "noname.xml", NULL, 0);
        root = xmlDocGetRootElement(doc);
	groupId = (char*) xmlNodeGetContent(root); 
	std::cout << groupId << "\n";
	std::cout << db->getGroupInfo(groupId) << std::endl;
}
void test_creatGroup_addUserToGroup_getGroupInfo_addGroupMessage()
{
	std::string inf = "<info><name>VanIt</name><admin>u1000</admin><createdate>12.12.2018</createdate></info>";
	std::string info1 = "<registration_information><firstName>Jo</firstName><lastName>Black</lastName><gender>male</gender><birthDate>10.02.1990</birthDate><email>black@gmail.com</email><login>black1990</login><password>JBlack1990</password></registration_information>";
	std::string id = db->registerUser(info1);

	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	LIBXML_TEST_VERSION;
	if(!getId(id))
	{
		std::cout<<"Such login or email is already in use\n";
	}
	else
	{
		std::cout << id << std::endl;
		std::string gid = db->createGroup(inf);
		std::cout<< gid <<std::endl;
		const char* gid1 = gid.c_str();
		doc = xmlReadMemory(gid1, gid.size(), "noname.xml", NULL, 0);
		root = xmlDocGetRootElement(doc);
		gid =(char*) xmlNodeGetContent(root);
		std::cout<< gid <<std::endl;
		std::cout<< id <<std::endl;
		xmlFreeDoc(doc);
		xmlCleanupParser();
		xmlMemoryDump();
		std::cout<<db->getGroupInfo(gid)<<std::endl;
		db->addUserToGroup(gid, id);
		std::cout<<db->getGroupInfo(gid)<<std::endl;
		std::cout<<"Update gInfo\tadmin->u24, name-> VanIt-Basic_training\n";
		std::string updInfo = "<info><gId>" + gid + "</gId><name>VanItBasictraining</name><admin>u24</admin></info>";
		std::cout<<"updInfo : "<<updInfo<<std::endl;
		db->updateGroupInfo(updInfo);
		std::cout<<db->getGroupInfo(gid)<<std::endl;
		std::cout<<"start test addGroupMessage\n";
		std::string group_mess = "<message><date>16.12.2018</date><body>barev ankrkneliner)</body></message>";
		std::cout<< db->addGroupMessage(gid, id, group_mess) <<std::endl;
	}
}
void test_addUserMessage_getUsersConversation_getUserConversations()
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
	if(!getId(id1))
	{
		std::cout<<"Such login or email is already in use\n";
	}
	else
	{
		std::cout<< id1 <<std::endl;
		if(!getId(id2))
		{
			std::cout<<"Such login or email is already in use\n";
		}
		else
		{
			std::cout<< id2 <<std::endl;
			if(!getId(id3))
			{
				std::cout<<"Such login or email is already in use\n";
			}
			else
			{
				std::cout<< id3 <<std::endl;
				xmlFreeDoc(doc);
				xmlCleanupParser();
				xmlMemoryDump();
				std::cout<<"addUserMessage\n";
				std::cout<<db->addUserMessage(id1, id2 , message1)<<std::endl;
				std::cout<<db->addUserMessage(id2, id1 , message2)<<std::endl;
				std::cout<<db->addUserMessage(id1, id2 , message3)<<std::endl;
				std::cout<<"getUsersConversation\n";
				std::cout<<db->getUsersConversation(id1, id2)<<std::endl;
				db->addUserMessage(id2, id1 , message4);
				std::cout<<db->getUsersConversation(id1, id2)<<std::endl;
				db->addUserMessage(id1, id3 , message5);
				db->addUserMessage(id2, id3 , message6);
				db->addUserMessage(id3, id1 , message7);
				db->addUserMessage(id3, id2 , message7);
				std::cout<<"getUserConversations\n";
				std::cout<<"id1  "<<id1<<"  "<<db->getUserConversations(id1)<<std::endl;
				std::cout<<"id2  "<<id2<<"  "<<db->getUserConversations(id2)<<std::endl;
				std::cout<<"id3  "<<id3<<"  "<<db->getUserConversations(id3)<<std::endl;
			}
		}
	}
}


int main() {
//	test1();
//	test2();
//	test_groupFunctional();
//	test_IdGenerator();
//	test_createGroup();
//	test_creatGroup_addUserToGroup_getGroupInfo_addGroupMessage();
//	test_getUserConversation("u100000","u100003");
	test_addUserMessage_getUsersConversation_getUserConversations();
//	test_delete_message();	
	return 0;
}
