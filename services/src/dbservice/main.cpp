#include <iostream>
#include <dbservice/dbservice.hpp>

int main () {
	DbService db("config.txt");
	//std::cout << createConfigFile() << std::endl;
	//std::cout << generateID() << std::endl;
	std::cout << "main" << std::endl;
	return 0;
}
