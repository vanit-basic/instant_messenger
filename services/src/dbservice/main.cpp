#include <iostream>
#include <dbservice/dbservice.hpp>

int main () {
	DbService db("Config.txt");
	std::cout << "dbservice" << std::endl;
	return 0;
}
