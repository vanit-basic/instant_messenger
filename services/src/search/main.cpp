#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>
#include <search/search.hpp>
#include <search/cashdatabase.hpp>

int main (int argc, char** argv) {
        if (argc < 2) {
                std::cerr << "Config file is not specified" << std::endl;
                exit(-1);
        }
        else{
                InterruptHandler::hookSIGINT();
                std::string path = std::string(argv[1]);
                cashDatabase* m = new MongoCashDb(path);
                Search server(path, m);
                        try {
                                // wait for server initialization...
                                server.accept().wait();
                                std::cout << "tokenDbService start " << std::endl;

                                InterruptHandler::waitForUserInterrupt();

                                server.shutdown().wait();
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
