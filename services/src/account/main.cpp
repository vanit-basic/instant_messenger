#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>
#include <account/account.hpp>
using namespace web;
using namespace cfx;

int main(int argc, const char * argv[])
{
        InterruptHandler::hookSIGINT();

        Account server("ConfigFile.txt");
                if(server.checkServices())
                {

                        try {
                                // wait for server initialization...
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
        return 0;
}
