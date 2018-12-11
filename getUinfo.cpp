#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

std::string getUinfo(std::string user_id) {
	std::string temp = "";
	std::string str = "";
	std::ifstream xml_file("db_files/users/"+user_id+"/info.xml");
	if(xml_file.is_open()) {
		while(xml_file >> temp) {
			if(temp.substr(0, 7) == "<login>") {
				str += "</info>";
				break;
			}
			str += temp;
		}
	}
	return str;
}
int main () {
	std::string str = getUinfo("u100000");
	std::cout << str << std::endl;
	return 0;
}
