#include <iostream>
#include <IDgenerator.hpp>
#include <xmlDatabase.hpp>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

#include <helpers.hpp>

static xmlDatabase* sharedDB = NULL;

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
                       sharedDB->removeFromGroup((char*)node->name,userId);
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

void extract_credentials (xmlNode* a_node, std::string &login, std::string &mail, std::string &password)
{
        xmlNode *cur_node = NULL;
        for (cur_node = a_node->children; cur_node; cur_node = cur_node->next)
        {
                if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "login")))
                {
                        xmlChar* buf;
                        buf = xmlNodeGetContent(cur_node);
                        login = (char*) buf;
                        xmlFree(buf);
                }
                if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "email")))
                {
                        xmlChar* buf;
                        buf = xmlNodeGetContent(cur_node);
                        mail = (char*) buf;
                        xmlFree(buf);
                }
                if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "password")))
                {
                        xmlChar* buf;
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
std::string replace_tab(std::string input){

        while(input.find('\t') != std::string::npos){
                int pos = input.find('\t');
                input.erase(pos,1);
        }
        return input;
}

xmlNode* addMessId (xmlNode* root, std::string from)
{
        const char* mid = (IDgenerator::getMessageId()).c_str();
        const char* f = from.c_str();
        xmlNodeSetName(root, BAD_CAST mid);
        xmlNewProp(root, BAD_CAST "from", BAD_CAST f);
        return root;
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
        xmlSaveFormatFileEnc(p1, doc, "UTF-8", 0);
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

bool changeAdmin(std::string gId,std::string newAdmin){
        std::string oldAdmin = "";
        xmlNode* node = NULL;
        std::string path = "db_files/groups/" + gId + "/ginfo.xml";
        xmlDoc* doc = xmlReadFile(path.c_str(), NULL, 0);
        xmlNode* root = xmlDocGetRootElement(doc);
        for(node = root->children; node; node = node->next){
                if(node->type == XML_ELEMENT_NODE){
                        if(0 == strcmp((char*)node->name,"admin")){
                                oldAdmin = (char*)xmlNodeGetContent(node);
                                break;
                        }
                }
        }
        xmlFreeDoc(doc);
        path = "db_files/users/" + oldAdmin + "/info.xml";
        doc = xmlReadFile(path.c_str(), NULL, 0);
        root = xmlDocGetRootElement(doc);
        for(node = root->children; node; node = node->next){
                if(node->type == XML_ELEMENT_NODE){
                        if(0 == strcmp((char*)node->name,"groupAdmin")){
                                for(node = node->children; node; node = node->next){
                                        if(0 == strcmp((char*)node->name,gId.c_str())){
                                                delete_node(node);
                                                break;
                                        }
                                }
                        }
                }
        }
        xmlSaveFormatFileEnc(path.c_str(), doc, "UTF-8", 0);
        xmlFreeDoc(doc);
        path = "db_files/users/" + newAdmin + "/info.xml";
        doc = xmlReadFile(path.c_str(), NULL, 0);
        root = xmlDocGetRootElement(doc);
        for(node = root->children; node; node = node->next){
                if(node->type == XML_ELEMENT_NODE){
                        if(0 == strcmp((char*)node->name,"groupAdmin")){
                                xmlNewChild(node, NULL, BAD_CAST gId.c_str(), NULL);
                                break;
                        }
                }
        }
        xmlSaveFormatFileEnc(path.c_str(), doc, "UTF-8", 0);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        xmlMemoryDump();
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
                        xmlChar* buf1;
                        buf1 = xmlNodeGetContent(cur_node);
                        if(!(0 == strcmp((char*) buf1, new_quantity)))
                        {
                                status = false;
                        }
                        xmlFree(buf1);
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

std::string find_path(std::string from, std::string to){
        std::string path = "";
        path = "db_files/conversations/" + from + to +".xml";
        std::ifstream conv(path);
        if (conv.is_open())
        {
                conv.close();
                return path;
        }
        else
        {
                path =  "db_files/conversations/" + to + from +".xml";
                return path;
        }
}

bool removeFromXml(std::string fromUserId, std::string toUserId){
        bool flag = false;
        std::string data="db_files/users/"+fromUserId+"/convs/convs_list.xml";
        const char* FileData = data.c_str();
        xmlDoc* doc=NULL;
        doc=xmlReadFile(FileData,NULL,0);
        xmlNode* root =NULL;
        root = xmlDocGetRootElement(doc);
        xmlNode* child =NULL;
        child =root->children;
        while(child != NULL){
                std::string nodeName=(char*)child->name;
                if(nodeName == toUserId){
                        if(child->type != XML_TEXT_NODE){
                                flag = true;
                                child = delete_node(child);
                        }
                }
                else
                        child=child->next;
        }
        if(flag){
                xmlChar* info;
                std::string newXml="";
                int size;
                xmlDocDumpMemory(doc, &info, &size);
                newXml = (char*)info;
                xmlFree(doc);
                xmlFree(info);
                remove(FileData);
                xmlSaveFormatFileEnc(FileData,doc, "UTF-8", 0);
        }
        return flag;
}

void findMessage(std::string messageInfo, std::string &messageId, std::string &correctedMessage) {
	LIBXML_TEST_VERSION;
	const char* info = messageInfo.c_str();
	xmlDoc* doc = xmlReadMemory(info, messageInfo.size(), "noname.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(doc);
	xmlNode* node = NULL;
	xmlNode* node1 = NULL;
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

}
