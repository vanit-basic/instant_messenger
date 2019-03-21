#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>

#include <router/router.hpp>

using namespace web;
using namespace cfx;

int main(int argc, const char * argv[])
{
	InterruptHandler::hookSIGINT();

	if(argc < 2)
	{ 
		std::cerr << "Config file is not specified" << std::endl;
		exit(-1);
	}
	else
	{
		std::string path = std::string(argv[1]);

		Router server(path);
		std::cout<<__LINE__<<std::endl;
		if(server.checkServices())
		{
		std::cout<<__LINE__<<std::endl;
			try {
				server.accept().wait();
				std::cout << "Router start " << std::endl;

				InterruptHandler::waitForUserInterrupt();

				server.shutdown().wait();
			}
			catch(std::exception & e) {
				std::cerr << "somehitng wrong happen! :(" << '\n';
			}
			catch(...) {
				RuntimeUtils::printStackTrace();
			}
		}
	}
	return 0;
}
