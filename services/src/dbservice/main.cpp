#include <iostream>
#include <dbservice/dbservice.hpp>
#include "../../include/dbservice/mongoDb.hpp"

bool createConfigFile() {
        std::ofstream myfile ("config.txt", std::ios::out);
        std::string dbport = "mongodb://localhost:27017";
        std::string mydbport = "mongodb://localhost:27016";
        std::string tokendbport = "mongodb://localhost:27006";

        if (myfile.is_open()) {
                myfile << "db" << std::endl;
                myfile << dbport << std::endl;
                myfile << "mydb" << std::endl;;
                myfile << mydbport << std::endl;
                myfile << "tokendb" << std::endl;
                myfile << tokendbport << std::endl;
                myfile.close();
                return true;
        } else {
                return false;
        }
}

int main () {
	bool t = createConfigFile();
	MongoDB* mongo;
	DbService db("mydb", mongo);
	return 0;
}
