#include "IDgenerator.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>


IDgenerator obj("us_id.txt","gr_id.txt");
void delete_node(xmlNode* a_node)
{
        bool stat = true;
        xmlNode *cur_node = NULL;
        xmlNode* node = NULL;
        for (cur_node = a_node; cur_node; cur_node = cur_node->next)
        {
                if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)(cur_node->name), "Password")))
                {
                        xmlUnlinkNode(cur_node);
                        xmlFreeNode(cur_node);
                }
        }
}
void add_ID(xmlNode* root_element, std::string id)
{
	xmlNode* cur_node = root_element;
	const char* i = id.c_str();
	if (cur_node->type == XML_ELEMENT_NODE)
	{
		xmlNewChild(cur_node, NULL, BAD_CAST "Id", BAD_CAST i);
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
bool verification(std::string login, std::string mail)
{
	std::string error = "";
	if (!(isValidLogin(login) && isValidEmail(mail)))
	{
		if(!isValidLogin(login))
		{
			std::cout<<"Invalid login\n";
			error += "<Login>Invalid</Login>";
		}
		if(!isValidEmail(mail))
		{
			std::cout<<"Invalid mail\n";
			error += "<Email>Invalid</Email>";
		}
//		send(error);
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
void bloodhound(xmlNode* a_node, std::string &login, std::string &mail, std::string &password)
{
        xmlNode *cur_node = NULL;
        for (cur_node = a_node; cur_node; cur_node = cur_node->next)
        {
                if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "Login")))
                {
			login = (char*)xmlNodeGetContent(cur_node);
                }
                if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "Email")))
                {
			mail = (char*)xmlNodeGetContent(cur_node);
                }
                if ((cur_node->type == XML_ELEMENT_NODE) && (0 == strcmp((char*)cur_node->name, "Password")))
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
void registerUser(std::string info)
{
	int length = info.size();
	const char* inf = info.c_str();
	std::string login = "";
	std::string mail = "";
	std::string password = "";
	xmlDoc* doc = NULL;
	xmlNode* root_element = NULL;
	LIBXML_TEST_VERSION;
	doc = xmlReadMemory(inf, length, "noname.xml", NULL, 0);
	root_element = xmlDocGetRootElement(doc);
	bloodhound(root_element, login, mail, password);
	if(verification(login, mail))
	{
		std::string ID = IDgenerator::getUserId();
		std::string credtxt = "db_files/register/logins/"+login +"/"  + "cred.txt";
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
//		send(ID);
	}
}

int main()
{
	std::string info = "<registration_information><FirstName>Jo</FirstName><LastName>Black</LastName><Gender>male</Gender><BirthDate>10.02.1990</BirthDate><Email>black@gmail.com</Email><Login>black1990</Login><Password>JBlack1990</Password></registration_information>";

	registerUser(info);
	return 0;
}
