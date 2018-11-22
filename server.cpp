#include "connectionUser.h"

#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <unistd.h>

std::mutex m;
static int num = 0;
static std::map<std::string, std::string> infoMap;
static std::string name1 = "";
static std::string name2 = "";

std::map<std::string, std::string> stringToMap (std::string message) {
	int n = message.length();
	std::cout << "string is: " << message << std::endl;
	std::string key = "";
	std::string strMap = "";
	std::string value = "";
	std::map <std::string, std::string> infoMap;
	int pos = 0;
	message.erase(0, 1);

	for (int i = 0; i < n; ++i) {
		pos = message.find(":");
		key = message;
		key.erase(pos, n);
		message.erase(0, pos + 1);
		pos = message.find(":");
		value = message;
		message.erase(0, pos + 1);
		value.erase(pos, n + 1);
		infoMap[key] = value;
		n = message.length();
	}

	return infoMap;
}

void recv_message_client(connection* c, std::string message) {
	std::cout << message << std::endl;
	std::string messCopy = message;
	int n = message.length();
	if (message == "connect") {
		m.lock();
		name1 = std::to_string(num) + "1";
		name2 = std::to_string(num) + "2";
		++num;
		std::cout<<name1<<"  "<<name2<<"\n";
		c->send(name1);
		c->send(name2);
		c->send("q");
		m.unlock();
	}

	infoMap = stringToMap(message);
}

void recv_message(connection* client, std::string message) {
	std::cout << "From client " << client->getID() << message << std::endl;
	client->send(message);
}

int main () {
	std::list<connection*> l;
	std::list<connection*>::iterator iter = l.begin();
	connection server(std::string("out"), std::string("in"));

	server.setRecvMessageCallback(recv_message_client);

	while (true) {
		if (name1 != "" && name2 != "") {
			m.lock();
			connection* new_con = new connection(name2, name1);
			new_con->setID(name1);
			new_con->setRecvMessageCallback(recv_message);
			l.push_back(new_con);
			name1 = "";
			name2 = "";
			m.unlock();
		}
		usleep(100000);
	}

	std::map<std::string, std::string> loginPass;
	std::map<std::string, std::string> mail;
	infoMap = stringToMap(messenger);
	loginPass.insert(std::pair<std::string, std::string> (infoMap["login"], infoMap["password"]));
	mail.insert(std::pair<std::string, std::string>(infoMap["mail"], ""));
	for (iter = l.begin(); iter != l.end(); ++iter) {
		delete [](*iter);
	}

	return 0;
}
