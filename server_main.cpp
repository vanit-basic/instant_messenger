#include <iostream>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/stat.h>
#include "connection.hpp"
#include "user.hpp"
#include "validation.hpp"

static int i = 1;
static int id = 1;
static std::string str = "";
static std::map<std::string, connection*> id_c;
static std::map<std::string, std::string> uid_cid;
static std::map <std::string, std::pair<std::string, std::string>> log_id_pass;
static std::map <std::string, bool> email;
static std::map <std::string, bool> join;
static std::map <std::string, user>  users;

void recv_message(connection* c, std::string message) {
	std::cout << "The client sent (" << c->getID() << ") " << message << std::endl;
	std::string key, value, login, password;
	std::string msg = message;


	if ("Q" == message)
		c->send("Q");
	else {
		if (!(message.find(":registration:info:") == std::string::npos)) {
			std::map<std::string, std::string> data;
			msg.erase(msg.find(":registration:info"), 18);
			data = strToMap(msg);
			msg = message;

                        msg = msg.erase(0, msg.find(":mail:")+6);
                        key = msg.substr(0, msg.find(':'));
                        msg = msg.erase(0, msg.find(":login:")+7);
                        value = msg.substr(0, msg.find(':'));
                        msg = message;


			if(! email_valid2(email, data["mail"]) || ! login_valid2(log_id_pass, data["login"])) {

				if(! email_valid2(email, data["mail"])) {
                        		msg = msg.erase( msg.find(":mail:"), 6 + key.size());
					msg = msg + "mail:INVALID:";
				}
				if(! login_valid2(log_id_pass, data["login"])) {
					msg = msg.erase(msg.find(":login:"), 7 + value.size());
					msg = msg + "login:INVALID:";
				}
				c->send(msg);
			}
			else {
				std::string user_id = "User_id_" + std::to_string(id);
				++id;
				data.emplace("id", user_id);
				user new_user(data);
				users.emplace(user_id, new_user);
				log_id_pass.emplace(data["login"], std::make_pair(user_id, data["password"]));
				email.emplace(data["mail"], 0);
				c->send("Welcome!!!\n");
				c->send(user_id);
				c->send("Registration || log in || quit");
				std::string str = ":Users_data:id:" + user_id  + ":name:" + new_user.getFirstname() + " " + new_user.getLastname() + ":"; 
				std::map<std::string, connection*>::iterator it;

				for (it = id_c.begin(); it != id_c.end(); ++it) {
					(it->second)->send(str);
				}
			}
		}
		else {
			if (! (message.find(":action:sign_in:") == std::string::npos)) {
				std::string msg = message;
				msg = msg.erase(msg.find(":action:sign_in:"), msg.find(":action:sign_in:") + 22);
				login = msg.substr(0, msg.find(":"));
				msg = msg.erase(0, msg.find(":") + 10);
				password = msg.substr(0, msg.find(":"));
				std::string user_id;
				if (sign_in_valid(log_id_pass, login, password)) {
					if (! join_valid(join, login)) {
						c->send("Login is busy\n");
						c->send("Registration || log in || quit");
					}	
					else {
						join[login] = true;
						user_id = log_id_pass[login].first;
						std::string inform = ":information" + info(users, user_id);
						uid_cid.emplace(user_id, c->getID());
						std::string str;
						std::map<std::string, user>::iterator it;
						for (it = users.begin(); it != users.end(); ++it) {
							str += "id:" + it->first + ":name:" + (it->second).getFirstname() + " " + (it->second).getLastname() + ":"; 
						}
						str = ":Users_data:" + str;
						c->send(inform);
						c->send(str);


					}
				}
				else {
					c->send("No such combination of login and password found");
					c->send("Registration || log in || quit");
				}
			}
			else {
				if (message == ":return:") {
					c->send("Send message another user || create a new group || send message to group || quit");
				}
				else {
					if(! (message.find(":SM_user:id:") == std::string::npos)){
						std::string msg=message;
						std::cout<<"msg  "<<msg<<"\n";
						std::string s_u_id;
						std::string u_id;
						msg = msg.erase(0,12);
						s_u_id = msg.substr(0, msg.find(':'));
						msg = msg.erase(0, s_u_id.size() + 7);
						std::cout<<"msg  "<<msg<<"\n";
						u_id = msg.substr(0, msg.find(':'));
						msg = ":message_from_user:id:" + u_id + msg.erase(0, u_id.size());
						id_c[uid_cid[s_u_id]]->send(msg);
					}
				}
			}
		}
	}
}

void recv_message_binder(connection* c, std::string message) {
	if ("New client" == message) {
		std::cout << "Client: " << message << std::endl;
		std::string c_pipe = "C" + std::to_string(i);
		std::string s_pipe = "S" + std::to_string(i);
		i++;
		str = c_pipe + ":" + s_pipe;
		c->send(str);
		c->send("Q");
		connection * connect = new connection(s_pipe, c_pipe);
		connect->setID(c_pipe);
		connect->setRecvMessageCallback(recv_message);
		connect->send("Registration || log in || quit");
		id_c.emplace(c_pipe, connect);

	}

}

int main () {
	connection binder(std::string("out"), std::string("in"));
	binder.setRecvMessageCallback(recv_message_binder);
	std::map<std::string, connection*>::iterator it = id_c.begin();
	for (; it != id_c.end(); ++it) {
		delete [] (it->second);
	}
	return 0;
}
