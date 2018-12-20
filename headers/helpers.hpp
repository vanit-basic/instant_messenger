#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <xmlDatabase.hpp>
#include<string>

void UpdateGroupDate(xmlNode* root,const xmlChar* tegName, const xmlChar* content);
void UpdateUserDate(xmlNode* root,const xmlChar* tegName,const xmlChar* content);
void remgIdFromUinfo(xmlNode* root, std::string userId);
xmlNodePtr delete_node(xmlNode* a_node);
void add_ID(xmlNode* root_element, std::string id);
bool isValidLogin(std::string login);
bool isValidEmail(std::string mail);
bool verification(std::string login, std::string mail, std::string &result);
void tracker (xmlNode* a_node, std::string &login, std::string &mail, std::string &password);
void isValidId(std::string &ID);
void add_convs_dir(std::string ID);
void addCredtxt(std::string login, std::string password, std::string ID);
void addUserIdDir(std::string ID);
std::string replace_tab(std::string input);
void add_user_conv(std::string from, std::string to);
bool add_link(std:: string path, std::string from, std::string to);
void readConversationFile(xmlNode* node, std::string path);
void addConversationFile(xmlNode* node, std::string path);
bool add_message(xmlNode* node, std::string from, std::string to);
std::string xmlDocToString(xmlDoc* doc);
bool add_link_group_convs(std:: string groupId, std::string userId);
void isValidGroupId(std::string &gId);
bool changeAdmin(std::string gId,std::string newAdmin);
void add_ID(xmlNode* root_element, std::string id, bool &status);
void change_quantity(xmlNode* root_element, bool &status);
bool addGroupId (std::string gid, std::string uid);
bool removeFromGroupUserName(std::string groupID, std::string userID);
bool reduceGroupMembersQuantity(std::string groupID);
bool  removeUserIdFromXml(std::string groupID, std::string userID);


#endif
