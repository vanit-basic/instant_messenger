#include <stdio.h>

#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>

#include <account/account.hpp>

using namespace web;
using namespace cfx;

int main(int argc, const char * argv[])
{
	if (argc < 2)
	{
		std::cerr << "Config file is not specified" << std::endl;
		exit (-1);
	}
	else
	{
		std::string path = std::string(argv[1]);
        	InterruptHandler::hookSIGINT();

        	Account server(path);
                if(server.checkServices())
                {
                        try {
                                server.accept().wait();
                                std::cout << "Account service start " << std::endl;

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
