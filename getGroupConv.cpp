#include<iostream>
#include<string>
#include <stdio.h>
#include<fstream>

bool user_review(std::string user_id, std::string group_id)
{
	std::string users="";
	std::string str="";
	std::ifstream xml("db_files/groups/"+group_id+"/users.xml");
	while(xml>>str)
		users+=str;
	int pos = users.find(user_id);
	if(pos >= 0)
		return true;
	else 
		return false;
}

std::string getGroupConv(std::string user_id, std::string group_id)
{
	std::string str="";
	std::string conv="";
	std::ifstream xml("db_files/groups/"+group_id+"/conv.xml");
	if(user_review(user_id, group_id)){
		while(xml>>str)
			conv+=str;
		return conv;
	}
	else
		return "in valid group";
}

int main()
{

	std::string u_id="";
	std::string g_id="";
	std::getline(std::cin,u_id);
	std::getline(std::cin,g_id);
	std::cout<<getGroupConv(u_id, g_id)<<std::endl;	
	return 0;
}
