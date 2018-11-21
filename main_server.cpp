#include <iostream>
#include "connection.hpp"
#include <map>
static int a = 0;

std::map<std::string,std::string> string_to_map(std::string str) {
	std::map<std::string,std::string> yourmap;
	std::map<std::string,std::string>::iterator it;
	if(str[0] == ':'){
	str.erase(0,1);
	std::string string1;
	std::string string2;
	while(str.length() != 0) {
		string1 = str.substr(0,str.find(":"));
		str.erase(0,str.find(":") + 1);
		string2 = str.substr(0,str.find(":"));
		str.erase(0,str.find(":") + 1);
		yourmap.insert ( std::pair<std::string,std::string>(string1,string2));
	}
	}
	return yourmap;
}

std::string map_to_string (std::map<std::string, std::string> mymap)
{
	std::map<std::string,std::string>::iterator it;
	std::string str = ":";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		str += it->first + ":" + it->second + ":";
	return str;
}

void recv_message(connection* c, std::string message) {
	std::map<std::string, std::pair<std::string, std::string>> Id_Login_Pass ;
	std::cout << "Sent : " << message  << std::endl;
	std::string s = "";
	s.substr(0,6);
	if(s == ":Login") {
	s = message.substr(message.rfind(":") + 1, message.length() - message.rfind(":"));
	it = p.begin();
	int k = 0;
	while(k != p.size()) {
		if(s == it->first) {
			
		}
	}
	
	}	
        maps = string_to_map(message);
	std::string str = map_to_string(maps);
	c->send(str);
}

void binder_recv_message(connection* c, std::string message) {
	std::cout << "Sent : " << message  << std::endl;
	if(message == "new_client") {
		std::string name1 = "in" + std::to_string(a);
		std::string name2 = "out" + std::to_string(a);
		a++;
		connection* neww = new connection(name2, name1);
		neww->setRecvMessageCallback(recv_message);
		std::string name = name1 + ":" + name2;
		c->send(name);
		c->send("q");
	}
}

int main () {

	connection binder(std::string("out"),std::string("in"));
	binder.setRecvMessageCallback(binder_recv_message);
	return 0;
}
