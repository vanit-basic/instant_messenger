#include<iostream>
#include<string>
#include <stdio.h>
#include<fstream>

std::string getGroupInfo(std::string group_id)
{
	std::string str="";
	std::string res="";
	std::ifstream xml("db_files/groups/"+group_id+"/ginfo.xml");
	while(xml>>str)
		res+=str;
	return res;
}



int main()
{

	std::string id="";
	std::getline(std::cin,id);
	std::cout<<getGroupInfo(id)<<std::endl;	
	return 0;
}
