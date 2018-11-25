#include <iostream>
#include <string>
#include <unistd.h>
#include <mutex>
#include "connection.hpp"
#include "user.hpp"
#include "validation.hpp"

static std::mutex mt;
static std::string c_pipe = "";
static std::string s_pipe = "";
static std::map<std::string, std::string> inform;
static std::map <std::string, std::string> users_info;

void send_message(connection* c) {
	mt.lock();
	std::string str;
	std::cout << "Enter UD for view users data, MU for send message another user, CG for creat a new group, MG for send message to group or Q for quit\n";
	std::getline(std::cin, str);
	while (! ("UD" == str || "MU" == str || "CG" == str || "MG" == str || "Q" == str)) {
		std::cout << "Enter UD for view users data, MU for send message another user, CG for creat a new group, MG for send message to group or Q for quit\n";
		std::getline(std::cin, str);
	}
	if ("UD" == str) {
		print(users_info);
		c->send(":return:");
	}
	if ("MU" == str) {
		std::string id;
		std::string msg;

		print(users_info);
		std::cout << "Enter the user id to whom you want to send a message\n";
		getline(std::cin, id);
		while (! id_valid(users_info, id)) {
			std::cout << "Invlaid user id\n";
			print(users_info); 
			getline(std::cin, id);
		}
		std::cout << "Enter the message\n";
		getline(std::cin, msg);
		std::string user_msg = ":SM_user:id:" + id + ":my_id:" + inform["id"] + ":message:" + msg +":";
		c->send(user_msg);
	}
	if ("CG" == str)
		c->send(":action:creat_group:");
	if("MG" == str)
		c->send(":action:SM_group:");
	if("Q" == str)
		c->send("Q");
	mt.unlock();
}

void recv_message_binder(connection* c, std::string message) {
	if ("Q" != message && "" != message) {
		mt.lock();
		c_pipe = message.substr(0, message.find(":"));
		s_pipe = message.substr(message.find(":") + 1);
		mt.unlock();
	}
}

void recv_message(connection* c, std::string message) {
	std::cout << "The server sent: " << message << std::endl;
	if ("Registration || log in || quit" == message) {
		std::cout << "For registration enter R, for log in - L, for quit - Q\n";
		std::string action = "";
		std::getline(std::cin, action);
		while (!(("R" == action) || ("L" == action) || ("Q" == action))) {
			std::cout << "Please enter R for registration, L for log in or Q for quit\n";
			std::getline(std::cin, action);
		}


		if ("R" == action) {
			c->send(":action:registration:");
			std::string data = "";
			std::string str = "";
			std::string p_str;
			std::cout << "Enter your name\n";
			getline(std::cin, str);
			while (! firstname_valid(str)) {
				std::cout << "Enter the correct name\n";
				getline(std::cin, str);
			}
			data = ":firstname:" + str;

			std::cout << "Enter your surname\n";
			getline(std::cin, str);
			while (! lastname_valid(str)) {
				std::cout << "Enter the correct surname\n";
				getline(std::cin, str);
			}
			data += ":lastname:" + str;

			std::cout << "Enter your birth date (dd.mm.yyyy)\n";
			getline(std::cin, str);
			while (! birth_date_valid(str)) {
				std::cout << "Enter the correct birth date\n";
				getline(std::cin, str);
			}
			data += ":birth_date:" + str;

			std::cout << "Enter your gender\n";
			getline(std::cin, str);
			while (! gender_valid(str)) {
				std::cout << "Enter the correct gender\n";
				getline(std::cin, str);
			}
			data += ":gender:" + str;

			std::cout << "Enter your email\n";
			getline(std::cin, str);
			while (! email_valid(str)) {
				std::cout << "Enter the correct email\n";
				getline(std::cin, str);
			}
			data += ":mail:" + str;

			std::cout << "Enter login\n";
			getline(std::cin, str);
			while (! login_valid(str)) {
				std::cout << "Please enter a different login\n";
				getline(std::cin, str);
			}
			data += ":login:" + str;

			std::cout << "Enter password\n";
			getline(std::cin, str);
			while (! password_valid(str)) {
				std::cout << "Please enter new password\n";
				std::getline(std::cin, str);
			}
			std::cout << "Confirm password by typing it again\n";
			getline(std::cin, p_str);
			while (str != p_str) {
				std::cout << "The password is not confirmed. Enter it again\n";
				getline(std::cin, str);
				while (! password_valid(str)) {
					std::cout << "Please enter new password";
					std::getline(std::cin, str);
				}
				std::cout << "Confirm password by typing it again\n";
				getline(std::cin, p_str);
			}
			data = ":registration:info" + data + ":password:" + str + ":";
			c->send(data);
		}
		else {
			if ("L" == action) {
				std::string str = ":action:sign_in:";
				std::string str2;
				std::cout << "Enter login\n";
				std::getline(std::cin, str2);
				str += "login:" + str2 + ":";
				std::cout << "Enter password\n";
				std::getline(std::cin, str2);
				str += "password:" + str2 + ":";
				c->send(str);

			}
			else {
				if ("Q" == action) {
					c->send("Q");
				}
				else {
					if(!(message.find(":registration:info:") == std::string::npos)) {
						std::string msg=message;
						std::string str;
						if(!(message.find(":mail:INVALID:") == std::string::npos)) {
							msg.erase(msg.find("mail:INVALID:"), 13);
							std::cout << "Email is busy, enter new email\n";
							getline(std::cin, str);
							while (! email_valid(str)) {
								std::cout << "Enter the correct email\n";
								getline(std::cin, str);
							}
							msg = msg + "mail:" + str + ":";
						}
						if(!(message.find(":login:INVALID:") == std::string::npos)) {
							msg.erase(msg.find("login:INVALID:"), 14);
							std::cout << "Login is busy, enter new login\n";
							getline(std::cin, str);
							while (! email_valid(str)) {
								std::cout << "Enter the correct login\n";
								getline(std::cin, str);
							}
							msg = msg + "login:" + str + ":";
						}
						c->send(msg);
					}

					else {
						if (! (message.find(":information:") == std::string::npos)) {
							std::string str = message;
							str = str.erase(0, 13);
							inform = strToMap(str);
						}
						else {
							if (! (message.find(":Users_data:") == std::string::npos)) {
								std::cout<<"mtav\n";
								std::string msg = message;
								msg = msg.erase(0, 11);
								users_info = strToMap(msg);
								c->send(":return:");
							}
							else{
								if(message=="Send message another user || create a new group || send message to group || quit"){
									std::thread* t = new std::thread(send_message, c);
								}
								else{
									if(!(message.find(":message_from_user:id:")==std::string::npos)){
											std::cout<<"from server  "<<message<<"\n";
											c->send(":return:");
											}
								}
							}
						}
					}
				}
			}
		}
	}
}

int main () {

	std::ifstream access_possibility("access.txt");
	if (access_possibility.is_open()) {
		while (access_possibility.is_open())
			usleep(100);
	}
	else {
		usleep(1000);
		std::ofstream access_posibility("access.lock");
		connection binder("in", "out");
		binder.setID("Client");
		binder.send("New client");
		binder.setRecvMessageCallback(recv_message_binder);
		access_possibility.close();
		remove("access.lock");
	}
	mt.lock();
	connection client(c_pipe, s_pipe);
	client.setID(c_pipe);
	std::cout << "ID " << client.getID() << std::endl;
	client.setRecvMessageCallback(recv_message);
	mt.unlock();

	return 0;
}
