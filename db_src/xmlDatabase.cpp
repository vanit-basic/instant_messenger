#include <IDgenerator.hpp>
#include <xmlDatabase.hpp>
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

static xmlDatabase* sharedDB = NULL;

IDgenerator obj("us_id.txt","gr_id.txt", "mes_id.txt");

void UpdateGroupDate(xmlNode* root,const xmlChar* tegName, const xmlChar* content)
{
	for(xmlNode* node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE) {
			if(0 == strcmp((char*)node->name,(char*)tegName)){
				xmlNodeSetContent(node, content);
				break;
			}
		}
	}
}

void UpdateUserDate(xmlNode* root,const xmlChar* tegName,const xmlChar* content)
{
	for(xmlNode* node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE) {
			if(0 == strcmp((char*)node->name,(char*)tegName)){
				xmlNodeSetContent(node, content);
				break;
			}
		}
	}
}

void remgIdFromUinfo(xmlNode* root, std::string userId){
	xmlNode* node = NULL;
        for(node = root->children; node; node = node->next){
                if(0 == strcmp((char*)node->name, "groups"))
                        break;
        }
	for(node = node->children; node; node = node->next){
		if(node->type == XML_ELEMENT_NODE)
			removeFromGroup((char*)node->name,userId);
	}

}

xmlNodePtr delete_node(xmlNode* a_node)
{
	bool stat = true;
	xmlNode *cur_node = a_node;
	xmlNode* node = NULL;
	if (cur_node->type == XML_ELEMENT_NODE)
	{
		if(cur_node->prev)
		{
			node = cur_node->prev;
		}
		else
		{
			node = cur_node->parent;
			stat = false;
		}
		xmlUnlinkNode(cur_node);
		xmlFreeNode(cur_node);
		if(stat == true)
		{
			cur_node = node;
		}
		else
		{
			cur_node = node->children;
		}
	}
	return cur_node;
}

void add_ID(xmlNode* root_element, std::string id) 
{
	xmlNode* cur_node = root_element;
	const char* i = id.c_str();
	if (cur_node->type == XML_ELEMENT_NODE)
	{
		xmlNewChild(cur_node, NULL, BAD_CAST "uId", BAD_CAST i);
		xmlNewChild(cur_node, NULL, BAD_CAST "groups", NULL);
		xmlNewChild(cur_node, NULL, BAD_CAST "groupAdmin", NULL);
	}
}

bool isValidLogin(std::string login) 
{
	std::string log = "db_files/register/logins/" + login;
	const char* l = log.c_str();
	struct stat sb;
	if (stat(l, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool isValidEmail(std::string mail) 
{
	std::string path = "db_files/register/mails/" + mail;
	std::ifstream email(path);
	if (email.is_open())
	{
		email.close();
		return false;
	}
	else
	{
		return true;
	}
}

bool verification(std::string login, std::string mail, std::string &result) 
{
	if (!(isValidLogin(login) && isValidEmail(mail)))
	{
		if(!isValidLogin(login))
		{
			result += "<login>Invalid</login>";
		}
		if(!isValidEmail(mail))
		{
			result += "<email>Invalid</email>";
		}
		result = "<error>" + result + "</error>";
		return false;
	}
	else
	{
		std::string log_f = "db_files/register/logins/" + login;
		const char* log_f_n = log_f.c_str();
		std::string mail_f = "db_files/register/mails/" + mail;
		mode_t process_mask = umask (0);
		mkdir(log_f_n, 0777);
		umask (process_mask);
		std::ofstream email(mail_f);
		email.close();
		return true;
	}
}

void tracker (xmlNode* a_node, std::string &login, std::string &mail, std::string &password) 
{
	xmlNode *cur_node = NULL;
	xmlChar* buf;
	for (cur_node = a_node->children; cur_node; cur_node = cur_node->next)
	{
		if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "login")))
		{
			buf = xmlNodeGetContent(cur_node);
			login = (char*) buf;
			xmlFree(buf);
		}
		if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "email")))
		{
			buf = xmlNodeGetContent(cur_node);
			mail = (char*) buf;
			xmlFree(buf);
		}
		if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "password")))
		{
			buf = xmlNodeGetContent(cur_node);
			password = (char*) buf;
			xmlFree(buf);
			cur_node = delete_node(cur_node);
		}
		if (!((login == "") || (mail == "") || (password == "")))
		{
			break;
		}
	}
}

void isValidId(std::string &ID)
{
	std::string ids = "db_files/users/" + ID;
	const char* uid = ids.c_str();
	struct stat sb;
	while (stat(uid, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ID = IDgenerator::getUserId();
		ids = "db_files/users/" + ID;
		uid = ids.c_str();
	}
}

void add_convs_dir(std::string ID)
{
	std::string path = "db_files/users/" + ID + "/convs";
	const char* path_c = path.c_str();
	mode_t process_mask = umask (0);
	mkdir(path_c, 0777);
	umask (process_mask);
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	doc = xmlNewDoc(BAD_CAST "1.0");
	root = xmlNewNode(NULL, BAD_CAST "convs");
	xmlDocSetRootElement(doc, root);
	path = path + "/convs_list.xml";
	const char* convs = path.c_str();
	xmlSaveFormatFileEnc(convs, doc, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlCleanupParser();
}
void addCredtxt(std::string login, std::string password, std::string ID)
{
	std::string credtxt = "db_files/register/logins/" + login + "/creds.txt";
	std::ofstream cred(credtxt);
	if (cred.is_open())
	{
		cred<<password;
		cred<<"\n";
		cred<<ID;
		cred<<"\n";
	}
	cred.close();
}

void addUserIdDir(std::string ID)
{
	std::string id_f = "db_files/users/" + ID;
	const char* id_f_n = id_f.c_str();
	mode_t process_mask = umask (0);
	mkdir(id_f_n, 0777);
	umask (process_mask);
}

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
	tracker(root_element, login, mail, password);
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
	xmlChar* buf;
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE) {
			if(0 == strcmp((char*)node->name,"uId")){
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

std::string replace_tab(std::string input){

	while(input.find('\t') != std::string::npos){
		int pos = input.find('\t');
		input.erase(pos,1);
	}
	return input;
}

std::string xmlDatabase::getUserConversations(std::string userID) {
	std::string tmp = "";
	std::string fin = "";
	std::ifstream id("db_files/users/"+userID+"/convs/convs_list.xml");
	while(getline(id,tmp)) {
		fin = fin +tmp;
	}
	fin = replace_tab(fin);
	id.close();
	return fin;
}

std::string xmlDatabase::getUsersConversation(std::string fromID, std::string toID) {
	std::string tmp = "";
	std::string fin = "";
	std::ifstream id("db_files/users/" + fromID + "/convs/" + toID + ".xml");
	while(getline(id,tmp)) {
		fin = fin + tmp;
	}
	fin = replace_tab(fin);
	id.close();
	return fin;
}

void add_user_conv(std::string from, std::string to)
{
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	std::string path = "";
	path = "db_files/users/" + from + "/convs/convs_list.xml";
	const char* p1 = path.c_str();
	doc = xmlReadFile (p1, NULL, 0);
	root = xmlDocGetRootElement(doc);
	const char* t = to.c_str();
	xmlNewChild(root, NULL, BAD_CAST t , NULL);
	xmlSaveFormatFileEnc(p1, doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	path = "db_files/users/" + to + "/convs/convs_list.xml";
	const char* p2 = path.c_str();
	doc = xmlReadFile (p2, NULL, 0);
	root = xmlDocGetRootElement(doc);
	const char* f = from.c_str();
	xmlNewChild(root, NULL, BAD_CAST f , NULL);
	xmlSaveFormatFileEnc(p2, doc, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlCleanupParser();
}

bool add_link(std:: string path, std::string from, std::string to)
{
	std::string l1 = "db_files/users/" + from + "/convs/" + to + ".xml";
	std::string l2 = "db_files/users/" + to + "/convs/" + from + ".xml";
	const char* link1 = l1.c_str();
	const char* link2 = l2.c_str();
	const char* conv = path.c_str();
	if ((0 == symlink(conv, link1)) && (0 == symlink(conv, link2)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void readConversationFile(xmlNode* node, std::string path)
{
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	const char* path1 = path.c_str();
	doc = xmlReadFile (path1, NULL, 0);
	root = xmlDocGetRootElement(doc);
	xmlAddChild(root, node);
	xmlSaveFormatFileEnc(path1, doc, "UTF-8", 0);
	xmlUnlinkNode(root);
	xmlFreeDoc(doc);
	xmlCleanupParser();
}

void addConversationFile(xmlNode* node, std::string path)
{
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	doc = xmlNewDoc(BAD_CAST "1.0");
	root = xmlNewNode(NULL, BAD_CAST "conv");
	xmlDocSetRootElement(doc, root);
	xmlAddChild(root, node);
	const char* path1 = path.c_str();
	xmlSaveFormatFileEnc(path1, doc, "UTF-8", 0);
	xmlUnlinkNode(root);
	xmlFreeDoc(doc);
	xmlCleanupParser();
}

bool add_message(xmlNode* node, std::string from, std::string to)
{
	bool status = true;
	std::string path1 = "db_files/conversations/" + from + to + ".xml";
	std::string path2 = "db_files/conversations/" + to + from + ".xml";
	std::ifstream path_one(path1);
	std::ifstream path_two(path2);
	if(path_one.is_open())
	{
		path_one.close();
		readConversationFile(node, path1);
	}
	else
	{
		if(path_two.is_open())
		{
			path_two.close();
			readConversationFile(node, path2);
		}
		else
		{
			addConversationFile(node, path1);
			add_user_conv(from, to);
			path1 = "../../../../db_files/conversations/" + from + to + ".xml";
			status = add_link(path1, from, to);
		}
	}
	return status;
}

xmlNode* addMessId (xmlNode* root, std::string from)
{
	const char* mid = (IDgenerator::getMessageId()).c_str();
	const char* f = from.c_str();
	xmlNodeSetName(root, BAD_CAST mid);
	xmlNewProp(root, BAD_CAST "from", BAD_CAST f);
	return root;
}

std::string xmlDocToString(xmlDoc* doc)
{
	std::string info = "";
	xmlChar* buf;
	int size = 0;
	xmlDocDumpMemory(doc, &buf, &size);
	info = (char*) buf;
	if (!(buf == NULL))
	{
		info = (char*)buf;
	}

	xmlFree(buf);
	return info;
}

bool add_link_group_convs(std:: string groupId, std::string userId)
{
	std::string p1 = "db_files/users/" + userId + "/convs/" + groupId + ".xml";
	std::string convs = "../../../../db_files/groups/" + groupId + "/conv.xml";
	const char* link = p1.c_str();
	const char* conv = convs.c_str();
	std::string p2 = "db_files/users/" + userId + "/convs/convs_list.xml";
	const char* path = p2.c_str();
	const char* gId = groupId.c_str();
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	doc = xmlReadFile(path, NULL, 0);
	root = xmlDocGetRootElement(doc);
	if ((0 == symlink(conv, link)) && (!(NULL == xmlNewChild(root, NULL, BAD_CAST gId, NULL))))
	{
		xmlSaveFormatFileEnc(path, doc, "UTF-8", 0);
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return true;
	}
	else
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return false;
	}
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

void isValidGroupId(std::string &gId) {
	std::string ids = "db_files/groups/" + gId;
	const char* gid = ids.c_str();
	struct stat sb;
	while (stat(gid, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		gId = IDgenerator::getGroupId();
		ids = "db_files/groups/" + gId;
		gid = ids.c_str();
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
				value = (char*) xmlNodeGetContent(node);
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
		if(child->type != XML_TEXT_NODE){
			if(xmlGetProp(child,cur)!=NULL){
				xmlNode* temp = child->next;
				xmlUnlinkNode(child);
				child = temp;
			}
		}
		else{
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
	xmlChar* buf;
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE) {
			if(0 == strcmp((char*)node->name,"gId")){
				buf = xmlNodeGetContent(node);
				gId = (char*)buf;
				xmlFree(buf);
				break;
			}
		}
	}
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
				login = (char*)xmlNodeGetContent(node);
				continue;
			}
			if(0 == strcmp((char*)node->name, "email"))
				email = (char*)xmlNodeGetContent(node);
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

bool xmlDatabase::deleteGroup(std::string groupID) {
	return true;
}

void add_ID(xmlNode* root_element, std::string id, bool &status)
{
	xmlNode* cur_node = root_element;
	const char* i = id.c_str();
	if (cur_node->type == XML_ELEMENT_NODE)
	{
		if(NULL == xmlNewChild(cur_node, NULL, BAD_CAST i, NULL))
		{
			status = false;
		}
	}
}

void change_quantity(xmlNode* root_element, bool &status)
{
	status = false;
	xmlNode *cur_node = NULL;
	std::string quantity = "";
	for (cur_node = root_element->children; cur_node; cur_node = cur_node->next)
	{
		if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)(cur_node->name), "usersquantity")))
		{
			status = true;
			xmlChar* buf;
			buf = xmlNodeGetContent(cur_node);
			quantity = (char*) buf;
			xmlFree(buf);
			quantity = std::to_string(std::stoi(quantity) + 1);
			const char* new_quantity = quantity.c_str();
			xmlNodeSetContent(cur_node, BAD_CAST new_quantity);
			buf = xmlNodeGetContent(cur_node);
			if(!(0 == strcmp((char*) buf, new_quantity)))
			{
				status = false;
			}
			xmlFree(buf);
		}
	}
}


bool addGroupId (std::string gid, std::string uid)
{
	bool status = false;
	std::string p = "db_files/users/" + uid + "/info.xml";
	const char* path = p.c_str();
	const char* Gid = gid.c_str();
	xmlDoc* doc = NULL;
	xmlNode* root = NULL;
	xmlNode* node = NULL;
	doc = xmlReadFile(path, NULL, 0);
	root = xmlDocGetRootElement(doc);
	for (xmlNode* cur_node = root->children; cur_node; cur_node = cur_node->next)
	{
		if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "groups")))
		{
			if(!(NULL == xmlNewChild(cur_node, NULL, BAD_CAST Gid, NULL)))
			{
				status = true;
				break;
			}
		}
	}
	xmlSaveFormatFileEnc(path, doc, "UTF-8", 0);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	return status;
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
	std::string fromId,toId,messageId,remove_status;
	xmlDoc* doc_rest = NULL;
	xmlNode* root_rest = NULL;
	xmlDoc* doc = NULL;
	xmlNode* root_element = NULL;
	xmlNode* node = NULL;
	doc_rest = xmlReadMemory(messageInfo.c_str(), messageInfo.size(), "noname.xml", NULL, 0);
	root_rest = xmlDocGetRootElement(doc_rest);
	for(node = root_rest->children;node;node = node->next){
                if(0== strcmp((char*)node->name,"fromId"))
			fromId=(char*)xmlNodeGetContent(node);
                if(0== strcmp((char*)node->name,"toId"))
			toId = (char*)xmlNodeGetContent(node);
                if(0== strcmp((char*)node->name,"messageId"))
			messageId = (char*)xmlNodeGetContent(node);
                if(0== strcmp((char*)node->name,"remove_status"))
			remove_status = (char*)xmlNodeGetContent(node);
	
	}
	std::cout<<fromId<<":::::::::::"<<toId<<std::endl;
	xmlChar* atribut = (xmlChar*)fromId.c_str();
	xmlFreeDoc(doc_rest);
        xmlCleanupParser();
        xmlMemoryDump();
	std::string conv = "db_files/users/" + fromId + "/convs/" + toId;
	const char* del_mess = conv.c_str();
	LIBXML_TEST_VERSION;
	doc = xmlReadFile(del_mess, NULL, 0);
	root_element = xmlDocGetRootElement(doc);
	for(node = root_element->children;node;node = node->next){
                if(0== strcmp((char*)node->name,messageId.c_str()))
                        break;
			}
        if(remove_status=="0")
                xmlNewProp(node,BAD_CAST atribut, BAD_CAST "deleted");
        else 
               xmlUnlinkNode(node);
	       xmlSaveFormatFileEnc(conv.c_str(), doc, "UTF-8", 0);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();
                return true;
}

bool xmlDatabase::removeMessageFromGroupConversation(std::string groupInfo){


	return true;
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

bool removeFromGroupUserName(std::string groupID, std::string userID) {
	LIBXML_TEST_VERSION
	std::cout << groupID << "  " << userID << std::endl;
	std::string path = "db_files/groups/" + groupID;
	DIR* groupsDir = opendir(path.c_str());
	if (groupsDir) {
		xmlDoc *doc = NULL;
		xmlNode *root_element = NULL;
		std::string pathForXml = path + "/users.xml";
		doc = xmlReadFile(pathForXml.c_str(), NULL, 0);
		if (doc == NULL) {
			std::cout << "error: there is no such group!" << std::endl;
		} else {
			root_element = xmlDocGetRootElement(doc);
			xmlNode *cur_node = NULL;
			///TBC a_node -> root_element
			for (cur_node = root_element; cur_node; cur_node = cur_node->next) {
				if (cur_node->type == XML_ELEMENT_NODE) {
					const char* name = (const char*)cur_node->name;
					if (strcmp(name, "user") == 0) {
						xmlUnlinkNode(cur_node);
						xmlFreeNode(cur_node);
						break;
					}
				}
			}
			xmlFreeDoc(doc);
			xmlCleanupParser();

		}
		closedir(groupsDir);
	}
}

bool reduceGroupMembersQuantity(std::string groupID) {
	std::string pathGroup = "db_files/groups/" + groupID;
	std::string path = "db_files/groups/" + groupID;
	DIR* usersDir = opendir(pathGroup.c_str());
	if (usersDir) {
		xmlDoc *doc = NULL;
		xmlNode *root_element = NULL;
		std::string pathForInfo = path + "/ginfo.xml";
		doc = xmlReadFile(pathForInfo.c_str(), NULL, 0);
		if (doc == NULL) {
			std::cout << "Error: there is no such a group!" << std::endl;
		}
		root_element = xmlDocGetRootElement(doc);
		xmlNode *cur_node = NULL;
		///TBC a_node -> root_element
		for (cur_node = root_element->children; cur_node; cur_node = cur_node->next) {
			if (cur_node->type == XML_ELEMENT_NODE) {
				const xmlChar* name = cur_node->name;
				if (strcmp((const char*)name, "usersquantity") == 0) {
					xmlChar* value = xmlNodeGetContent(cur_node);
					int temp = atoi((char*) value) - 1;
					const char* tmp = std::to_string(temp).c_str();
					xmlNodeSetContent(cur_node, (xmlChar*) tmp);
					xmlFree(value);
					break;
				}
			}
		}
		xmlSaveFormatFileEnc(pathForInfo.c_str(), doc, "UTF-8", 0);
		xmlFreeDoc(doc);
		xmlCleanupParser();
	} else {
		std::cout << "Error 404 not found" << std::endl;
	}

	closedir(usersDir);
	return true;
}

bool  removeUserIdFromXml(std::string groupID, std::string userID) {
	std::string pathForID = "db_files/groups/" + groupID;
	DIR* usersDirID = opendir(pathForID.c_str());
	if (usersDirID) {
		xmlDoc *doc = NULL;
		xmlNode *root_element = NULL;
		std::string pathForXml = pathForID + "/users.xml";
		doc = xmlReadFile(pathForXml.c_str(), NULL, 0);
		if (doc == NULL) {
			std::cout << "error: user is not a member of group!" << std::endl;
		} else {
			root_element = xmlDocGetRootElement(doc);
			xmlNode* cur_node = NULL;
			for (cur_node = root_element->children; cur_node; cur_node = cur_node->next) {
				if (cur_node->type == XML_ELEMENT_NODE) {
					const char* name = (const char*)cur_node->name;
					if (strcmp(name, userID.c_str()) == 0) {
						xmlUnlinkNode(cur_node);
						xmlFreeNode(cur_node);
						break;
					}
				}
			}
		}
		xmlSaveFormatFileEnc(pathForXml.c_str(), doc, "UTF-8", 0);
		xmlFreeDoc(doc);
		xmlCleanupParser();
	}

	closedir(usersDirID);
	return true;
}

bool xmlDatabase::removeFromGroup(std::string groupID, std::string userID) {
	bool t = false;
	t = removeFromGroupUserName(groupID, userID);
	t = reduceGroupMembersQuantity(groupID);
	t = removeUserIdFromXml(groupID, userID);
	return 0;
}
