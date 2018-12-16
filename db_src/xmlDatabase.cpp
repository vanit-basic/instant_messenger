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

void UpdateGroupDate(xmlNode* root,const xmlChar* tegName,const xmlChar* content)
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
        xmlNewChild(cur_node, NULL, BAD_CAST "id", BAD_CAST i);
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
    std::string email = "db_files/register/mails/" + mail;
    const char* em = email.c_str();
    struct stat sb;
    if (stat(em, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
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
        return false;
    }
    else
    {
        std::string log_f = "db_files/register/logins/" + login;
        const char* log_f_n = log_f.c_str();
        std::string mail_f = "db_files/register/mails/" + mail;
        const char* mail_f_n = mail_f.c_str();
        mode_t process_mask = umask (0);
        mkdir(log_f_n, 0777);
        mkdir(mail_f_n, 0777);
        umask (process_mask);
        return true;
    }
}

void tracker (xmlNode* a_node, std::string &login, std::string &mail, std::string &password) 
{
    xmlNode *cur_node = NULL;
    for (cur_node = a_node->children; cur_node; cur_node = cur_node->next)
    {
        if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "login")))
        {
            login = (char*)xmlNodeGetContent(cur_node);
        }
        if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "email")))
        {
            mail = (char*)xmlNodeGetContent(cur_node);
        }
        if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "password")))
        {
            password = (char*)xmlNodeGetContent(cur_node);
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
	xmlSaveFormatFileEnc(convs, doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
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
		add_ID(root_element, ID);
		std::string id_f = "db_files/users/" + ID;
		const char* id_f_n = id_f.c_str();
		mode_t process_mask = umask (0);
		mkdir(id_f_n, 0777);
		umask (process_mask);
		std::string us_inf = "db_files/users/" + ID + "/info.xml";
		const char* us_inf_char = us_inf.c_str();
		xmlSaveFormatFileEnc(us_inf_char, doc, "UTF-8", 1);
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
                                uId = (char*)xmlNodeGetContent(node);
                                break;
                        }
                }
        }
        std::string path = "db_files/users/" + uId + "/info.xml";
        xmlDoc* docGen = xmlReadFile(path.c_str(), NULL, 0);
        xmlNode* rootGen = xmlDocGetRootElement(docGen);
        for(node = root->children; node; node = node->next) {
                if(node->type == XML_ELEMENT_NODE && strcmp((char*)node->name,"uId")!=0)
                        UpdateUserDate(rootGen, node->name, xmlNodeGetContent(node));
        }
        xmlSaveFormatFileEnc(path.c_str(), docGen, "UTF-8", 1);
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
		if(xml_file.is_open()) {
			while(xml_file >> temp) {
				if(! (temp.substr(0, 7) == "<login>")) {
					info += temp;
				}
			}
		}
		info = info.erase(0, info.find("<info>"));
		return info;
	}
	else
		return "Error 404";

}

/*std::string replacePattern(std::string input, std::string pattern) {
	std::string out = input.replace(pattern);
	return out;
}*/
std::string findAndReplaceAll(std::string & data, std::string toSearch)
{
	size_t pos = data.find(toSearch);
 
	while( pos != std::string::npos)
	{
		data.replace(pos, toSearch.size(), "");
		pos =data.find(toSearch, pos + toSearch.size());
	}
	return data;
}
std::string xmlDatabase::getUserConversations(std::string userID) {
    std::string tmp = "";
    std::string fin = "";
    std::ifstream id("db_files/users/"+userID+"/convs/convs_list.xml");
    while(getline(id,tmp)) {
        fin = fin +tmp;
    }
    fin = findAndReplaceAll(fin,"\n");

    return fin;
}

std::string xmlDatabase::getUsersConversation(std::string fromID, std::string toID) {
	std::string tmp = "";
	std::string fin = "";
	std::ifstream id("db_files/users/" + fromID + "/convs/" + toID);
	while(getline(id,tmp)) {
		fin = fin + tmp;
	}
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
        xmlSaveFormatFileEnc(p2, doc, "UTF-8", 1);
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

bool add_message(xmlNode* node, std::string from, std::string to)
{
        bool status = true;
        std::string path1 = "db_files/conversations/" + from + to + ".xml";
        std::string path2 = "db_files/conversations/" + to + from + ".xml";
        std::ifstream path_one(path1);
        std::ifstream path_two(path2);
        xmlDoc* doc = NULL;
        xmlNode* root = NULL;
        if(path_one.is_open())
        {
                path_one.close();
                const char* path = path1.c_str();
                doc = xmlReadFile (path, NULL, 0);
                root = xmlDocGetRootElement(doc);
                xmlAddChild(root, node);
                xmlSaveFormatFileEnc(path, doc, "UTF-8", 1);
        	xmlCleanupParser();
        }
        else
        {
                if(path_two.is_open())
                {
                        path_two.close();
                        const char* path = path2.c_str();
                        doc = xmlReadFile (path, NULL, 0);
                        root = xmlDocGetRootElement(doc);
                        xmlAddChild(root, node);
                        xmlSaveFormatFileEnc(path, doc, "UTF-8", 1);
        		xmlCleanupParser();
                }
                else
                {
			doc = xmlNewDoc(BAD_CAST "1.0");
                        root = xmlNewNode(NULL, BAD_CAST "conv");
                        xmlDocSetRootElement(doc, root);
                        xmlAddChild(root, node);
                        const char* path = path1.c_str();
                        xmlSaveFormatFileEnc(path, doc, "UTF-8", 1);
                        add_user_conv(from, to);
//jisht link sarqelu hamar path petqa amboxjutyamb tanq, aysinqn amen mekis mot da tarbera linelu minchev instant_messenger direktorian(orinak im mot /home/narek/Documents/Tnayin/  a janapar@ dzer mot ktarbervi aysqan mas@), ashxatacneluc araj nerqevi toxum jisht amboxj janapar@ tveq patth1 = "/amboxj jamaparh@ neraryal conversations direktorian/"  + from + to + ".xml" P.S. amboxj janaparh@ imanalu hamar terminalov mteq conversation direktorian u pwd areq
			path1 = "/home/narek/Documents/Tnayin/instant_messenger/db_files/conversations/" + from + to + ".xml";
                        status = add_link(path1, from, to);
        		xmlCleanupParser();
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

bool xmlDatabase::addUserMessage(std::string from, std::string to, std::string message)
{
        bool status = false;
        std::string path = "";
        const char* mess = message.c_str();
        xmlDoc* doc = NULL;
        xmlNode* root = NULL;
        LIBXML_TEST_VERSION;
        doc = xmlReadMemory(mess, message.length(), "noname.xml", NULL, 0);
        root = xmlDocGetRootElement(doc);
        root = addMessId(root, from);
        status = add_message(root, from, to);
	xmlCleanupParser();
	xmlMemoryDump();
        return status;
}

std::string xmlDatabase::createGroup(std::string groupInfo) {
	std::string groupId = IDgenerator::getGroupId();
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
	if (root->type == XML_ELEMENT_NODE) {
		const char * gId = groupId.c_str();
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
	xmlSaveFormatFileEnc(file, doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();

	doc = xmlNewDoc(BAD_CAST "1.0");
	root = xmlNewNode(NULL, BAD_CAST "users");
	xmlDocSetRootElement(doc, root);
	const char * value1 = value.c_str();
	xmlNewChild(root, NULL, BAD_CAST value1, NULL);
	path = "db_files/groups/" + groupId + "/users.xml";
	const char* file1 = path.c_str();
	xmlSaveFormatFileEnc(file1, doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();

	doc = xmlNewDoc(BAD_CAST "1.0");
	root = xmlNewNode(NULL, BAD_CAST "conv");
	xmlDocSetRootElement(doc, root);
	path = "db_files/groups/" + groupId + "/conv.xml";
	const char* file2 = path.c_str();
	xmlSaveFormatFileEnc(file2, doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();

	std::string id = "<gId>" + groupId + "</gId>";
	return id;
}

std::string xmlDatabase::getGroupInfo(std::string groupID) {
	std::string str = "";
	std::string res = "";
	std::ifstream xml("db_files/groups/" + groupID + "/ginfo.xml");
	while(xml >> str)
		res += str;
	res = res.erase(0, res.find("<info>"));
	return res;
}

std::string xmlDatabase::getGroupConversation(std::string groupID) {
	std::string temp = "";
	std::string conversation = "";
	std::ifstream xml("db_files/groups/" + groupID + "/conv.xml");
	while(xml >> temp){
		conversation += temp;
	}
	return conversation;
}

bool xmlDatabase::updateGroupInfo(std::string groupInfo) {
	LIBXML_TEST_VERSION;
	xmlDoc* doc = xmlReadMemory(groupInfo.c_str(), groupInfo.size(), "noname.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(doc);
	xmlNode* node = NULL;
	std::string gId = "";
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE) {
			if(0 == strcmp((char*)node->name,"gId")){
				gId = (char*)xmlNodeGetContent(node);
				break;
			}
		}
	}
	std::string path = "db_files/groups/" + gId + "/ginfo.xml";
	xmlDoc* docGen = xmlReadFile(path.c_str(), NULL, 0);
	xmlNode* rootGen = xmlDocGetRootElement(docGen);
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE && strcmp((char*)node->name,"gId")!=0)
			UpdateGroupDate(rootGen, node->name, xmlNodeGetContent(node));
	}
	xmlSaveFormatFileEnc(path.c_str(), docGen, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlFreeDoc(docGen);
	xmlMemoryDump();
	return true;
}

bool xmlDatabase::addGroupMessage(std::string messageInfo) {
	return true;
}

xmlDatabase* xmlDatabase::getShared() {
	return sharedDB;
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
			quantity = (char*)xmlNodeGetContent(cur_node);
			quantity = std::to_string(std::stoi(quantity) + 1);
			const char* new_quantity = quantity.c_str();
			xmlNodeSetContent(cur_node, BAD_CAST new_quantity);
			if(!(0 == strcmp((char*)(xmlNodeGetContent(cur_node)), new_quantity)))
			{
				status = false;
			}
		}
	}
}

bool xmlDatabase::addUserToGroup(std::string groupID, std::string userID) 
{
	bool status = true;
	std::string gr_inf = "db_files/groups/" + groupID + "/ginfo.xml";
	const char* c_gr_inf = gr_inf.c_str();
	std::string users = "db_files/groups/" + groupID + "/users.xml";
	const char* c_users = users.c_str();
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;
	LIBXML_TEST_VERSION;
	doc = xmlReadFile(c_users, NULL, 0);
	root_element = xmlDocGetRootElement(doc);
	add_ID(root_element, userID, status);
	xmlSaveFormatFileEnc(c_users, doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	if(status)
	{
		doc = xmlReadFile(c_gr_inf, NULL, 0);
		root_element = xmlDocGetRootElement(doc);
		change_quantity(root_element, status);
		xmlSaveFormatFileEnc(c_gr_inf, doc, "UTF-8", 1);
		xmlFreeDoc(doc);
		xmlCleanupParser();
	}
	return status;
}

bool xmlDatabase::removeMessage(std::string messageInfo) {
	return true;
}

bool xmlDatabase::removeGroupConversation(std::string groupInfo) {
	return true;
}

xmlDatabase::xmlDatabase() {
	if(NULL == sharedDB) sharedDB = this;
}

xmlDatabase::~xmlDatabase() { }

bool xmlDatabase::removeFromGroup(std::string groupID, std::string userID) {
	LIBXML_TEST_VERSION
	std::cout << groupID << "  " << userID << std::endl;
	std::string path = "../db_files/groups/" + groupID;
	DIR* groupsDir = opendir(path.c_str());
	if (groupsDir) {
		xmlDoc *doc = NULL;
		xmlNode *root_element = NULL;
		doc = xmlReadFile("users.xml", NULL, 0);
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
		}
	}

	std::string pathGroup = "../db_files/groups/" + groupID;
	DIR* usersDir = opendir(pathGroup.c_str());
	if (usersDir) {
		DIR* userDir = opendir(userID.c_str());
		if (userDir) {
			xmlDoc *doc = NULL;
			xmlNode *root_element = NULL;
			doc = xmlReadFile("ginfo.xml", NULL, 0);
			if (doc == NULL) {
				std::cout << "Error: there is no such a group!" << std::endl;
			}
			root_element = xmlDocGetRootElement(doc);
			xmlNode *cur_node = NULL;
			//TBC a_node -> root_element
			for (cur_node = root_element; cur_node; cur_node = cur_node->next) {
				if (cur_node->type == XML_ELEMENT_NODE) {
					const xmlChar* name = cur_node->name;
					if (strcmp((const char*)name, "usersquantity") == 0) {
						const xmlChar* value = xmlNodeGetContent(cur_node);
						int temp = atoi((char*) value) - 1;
						const char* tmp = std::to_string(temp).c_str();
						xmlNodeSetContent(cur_node, (xmlChar*) tmp);
						break;
					}
				}
			}


			xmlFreeDoc(doc);

			closedir(userDir);
		} else {
			std::cout << "Error 404 not found" << std::endl;
		}



		closedir(usersDir);
		closedir(groupsDir);
		xmlCleanupParser();

		return true;
	}
}
