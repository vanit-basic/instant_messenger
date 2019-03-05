#include <iostream>
#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>
#include <dbservice/dbservice.hpp>
#include "../../include/dbservice/mongoDb.hpp"

int main (int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Config file is not specified" << std::endl;
		exit(-1);
	}
	else{
		InterruptHandler::hookSIGINT();
		std::string path = std::string(argv[1]);
		database* m = new MongoDB(path);
		m->deleteGroup("g3");
		std::cout<<"database\n";
		DbService db(path, m);
		std::cout<<"dbservice\n";
                        try {
                                // wait for server initialization...
                                db.accept().wait();
                                std::cout << "DbService start " << std::endl;

                                InterruptHandler::waitForUserInterrupt();

                                db.shutdown().wait();
                        }
                        catch(std::exception & e) {
                                std::cerr << "something wrong happen! :(" << '\n';
                        }
                        catch(...) {
                                RuntimeUtils::printStackTrace();
                        }

	}
	return 0;
}
