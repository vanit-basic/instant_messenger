#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include "IDgenerator.hpp"

std::string createGroup(std::string groupInfo) {

	std::string groupId ="g2"; //IDgenerator::getGroupId();
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
		xmlNewChild(root, NULL, BAD_CAST "groupId", BAD_CAST gId);
	}
	xmlNode* node = NULL;
	std::string value = "";
	for(node = root->children; node; node = node->next) {
		if(node->type == XML_ELEMENT_NODE) {
			if(0 == strcmp((char*)node->name, "admin")) {
				value =(char*) xmlNodeGetContent(node);
				std::cout<<value<<"   value\n";
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
	
	std::cout<<"0\n";
	doc = xmlNewDoc(BAD_CAST "1.0");
	std::cout<<"1\n";
        root = xmlNewNode(NULL, BAD_CAST "users");
	std::cout<<"2\n";
        xmlDocSetRootElement(doc, root);
//	xmlCreateIntSubset(doc, BAD_CAST "users", NULL, BAD_CAST "tree2.dtd");	
	std::cout<<"3\n";
	const char * value1 = value.c_str();
	xmlNewChild(root, NULL, BAD_CAST value1, NULL);
	std::cout<<"4\n";
	


	
	path = "db_files/groups/" + groupId + "/users.xml";
	const char* file1 = path.c_str();
	std::cout<<"4\n";
	xmlSaveFormatFileEnc(file1, doc, "UTF-8", 1);
	std::cout<<"5\n";
	xmlFreeDoc(doc);
        xmlCleanupParser();

	doc = xmlNewDoc(BAD_CAST "1.0");
        root = xmlNewNode(NULL, BAD_CAST "conv");
        xmlDocSetRootElement(doc, root);
//	xmlCreateIntSubset(doc, BAD_CAST "conv", NULL, BAD_CAST "tree2.dtd");	
	

	
	path = "db_files/groups/" + groupId + "/conv.xml";
	const char* file2 = path.c_str();
        xmlSaveFormatFileEnc(file2, doc, "UTF-8", 1);
        xmlFreeDoc(doc);
        xmlCleanupParser();



	return groupId;
}

int main()
{
	std::string g = "<info><name>barev</name><admin>u12</admin><date>12.12.1990</date><quantity>1</quantity></info>";
	std::cout<<createGroup(g)<<"\n";
	return 0;
}
