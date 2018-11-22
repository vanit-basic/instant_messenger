#include <iostream>
#include <unistd.h>
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
	std::map<std::string, std::pair<std::string, std::string>> Login_Id_Pass ;
	std::map<std::string, std::pair<std::string, std::string>>::iterator it;
	std::cout << "Sent : " << message  << std::endl;
	if(message == "help") {
		c->send("Sign in(Enter 1) or Registration(Enter 2)");
	}
	if(message == "2") {
		c->send("Enter your info");
	}
	std::string s = "";
	if(message.substr(0,7) == ":Login:") {
	s = message.substr(message.rfind(":") + 1, message.length() - message.rfind(":"));
		std::cout << "ifi mej" << "\n";
	it = Login_Id_Pass.begin();
	int k = 0;
	while(it != Login_Id_Pass.end()) {
		std::cout << "whilei mej" << "\n";
		if(s == it->first) {
			c->send("Invalid_Login");
			k++;
		}
	}
	if(k == 0) {
	c->send("Valid_Login");
	}
	}
	if(message.substr(0,20) == ":action:registration") {
		message.erase(0,20);
		std::map<std::string, std::string> users = string_to_map(message);
		//user u(users);
	}	
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
