#include <iostream>
#include <regex>
#include <list>
#include <map>
#include <string>
#include <iterator>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "connection.hpp"
#include "user.hpp"
#include "function_server.hpp"

int main () {
	std::ifstream busy("busy.lock");
	if(busy.is_open()){
		while(busy.is_open()){
			usleep(100);
		}
	}
	else{
		std::ofstream busy1("busy.lock");

		connection binder(std::string("out"), std::string("in"));
		binder.setRecvMessageCallback(binder_recv_message);
		busy1.close();
		remove("busy.lock");
	}


	return 0;
}
