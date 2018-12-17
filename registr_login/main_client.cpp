#include <iostream>
#include <unistd.h>
#include <string>
#include "connection.hpp"
#include "isvalid.hpp"
#include "function_client.hpp"

int main () {

        connection binder(std::string("in"), std::string("out"));
        binder.send("connect");
        binder.setRecvMessageCallback(binder_recv_message);
        usleep(1000);
        //      while(true){}






        return 0;
}
