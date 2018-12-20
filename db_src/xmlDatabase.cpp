#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

#include <helpers.hpp>
#include <IDgenerator.hpp>
#include <xmlDatabase.hpp>

static xmlDatabase* sharedDB = NULL;

IDgenerator obj("us_id.txt","gr_id.txt", "mes_id.txt");


std::string xmlDatabase::registerUser(std::string userInfo) 
{
	std::string result = "";
	int length = userInfo.size();
	const char* inf = userInfo.c_str();
	std::string login = "";
	std::string mail = "";
	std::string password = "";
	xmlDoc* doc = NULL;
	xmlNode* root_element = NULL;
	LIBXML_TEST_VERSION;
	doc = xmlReadMemory(inf, length, "noname.xml", NULL, 0);
	root_element = xmlDocGetRootElement(doc);
	extract_credentials(root_element, login, mail, password);
	if(verification(login, mail, result))
	{
		std::string ID = IDgenerator::getUserId();
		isValidId(ID);
		addCredtxt(login, password, ID);
		add_ID(root_element, ID);
		addUserIdDir(ID);
		std::string us_inf = "db_files/users/" + ID + "/info.xml";
		const char* us_inf_char = us_inf.c_str();
		xmlSaveFormatFileEnc(us_inf_char, doc, "UTF-8", 0);
		add_convs_dir(ID);
		xmlFreeDoc(doc);
		xmlCleanupParser();
		xmlMemoryDump();
		result = "<uId>" + ID +"</uId>";
	}
	return result;
}

std::string xmlDatabase::loginUser(std::string login, std::string password) {
	// Open directory with login name
	std::string pathLog = "db_files/register/logins/" + login;
	DIR* loginDir = opendir(pathLog.c_str());
	if (!loginDir) {
		// If there is not directory with such name then login and / or password is not available
		std::cout << "!Your login and / or password is not available! Please, try again!" << std::endl;
	} else {
		// Open pass.txt
		std::string path = "db_files/register/logins/" + login + "/creds.txt";
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
	LIBXML_TEST_VERSION;
	xmlDoc* doc = xmlReadMemory(userInfo.c_str(), userInfo.size(), "noname.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(doc);
	xmlNode* node = NULL;
	std::string uId = "";
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE) {
			if(0 == strcmp((char*)node->name,"uId")){
				xmlChar* buf;
				buf = xmlNodeGetContent(node);
				uId = (char*)buf;
				xmlFree(buf);
				break;
			}
		}
	}
	std::string path = "db_files/users/" + uId + "/info.xml";
	xmlDoc* docGen = xmlReadFile(path.c_str(), NULL, 0);
	xmlNode* rootGen = xmlDocGetRootElement(docGen);
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE && strcmp((char*)node->name,"uId")!=0){
			xmlChar* buf;
			buf = xmlNodeGetContent(node);
			UpdateUserDate(rootGen, node->name, buf);
			xmlFree(buf);
		}
	}
	xmlSaveFormatFileEnc(path.c_str(), docGen, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlFreeDoc(docGen);
	xmlMemoryDump();
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
		while(! xml_file.eof()) {
			info += temp;
			xml_file >> temp;
		}
		xml_file.close();
		return info;
	}
	else
		return "Error 404";

}

std::string xmlDatabase::getUserShortInfo(std::string userId) {
	std::string path = "db_files/users/" + userId;
	const char * p = path.c_str();
	struct stat sb;
	std::string shortInfo = "";
	if(stat(p, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		path += "/info.xml";
		const char * filename = path.c_str();

		xmlDoc * doc = NULL;
		xmlNode * root = NULL;
		xmlNode * node = NULL;

		doc = xmlReadFile(filename, NULL, 0);
		root = xmlDocGetRootElement(doc);

		xmlDoc * newDoc = xmlNewDoc(BAD_CAST "1.0");
		xmlNode * newRoot = xmlNewNode(NULL, BAD_CAST "info");
		xmlDocSetRootElement(newDoc, newRoot);

		for (node = root->children; node; node = node->next) {
			if (node->type == XML_ELEMENT_NODE) {
				if(0 == strcmp((char*)node->name, "firstName") || 0 == strcmp((char*)node->name, "lastName") || 0 == strcmp((char*)node->name, "birthDate") || 0 == strcmp((char*)node->name, "avatar")) {
					xmlNewChild(newRoot, NULL, BAD_CAST node->name, BAD_CAST xmlNodeGetContent(node));

				}
			}
		}

		xmlChar* info;
		int size;
		xmlDocDumpMemory(newDoc, &info, &size);
		shortInfo = (char*) info;
		xmlFree(info);
		xmlFreeDoc(doc);
		xmlFreeDoc(newDoc);

	}
	return shortInfo;
}

std::string xmlDatabase::getUserConversations(std::string userId) {
	std::string tmp = "";
	std::string fin = "";
	std::ifstream id("db_files/users/"+userId+"/convs/convs_list.xml");
	while(getline(id,tmp)) {
		fin = fin +tmp;
	}
	fin = replace_tab(fin);
	id.close();
	return fin;
}

std::string xmlDatabase::getUsersConversation(std::string from, std::string to) {
	std::string data ="db_files/users/"+ from + "/convs/" + to + ".xml";
	xmlDoc* doc =NULL;
	xmlNode* root = NULL;
	xmlNode* node = NULL;
	doc=xmlReadFile(data.c_str(),NULL,0);
	root = xmlDocGetRootElement(doc);
	node = root->children;
	const char* temp =from.c_str() ;
	xmlChar* cur =xmlCharStrdup(temp);
	while(node != NULL){
		if(xmlGetProp(node,cur)!=NULL){
			if(node->type != XML_TEXT_NODE){
				xmlNode* temp = node->next;
				xmlUnlinkNode(node);
				xmlFree(node);
				node = temp;
			}
		}
		else{
			node=node->next;
		}
	}

	xmlChar* info;
	std::string conversation="";
	int size;
	xmlDocDumpMemory(doc, &info, &size);
	conversation = (char*)info;
	xmlFree(doc);
	xmlFree(info);


	return conversation;

}

std::string xmlDatabase::addUserMessage(std::string from, std::string to, std::string message)
{
	bool status = false;
	std::string path = "";
	std::string info = "";
	const char* mess = message.c_str();
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	LIBXML_TEST_VERSION;
	doc = xmlReadMemory(mess, message.length(), "noname.xml", NULL, 0);
	root = xmlDocGetRootElement(doc);
	root = addMessId(root, from);
	info = xmlDocToString(doc);
	status = add_message(root, from, to);
	xmlMemoryDump();
	xmlCleanupParser();
	if(status && (!(info == "")))
	{
		return info;
	}
	else
	{
		return "<error/>";
	}
}


std::string xmlDatabase::createGroup(std::string groupInfo) {
	std::string groupId = IDgenerator::getGroupId();
	isValidGroupId(groupId);
	std::string path = "db_files/groups/" + groupId;
	const char * p = path.c_str();

	mode_t process_mask = umask (0);
	mkdir(p , 0777);
	umask (process_mask);

	xmlDoc* doc = NULL;
	xmlNode* root = NULL;

	LIBXML_TEST_VERSION;
	const char* inf = groupInfo.c_str();
	doc = xmlReadMemory(inf, groupInfo.size(), "noname.xml", NULL, 0);
	root = xmlDocGetRootElement(doc);
	const char * gId = groupId.c_str();
	if (root->type == XML_ELEMENT_NODE) {
		xmlNewChild(root, NULL, BAD_CAST "gId", BAD_CAST gId);
		xmlNewChild(root, NULL, BAD_CAST "usersquantity", BAD_CAST "1");
	}
	xmlNode* node = NULL;
	std::string value = "";
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE) {
			if(0 == strcmp((char*)node->name, "admin")) {
				xmlChar* buf;
				buf = xmlNodeGetContent(node);
				value = (char*)buf;
				xmlFree(buf);
				break;
			}
		}
	}
	path = path + "/ginfo.xml";
	const char* file = path.c_str();
	xmlSaveFormatFileEnc(file, doc, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();

	path = "db_files/users/" + value + "/info.xml"; 
	const char* filename = path.c_str();
	doc = xmlReadFile(filename, NULL, 0);
	root = xmlDocGetRootElement(doc);
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE) {
			if(0 == strcmp((char*)node->name, "groupAdmin")) {	
				xmlNewChild(node, NULL, BAD_CAST gId, NULL);
			}
			if(0 == strcmp((char*)node->name, "groups")) {	
				xmlNewChild(node, NULL, BAD_CAST gId, NULL);
			}
		}
	}
	xmlSaveFormatFileEnc(filename, doc, "UTF-8", 0);
	xmlFreeDoc(doc);

	doc = xmlNewDoc(BAD_CAST "1.0");
	root = xmlNewNode(NULL, BAD_CAST "users");
	xmlDocSetRootElement(doc, root);
	const char * value1 = value.c_str();
	xmlNewChild(root, NULL, BAD_CAST value1, NULL);
	path = "db_files/groups/" + groupId + "/users.xml";
	const char* file1 = path.c_str();
	xmlSaveFormatFileEnc(file1, doc, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlCleanupParser();

	doc = xmlNewDoc(BAD_CAST "1.0");
	root = xmlNewNode(NULL, BAD_CAST "conv");
	xmlDocSetRootElement(doc, root);
	path = "db_files/groups/" + groupId + "/conv.xml";
	const char* file2 = path.c_str();
	xmlSaveFormatFileEnc(file2, doc, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlCleanupParser();

	add_link_group_convs(groupId, value);
	std::string id = "<gId>" + groupId + "</gId>";
	return id;
}

std::string xmlDatabase::getGroupInfo(std::string groupID) {
	std::string str = "";
	std::string res = "";
	std::ifstream xml("db_files/groups/" + groupID + "/ginfo.xml");
	while(xml >> str)
		res += str;
	xml.close();
	return res;
}

std::string xmlDatabase::getGroupConversation(std::string userID,std::string groupID) {
	std::string data ="db_files/groups/"+groupID+"/conv.xml";
	const char* FileData=data.c_str();
	xmlDoc* doc =NULL;
	xmlNode* root = NULL;
	xmlNode* child = NULL;
	doc=xmlReadFile(FileData,NULL,0);
	root = xmlDocGetRootElement(doc);
	child = root->children;
	const char* temp =userID.c_str() ;
	xmlChar* cur =xmlCharStrdup(temp);
	while(child != NULL){
		if(xmlGetProp(child,cur)!=NULL){
			if(child->type != XML_TEXT_NODE){
				child = delete_node(child);
			}
		} else {
			child=child->next;
		}
	}

	xmlChar* info;
	std::string conversation="";
	int size;
	xmlDocDumpMemory(doc, &info, &size);
	conversation = (char*)info;
	xmlFree(doc);
	xmlFree(info);

	return conversation;
}


bool xmlDatabase::updateGroupInfo(std::string groupInfo) {
	LIBXML_TEST_VERSION;
	xmlDoc* doc = xmlReadMemory(groupInfo.c_str(), groupInfo.size(), "noname.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(doc);
	xmlNode* node = NULL;
	std::string gId = "";
	std::string newAdmin = "";
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE) {
			if(0 == strcmp((char*)node->name,"admin")){
				newAdmin =(char*)xmlNodeGetContent(node);	
				continue;
			}
			if(0 == strcmp((char*)node->name,"gId")){
				xmlChar* buf;
				buf = xmlNodeGetContent(node);
				gId = (char*)buf;
				xmlFree(buf);
			}
		}
	}
	if(newAdmin != "")
                changeAdmin(gId,newAdmin);
	std::string path = "db_files/groups/" + gId + "/ginfo.xml";
	xmlDoc* docGen = xmlReadFile(path.c_str(), NULL, 0);
	xmlNode* rootGen = xmlDocGetRootElement(docGen);
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE && strcmp((char*)node->name,"gId")!=0){
			xmlChar* buf;
			buf = xmlNodeGetContent(node);
			UpdateGroupDate(rootGen, node->name, buf);
			xmlFree(buf);
		}
	}
	xmlSaveFormatFileEnc(path.c_str(), docGen, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlFreeDoc(docGen);
	xmlCleanupParser();
	xmlMemoryDump();
	return true;
}
bool xmlDatabase::updateGroupMessage(std::string groupId, std::string messBody) {
	bool b = true;
	std::string path = "db_files/groups/" + groupId;
	const char* mBody = messBody.c_str();
	const char* p = path.c_str();
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	xmlDoc* doc1 = NULL;
	xmlNode* root1 = NULL;
	doc1 = xmlReadMemory(mBody, messBody.size(), "noname.xml", NULL, 0);
	root1 = xmlDocGetRootElement(doc1);
	const char* mId =(char*)root1->name;
	struct stat sb;
	if(stat(p, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		path = path + "/conv.xml";
		const char* pat = path.c_str();
		std::ifstream file(path);
		if(file.is_open()) {
			doc = xmlReadFile(pat, NULL, 0);
			root = xmlDocGetRootElement(doc);
			for(xmlNode* node = root->children; node; node = node->next) {
				if((node->type == XML_ELEMENT_NODE) && (0 == strcmp((const char*)(node->name), mId))) {
					node = delete_node(node);
					xmlAddChild(root, root1);
					xmlSaveFormatFileEnc(pat, doc, "UTF-8", 0);
					xmlUnlinkNode(root);
					xmlFreeDoc(doc);
					xmlCleanupParser();
					xmlMemoryDump();
					b = true;
					break;
				}
				else{
					b = false;
				}
			}
		}
		else
			b = false;
	}
	else
		b = false;

	return b;
}

std::string xmlDatabase::addGroupMessage(std::string groupId, std::string userId, std::string message)
{ 
	std::string p = "db_files/groups/" + groupId + "/conv.xml";
	std::string info = "";
	const char* path = p.c_str();
	const char* mess = message.c_str();
	xmlDoc* doc_mess = NULL;
	xmlNode* root_mess = NULL;
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	LIBXML_TEST_VERSION;
	doc_mess = xmlReadMemory(mess, message.length(), "noname.xml", NULL, 0);
	root_mess = xmlDocGetRootElement(doc_mess);
	root_mess = addMessId(root_mess, userId);
	info = xmlDocToString(doc_mess);
	doc = xmlReadFile (path, NULL, 0);
	root = xmlDocGetRootElement(doc);
	xmlAddChild(root, root_mess);
	xmlSaveFormatFileEnc(path, doc, "UTF-8", 0);
	xmlUnlinkNode(root);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
	if (info == "")
	{
		info = "<error/>";
	}
	return info;
}

xmlDatabase* xmlDatabase::getShared() {
	return sharedDB;
}


bool xmlDatabase::deleteUser(std::string userId){
	std::string login = "";
	std::string email = "";
	xmlNode* node = NULL;
	xmlNode* root = NULL;
	std::string path = "db_files/users" + userId + "/info.xml";
	xmlDoc* doc = xmlReadFile(path.c_str(), NULL, 0);
	root = xmlDocGetRootElement(doc);
	remgIdFromUinfo(root, userId);
	for(node = root->children; node; node = node->next){
		if(node->type == XML_ELEMENT_NODE){
			if(0 == strcmp((char*)node->name, "login")){
				xmlChar* buf;
				buf = xmlNodeGetContent(node);
				login = (char*)buf;
				xmlFree(buf);
				continue;
			}
			if(0 == strcmp((char*)node->name, "email")){
				xmlChar* buf;
				buf = xmlNodeGetContent(node);
				email = (char*)buf;
				xmlFree(buf);
			}
		}
	}
	path = "db_files/register/logins/" + login;
	rmdir(path.c_str());
	path = "db_files/register/mails/" + email;
	remove(path.c_str());	
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
	path = "db_files/users" + userId;
	rmdir(path.c_str());
	return true;
}

bool xmlDatabase::deleteGroup(std::string groupId) {
        LIBXML_TEST_VERSION;
        std::string path = "";
	path = "db_files/groups/" + groupId + "/users.xml";
        xmlDoc* doc = NULL;
        xmlNode* root = NULL;
        doc=xmlReadFile(path.c_str(),NULL,0);
        root= xmlDocGetRootElement(doc);
        for (xmlNode* cur_node = root->children; cur_node; cur_node = cur_node->next){
                if (cur_node->type == XML_ELEMENT_NODE){
                        std::string nodeName = (char*)cur_node->name;
			std::string path1="db_files/users/" + nodeName + "/info.xml";
			xmlNode* root2=NULL;
			xmlDoc* doc2=NULL;
			doc2=xmlReadFile(path1.c_str(),NULL,0);
			root2=xmlDocGetRootElement(doc2);
			for (xmlNode* cur_node2 = root2->children; cur_node2; cur_node2 = cur_node2->next){
				if (cur_node2->type == XML_ELEMENT_NODE){
					const char* name = (const char*)cur_node2->name;
					if (strcmp(name, "groups") == 0){
						for (xmlNode* cur_node3 = cur_node2->children; cur_node3; cur_node3 = cur_node3->next){
							if (cur_node3->type == XML_ELEMENT_NODE){
								const char* name = (const char*)cur_node3->name;
								if (strcmp(name, groupId.c_str()) == 0){
									delete_node(cur_node3);
									break;
								}
							}
						}
					}
					if (strcmp(name, "groupAdmin") == 0){
						for (xmlNode* cur_node3 = cur_node2->children; cur_node3; cur_node3 = cur_node3->next){
							if (cur_node3->type == XML_ELEMENT_NODE){
								const char* name = (const char*)cur_node3->name;
								if (strcmp(name, groupId.c_str()) == 0){
									delete_node(cur_node3);
									break;
								}
							}
						}
					}
				}
			}
			xmlSaveFormatFileEnc(path1.c_str(), doc2, "UTF-8", 0);
			xmlFreeDoc(doc2);
		}
	}
	xmlSaveFormatFileEnc(path.c_str(), doc, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
	path="rm -r db_files/groups/" + groupId;
	system(path.c_str());
	return true;
}




bool xmlDatabase::addUserToGroup(std::string groupID, std::string userID) 
{
	bool status = true;
	std::string gr_inf = "db_files/groups/" + groupID + "/ginfo.xml";
	const char* c_gr_inf = gr_inf.c_str();
	std::string users = "db_files/groups/" + groupID + "/users.xml";
	const char* c_users = users.c_str();
	xmlDoc* doc = NULL;
	xmlNode* root_element = NULL;
	LIBXML_TEST_VERSION;
	doc = xmlReadFile(c_users, NULL, 0);
	root_element = xmlDocGetRootElement(doc);
	add_ID(root_element, userID, status);
	xmlSaveFormatFileEnc(c_users, doc, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	if(status)
	{
		doc = xmlReadFile(c_gr_inf, NULL, 0);
		root_element = xmlDocGetRootElement(doc);
		change_quantity(root_element, status);
		xmlSaveFormatFileEnc(c_gr_inf, doc, "UTF-8", 0);
		xmlFreeDoc(doc);
		xmlCleanupParser();
		status = addGroupId(groupID, userID);
		if(status)
		{
			status = add_link_group_convs(groupID, userID);
		}
	}
	return status;
}

bool xmlDatabase::removeMessage(std::string messageInfo) {
	std::string from,to,messageId,remove_status;
	xmlDoc* doc_rest = NULL;
	xmlNode* root_rest = NULL;
	xmlDoc* doc = NULL;
	xmlNode* root_element = NULL;
	xmlNode* node = NULL;
	doc_rest = xmlReadMemory(messageInfo.c_str(), messageInfo.size(), "noname.xml", NULL, 0);
	root_rest = xmlDocGetRootElement(doc_rest);
	for(node = root_rest->children;node;node = node->next){
		if(0== strcmp((char*)node->name,"from"))
			from=(char*)xmlNodeGetContent(node);
		if(0== strcmp((char*)node->name,"to"))
			to = (char*)xmlNodeGetContent(node);
		if(0== strcmp((char*)node->name,"messageId"))
			messageId = (char*)xmlNodeGetContent(node);
		if(0== strcmp((char*)node->name,"remove_status"))
			remove_status = (char*)xmlNodeGetContent(node);
	}
	std::cout<<from<<":::::::::::"<<to<<std::endl;
	xmlChar* atribut = (xmlChar*)from.c_str();
	xmlFreeDoc(doc_rest);
	xmlCleanupParser();
	xmlMemoryDump();
	std::string conv = "db_files/users/" + from + "/convs/" + to + ".xml";
	LIBXML_TEST_VERSION;
	doc = xmlReadFile(conv.c_str(), NULL, 0);
	root_element = xmlDocGetRootElement(doc);
	for(node = root_element->children;node;node = node->next){
                if(0== strcmp((char*)node->name,messageId.c_str()))
                        break;
		}
	if(xmlGetProp(node,atribut)==NULL){
        if(remove_status=="0")
                xmlNewProp(node,BAD_CAST atribut, BAD_CAST "deleted");
        else 
               xmlUnlinkNode(node);
	}
	xmlSaveFormatFileEnc(conv.c_str(), doc, "UTF-8", 0);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();
}

bool xmlDatabase::removeMessageFromGroupConversation(std::string messageInfo){

        std::string userId;
        std::string groupId;
        std::string messageId;
        std::string remove_status;
        xmlDoc* doc_rest = NULL;
        xmlNode* root_rest = NULL;
        xmlDoc* doc = NULL;
        xmlNode* root_element = NULL;
        xmlNode* node = NULL;
        doc_rest = xmlReadMemory(messageInfo.c_str(), messageInfo.size(), "noname.xml", NULL, 0);
        root_rest = xmlDocGetRootElement(doc_rest);
        for(node = root_rest->children;node;node = node->next){
                if(0 == strcmp((char*)node->name,"userId"))
                        userId=(char*)xmlNodeGetContent(node);
                if(0 == strcmp((char*)node->name,"groupId"))
                        groupId = (char*)xmlNodeGetContent(node);
                if(0 == strcmp((char*)node->name,"messageId"))
                        messageId = (char*)xmlNodeGetContent(node);
                if(0 == strcmp((char*)node->name,"remove_status"))
                        remove_status = (char*)xmlNodeGetContent(node);

        }

        xmlChar* attribute = (xmlChar*)userId.c_str();
        xmlFreeDoc(doc_rest);
        xmlCleanupParser();
        xmlMemoryDump();

        std::string conv = "db_files/groups/" + groupId + "/conv.xml";
        LIBXML_TEST_VERSION;
        doc = xmlReadFile(conv.c_str(), NULL, 0);
        root_element = xmlDocGetRootElement(doc);
        for(node = root_element->children;node;node = node->next){
                if(0== strcmp((char*)node->name,messageId.c_str()))
                        break;
                        }
        if(remove_status=="0")
                xmlNewProp(node,BAD_CAST attribute, BAD_CAST "deleted");
        else
               xmlUnlinkNode(node);
               xmlSaveFormatFileEnc(conv.c_str(), doc, "UTF-8", 0);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();
                return true;
}


bool xmlDatabase::removeUserConversation(std::string fromUserId,std::string toUserId){
	std::cout<<fromUserId<<" "<<toUserId<<std::endl;
	if(removeFromXml(fromUserId, toUserId)){
                std::string dataReviewLink("db_files/users/"+toUserId+"/convs/"+fromUserId+".xml");
                const char*  Link= dataReviewLink.c_str();
                std::string dataReviewUserLink("db_files/users/"+fromUserId+"/convs/"+toUserId+".xml");
                const char* UserLink = dataReviewUserLink.c_str();
                std::string dataConvLink1("db_files/conversations/"+toUserId+fromUserId+".xml");
                const char* Conv1 = dataConvLink1.c_str();
                std::string dataConvLink2("db_files/conversations/"+fromUserId+toUserId+".xml");
                const char* Conv2 = dataConvLink2.c_str();
                std::ifstream reviewLink("db_files/users/"+toUserId+"/convs/"+fromUserId+".xml");
                if(reviewLink.is_open()){
                        std::ifstream reviewUserLink("db_files/users/"+fromUserId+"/convs/"+toUserId+".xml");
                        if(reviewUserLink.is_open()){
                                reviewUserLink.close();
                                remove(UserLink);
                        }
                        reviewLink.close();
                        return true;
                }
                else{
                        std::ifstream reviewUserLink("db_files/users/"+fromUserId+"/convs/"+toUserId+".xml");
                        if(reviewUserLink.is_open()){
                                std::ifstream convFile1("db_files/conversations/"+toUserId+fromUserId+".xml");
                                if(convFile1.is_open()){
                                        convFile1.close();
                                        remove(Conv1);
                                }
                                else{
                                        std::ifstream convFile2("db_files/conversations/"+fromUserId+toUserId+".xml");
                                        if(convFile2.is_open()){
                                                convFile1.close();
                                                remove(Conv2);
                                        }
                                }
                                reviewUserLink.close();
                                remove(UserLink);
                        }
                        return true;
                }
        }
        else
                return false;
}

bool xmlDatabase::removeGroupConversation(std::string groupId) {
	std::string path = "db_files/groups/" + groupId + "/conv.xml";
	remove (path.c_str());
	xmlDocPtr doc = NULL;
	xmlNodePtr root = NULL;
	LIBXML_TEST_VERSION;
	doc = xmlNewDoc(BAD_CAST "1.0");
	root = xmlNewNode(NULL, BAD_CAST "conv");
	xmlDocSetRootElement(doc, root);
	xmlSaveFormatFileEnc(path.c_str(), doc, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();

	return true;
}



xmlDatabase::xmlDatabase() {
	if(NULL == sharedDB) sharedDB = this;
}

xmlDatabase::~xmlDatabase() { }



bool xmlDatabase::removeFromGroup(std::string groupID, std::string userID) {
	bool t = false;
	t = removeFromGroupUserName(groupID, userID);
	t = reduceGroupMembersQuantity(groupID);
	t = removeUserIdFromXml(groupID, userID);
	return 0;
}

std::string xmlDatabase::getGroupUsers(std::string groupID) {
	std::string str = "";
	std::string pathForID = "db_files/groups/" + groupID;

	DIR* usersDirID = opendir(pathForID.c_str());
	
	if (usersDirID) {
		xmlDoc *doc = NULL;
		xmlNode *root_element = NULL;
		std::string pathForXml = pathForID + "/users.xml";
		doc = xmlReadFile(pathForXml.c_str(), NULL, 0);
			xmlChar* info = NULL;
			int countXmlElements = 0;
			xmlDocDumpMemory(doc, &info, &countXmlElements);
			str = (char*)info;
			xmlFreeDoc(doc);
			xmlFree(info);
	}

	closedir(usersDirID);
	return str;
}

bool xmlDatabase::updateUserMessage(std::string from, std::string to, std::string messageInfo) {
	std::string messageId = "";
	std::string correctedMessage;
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	xmlNode* node = NULL;
	xmlNode* node1 = NULL;

	LIBXML_TEST_VERSION;
	const char* info = messageInfo.c_str();
	doc = xmlReadMemory(info, messageInfo.size(), "noname.xml", NULL, 0);
	root = xmlDocGetRootElement(doc);
	for (node = root->children; node; node = node->next) {
		if (node->type == XML_ELEMENT_NODE) {
			messageId = (char*) node->name;
			for (node1 = node->children; node1; node1 = node1->next) {
				if (0 == strcmp((char*)node1->name, "body")) {
					xmlChar* buf;
					buf = xmlNodeGetContent(node);
					correctedMessage = (char*) buf;
					xmlFree(buf);
				}
			}
		}
	}
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();

	std::string path = find_path(from, to);
	doc = xmlReadFile(path.c_str(), NULL, 0);
	root = xmlDocGetRootElement(doc);
	for (node = root->children; node; node = node->next) {
		if (node->type == XML_ELEMENT_NODE) {
			if (0 == strcmp((char*)node->name, messageId.c_str())) {
				for (node1 = node->children; node1; node1 = node1->next) {
					if (0 == strcmp((char*)node1->name, "body")) {
						xmlNodeSetContent(node1, BAD_CAST correctedMessage.c_str());
					}
				}
			}
		}
	}
	const char * path1 = path.c_str(); 
	xmlSaveFormatFileEnc(path1, doc, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	return true;
}
