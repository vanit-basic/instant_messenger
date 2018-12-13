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

static xmlDatabase* sharedDB = NULL;

IDgenerator obj("us_id.txt","gr_id.txt");

void delete_node(xmlNode* a_node) {
    bool stat = true;
    xmlNode *cur_node = NULL;
    xmlNode* node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
        if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)(cur_node->name), "password")))
        {
            xmlUnlinkNode(cur_node);
            xmlFreeNode(cur_node);
        }
    }
}

void add_ID(xmlNode* root_element, std::string id) {
    xmlNode* cur_node = root_element;
    const char* i = id.c_str();
    if (cur_node->type == XML_ELEMENT_NODE)
    {
        xmlNewChild(cur_node, NULL, BAD_CAST "id", BAD_CAST i);
    }
}

bool isValidLogin(std::string login) {
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

bool isValidEmail(std::string mail) {
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

bool verification(std::string login, std::string mail, std::string &result) {
    if (!(isValidLogin(login) && isValidEmail(mail)))
    {
        if(!isValidLogin(login))
        {
            std::cout<<"Invalid login\n";
            result += "<login>Invalid</login>";
        }
        if(!isValidEmail(mail))
        {
            std::cout<<"Invalid mail\n";
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

void bloodhound(xmlNode* a_node, std::string &login, std::string &mail, std::string &password) {
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
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
            delete_node(cur_node);
        }
        if (!((login == "") || (mail == "") || (password == "")))
        {
            break;
        }
        bloodhound(cur_node->children, login, mail, password);
    }
}

std::string xmlDatabase::registerUser(std::string userInfo) {
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
    bloodhound(root_element, login, mail, password);
    if(verification(login, mail, result))
    {
        std::string ID = IDgenerator::getUserId();
        std::string credtxt = "db_files/register/logins/"+login +"/"  + "creds.txt";
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
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();
        result = "<id>" + ID +"</id>";
    }
	    return result;
}

std::string xmlDatabase::loginUser(std::string login, std::string password) {
    // Open directory with login name
    DIR* loginDir = opendir(login.c_str());
    if (!loginDir) {
        // If there is not directory with such name then login and / or password is not available
        std::cout << "Your login and / or password is not available! Please, try again!" << std::endl;
    } else {
        // Open pass.txt
        std::string path = "./" + login + "/creds.txt";
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
	std::ifstream id("db_files/users/" + fromID + "/convs/" + toID);
	while(id >> tmp)
		fin = fin + tmp;
	return fin;
}


bool xmlDatabase::addUserMessage(std::string messageInfo) {
    return true;
}

std::string xmlDatabase::getGroupInfo(std::string groupID) {
    std::string str = "";
    std::string res = "";
    std::ifstream xml("db_files/groups/" + groupID + "/ginfo.xml");
    while(xml >> str)
        res += str;
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
    return true;
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
                        if(!(0 == strcmp((char*)(xmlNodeGetContent(cur_node)),  new_quantity)))
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

        DIR* groupsDir = opendir("groups/g1");
    if (groupsDir) {
        xmlDoc *doc = NULL;
        xmlNode *root_element = NULL;
        doc = xmlReadFile("ginfo.xml", NULL, 0);
        if (doc == NULL) {
            std::cout << "error: there is no such group!" << std::endl;
        } else {
            root_element = xmlDocGetRootElement(doc);
            xmlNode *cur_node = NULL;
	    ///TBC a_node -> root_element
            for (cur_node = root_element; cur_node; cur_node = cur_node->next) {
                if (cur_node->type == XML_ELEMENT_NODE) {
                    const char* name = (const char*)cur_node->name;
                    const char* value = (const char*)xmlNodeGetContent(cur_node->children);
                    if (strcmp(name, "user") == 0 && strcmp(value, userID.c_str()) == 0) {
                        xmlUnlinkNode(cur_node);
                        xmlFreeNode(cur_node);
                    }
                }
            }
            xmlFreeDoc(doc);
        }
    }

    DIR* usersDir = opendir("users");
    if (usersDir) {
        DIR* userDir = opendir(userID.c_str());
        if (userDir) {
            xmlDoc *doc = NULL;
            xmlNode *root_element = NULL;
            doc = xmlReadFile("info.xml", NULL, 0);
            if (doc == NULL) {
                std::cout << "error: there is no such group!" << std::endl;
            }
            root_element = xmlDocGetRootElement(doc);
            xmlNode *cur_node = NULL;
	    ///TBC a_node -> root_element
            for (cur_node = root_element; cur_node; cur_node = cur_node->next) {
                if (cur_node->type == XML_ELEMENT_NODE) {
                    const xmlChar* name = cur_node->name;
                    const xmlChar* value = xmlNodeGetContent(cur_node->children);
                    if (strcmp((const char*)name, "user") == 0 && strcmp((const char*)value, userID.c_str()) == 0) {
                        xmlUnlinkNode(cur_node);
                        xmlFreeNode(cur_node);
                    }
                }
            }

            xmlFreeDoc(doc);
            closedir(userDir);
        }

        closedir(usersDir);
        closedir(groupsDir);
        xmlCleanupParser();

        return true;
    } 
}

