#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>

#include <executor/executor.hpp>

using namespace web;
using namespace cfx;

int main(int argc, const char * argv[])
{
	InterruptHandler::hookSIGINT();
	if(argc < 2) {
		std::cerr << "Config file is not passed as an argument.\n\n";
		std::cerr << "Usage: " << argv[0] << " <path to config file>\n";
		exit(-1);
	}

	try {
		// wait for server initialization...
		std::string path(argv[1]);
		Executor server(path);
		if (server.startServices()) {
			server.accept().wait();
			InterruptHandler::waitForUserInterrupt();
			server.shutdown().wait();
		} else {
			std::cerr << "Cannot start services. Exiting...\n";
			exit(-2);
		}
	}

	catch(std::exception & e) {
		std::cerr << e.what() << '\n';
	}
	catch(...) {
		RuntimeUtils::printStackTrace();
	}
	return 0;
}
