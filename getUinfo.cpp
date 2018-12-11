#include <iostream>
#include <string>
#include <fstream>

std::string getUinfo (std::string user_id) {
	
	std::string info = "";
	std::string str = "";
	
	std::ifstream u_info ("db_files/users/"+user_id+"/info.xml");
	
	while (u_info >> str) {
	
		if (str.substr(0, 7) == "<login>") {
			break;
		}
		
		info += str;
	}

	return info;
}

int main () {

	std::string u_id = "";
	std::cout << "User id: ";
	std::cin >> u_id;
	std::cout << getUinfo(u_id) << "\n";
	
	return 0;
}
