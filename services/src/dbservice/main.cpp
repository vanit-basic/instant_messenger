#include <iostream>
#include <dbservice/dbservice.hpp>
#include "../../include/dbservice/mongoDb.hpp"

int main () {
	MongoDB* mongo;
	DbService db("config.json", mongo);
	db.accept().wait();
	std::cout << "Start " << std::endl;
	db.shutdown().wait();

	return 0;
}
