#include "connection.hpp"

#include <iostream>
#include <unistd.h>
#include <map>

static int a = 0;
static int id=0;
	std::map<std::string, std::pair<std::string, std::string>> Login_Id_Pass ;
	std::map<std::string, user> id_user;
	std::map<std::string, std::string> users;
	std::map<std::string, connection*> id_con;
	std::map<std::string, std::string> us_con_Id;
bool verific_login(std::string s)
{
	std::map<std::string, std::pair<std::string, std::string>>::iterator it=Login_Id_Pass.begin();
	while(it != Login_Id_Pass.end()) {
                if(s == it->first) {
                        return false;
                        
                }
		++it;
        }
	return true;

}
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

	std::cout << "Sent : " << message  << std::endl;
	if(message == "help") {	
		c->send("Sign in(Enter 1) or Registration(Enter 2)");
	}
	if(message == "2") {
		c->send("Enter your info");
	}
	std::string s = "";
	if(message == "1") {
		c->send("Enter login and password");
	}
	if(message.substr(0,7) == "Sign-in") {
		message.erase(0,8);
		std::string log = message.substr(0, message.find(":"));
		message.erase(0, message.find(":") + 1);
		if(Login_Id_Pass[log].second == message) {
			std::string id_us = Login_Id_Pass[log].first;
			std::string inform = ":information" + infos(id_user,id_us);
			us_con_Id.emplace(id_us, c->getId());
			c->send(inform);
			c->send("For send message to user enter 3, for create new group enter 4, for send message to group enter 5");
		}
		else {
			c->send("wrong login or password");
			c->send("Enter login and password");
		}
	}
	if( message.substr(0,7) == ":Login:") {
	s = message.substr(message.rfind(":") + 1, message.length() - message.rfind(":")-1);
		
		if(verific_login(s))
		{
			c->send("Valid_Login");
		}
		else
		{	c->send("Invalid_Login");
		}
			
	}
	if(message.substr(0,20) == ":action:registration") {
		message.erase(0,20);
		users = string_to_map(message);
		users.emplace("Id",std::to_string(id));
		user u(users);
		id_user.emplace(std::to_string(id), u);
		Login_Id_Pass.emplace(users["Login"],std::make_pair(std::to_string(id),users["Password"]));
		std::map<std::string, user>::iterator it1=id_user.begin();
		++id;
		c->send("Ok");
	}
	if(message == "3") {
		std::map<std::string, user>::iterator it=id_user.begin();
		std::string id_name = "";
		for(int k = 0; k < id; k++) {
			id_name += ":Id:" + it->first + ":FirstName:" + it->second.getFirstName();
		}
		c->send(id_name);
	}
	if(!(message.find("message") == std::string::npos)) {
		message.erase(0,7);
		std::string for_id = message.substr(0, message.find(":"));
		message.erase(0, message.find(":") + 1);
		id_con[us_con_Id[for_id]]->send(message);
	}	
}

void binder_recv_message(connection* c, std::string message) {
	std::cout << "Sent : " << message  << std::endl;
	if(message == "new_client") {
		std::string name1 = "in" + std::to_string(a);
		std::string name2 = "out" + std::to_string(a);
		a++;
		connection* neww = new connection(name2, name1);
		neww->setId(name1);
		id_con.emplace(name1, neww);		
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
