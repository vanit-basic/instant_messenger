#include "connectionUser.h"

#include <iostream>
#include <unistd.h>
#include <mutex>
#include <string>
#include <map>
#include <string>
#include <regex>
#include <thread>

std::string mapToString(std::map<std::string, std::string> infoMap) {
	std::string newString = ":";
	for (auto it = infoMap.begin(); it != infoMap.end(); ++it) {
		newString += it->first + ":" + it->second + ":";
	}

	return newString;
}

bool isValidName(std::string name) {
	int n = name.length();
	bool t = true;
	if (n > 1) {
		if (name[0] > 'A' && name[0] < 'Z') {
			t = true;
		} else {
			return false;
		}

		for (int i = 1; i < n; ++i) {
			if (name[i] > 'a' && name[i] < 'z') {
				t = true;
			} else {
				return false;
			}
		}
	} else {
		t = false;
	}

	return t;
}

bool isValidSurname(std::string surname) {
	int n = surname.length();
	bool t = true;
	if (n > 1) {
		if (surname[0] > 'A' && surname[0] < 'a') {
			t = true;
		} else {
			return false;
		}

		for (int i = 1; i < n; ++i) {
			if (surname[i] > 'a' && surname[i] < 'z') {
				t = true;
			} else {
				return false;
			}
		}
	} else {
		t = false;
	}

	return t;
}

bool isValidBirthdate(std::string birthdate) {
	int n = birthdate.length();
	if (n == 10) {
		std::string day = birthdate;
		std::string month = birthdate;
		std::string year = birthdate;
		day.erase(2, n - 3);
		month.erase(0, 3);
		month.erase(3, n - 2);
		year.erase(0, n - 4);
		bool t = false;

		if (stoi(year) > 1900 && stoi(year) < 2008) {
			if (month == "01" || month == "05" || month == "07" || month == "08" || month == "10" || month == "12") {
				if (stoi(day) <= 31 && stoi(day) > 0) {
					t = true;
				}
			} else if (month == "04" || month == "06" || month == "09" || month == "11") {
				if (stoi(day) <= 30 && stoi(day) > 0) {
					t = true;
				}
			} else if (month == "02") {
				if (stoi(year) % 4 == 0 && stoi(day) <= 29) {
					t = true;
				} else if (stoi(day) <= 28) {
					t = true;
				}
			}
		} else {
			return false;
		}
		return t;
	}
}

bool isValidGender(std::string gender) {
	int n = gender.length();
	if (n >= 4) {
		if (gender == "male" || gender == "female") {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool isValidLogin(std::string login) {
	int n = login.length();
	bool t = true;
	if (n >= 6) {
		if (login[0] > 'A' && login[0] < 'a') {
			t = true;
		} else {
			return false;
		}

		for (int i = 1; i < n; ++i) {
			if (login[i] > 'a' && login[i] < 'z') {
				t = true;
			} else if (login[i] == 45 || login[i] == 46 || login[i] == 64 || login[i] == 95) {
				t = true;
			} else {
				return false;
			}
		}
	} else {
		t = false;
	}

	return t;
}

std::string replaceBeforeDog(std::string mail){
	std::regex e("[[:alnum:]]+(\\.|-|_)");
	return std::regex_replace(mail, e, "");

}

std::string replaceAfterDog(std::string mail){
	std::regex e("[[:alnum:]]+(\\.|-)");
	return std::regex_replace(mail, e, "");
}

std::string replaceBeforePoint(std::string mail){
	std::regex e("[[:alpha:]]");
	return std::regex_replace(mail, e, "");
}



bool isValidMail(std::string mail){
	int posDog = mail.find("@");
	int posPoint = mail.rfind(".");
	if(posDog == -1 || posPoint == -1 || posPoint < posDog || (mail.length() - posPoint - 1) < 2 ) {
		return false;
	}

	std::string strBeg = replaceBeforeDog(mail.substr(0, posDog));
	std::string strMid = replaceAfterDog(mail.substr(posDog + 1, posPoint - posDog - 1));
	std::string last = replaceBeforePoint(mail.substr(posPoint + 1));
	std::regex beg("[[:alnum:]]+");
	std::regex mid("[[:alnum:]]+");
	if (std::regex_match(strBeg, beg) && std::regex_match(strMid, mid) && last == "" ) {
		return true;
	} else {
		return false;
	}
}

static int id = 0;
std::mutex m;
static std::string name1 = "";
static std::string name2 = "";
static std::string str = "";

void recv_message_server(connection* c, std::string message) {
	if(message!="") {
		m.lock();
		str = message;
		m.unlock();
	}
}

void recv_message(connection* c, std::string message) {
	std::cout << "from server" << message << std::endl;
}

std::string login (std::string login, std::string pass) {
	std::cout << "Enter login or e-mail: ";
	std::cin >> login;
	std::cout << "Enter password: ";
	std::cin >> pass;
	std::string s = ":action:signin:login:" + login + ":password:" + pass + ":";
	return s;
}

std::string regist(std::string login) {
	std::string mail = "";
	std::string id = "";
	std::string name = "";
	std::string surname = "";
	std::string birthdate = "";
	std::string gender = "";
	std::string s = ":action:registration:";

	while (! isValidName(name)) {
		std::cout << "Enter name: ";
		std::cin >> name;
	}

	s += ":name:" + name;

	while (! isValidSurname(surname)) {
		std::cout << "Enter surname: ";
		std::cin >> surname;
	}

	s += ":surname:" + surname;

	while (! isValidBirthdate(birthdate)) {
		std::cout << "Enter birthdate (like dd.mm.yyyy): ";
		std::cin >> birthdate;
	}

	s += ":birthdate:" + birthdate;

	while (! isValidGender(gender)) {
		std::cout << "Enter gender: ";
		std::cin >> gender;
	}

	s += ":gender:" + gender;

	s += ":ID:" + id;
	id++;

	while (! isValidLogin(login)) {
		std::cout << "Enter login: ";
		std::cin >> login;
	}

	s += ":login:" + login;

	while (! isValidMail(mail)) {
		std::cout << "Enter mail (like *****@****.***): ";
		std::cin >> mail;
	}

	s += ":mail:" + mail + ":";
	return s;
}

int main () {
	std::ifstream busy("busy.lock");
	if(busy.is_open()) {
		while(busy.is_open()) {
			usleep(100);
		}
	} else {
		std::ofstream busy1;
		busy1.open("busy.lock");
		connection binder(std::string("in"), std::string("out"));
		binder.setRecvMessageCallback(recv_message_server);
		binder.send("connect");

		int i = 0;
		while (name2=="") {
			m.lock();
			if (str != "") {
				++i;
				if (i == 1) {
					name1 = str;
					str = "";
				}
				if (i > 1) {
					name2 = str;
					str="";
				}

			}
			m.unlock();

		}

		busy1.close();
		remove("busy.lock");
	}
	connection client(name1, name2);
	client.setID(name1);
	client.setRecvMessageCallback(recv_message);

	std::string s = "";
	while (true) {
		std::string login = "";
		std::string pass = "";

		usleep(100);

		while (s != "s" || s != "r" || s != "q") {
			std::cout << "Enter s (for signin), r (for registration) or q (for quit): " << std::endl;
			std::cin >> s;
		}

		if (s == "s") {
			s = login(login, pass);
			client.send(s);
		} else if (s == "r") {
			s = regist(login);
			client.send(s);
		} else if (s == "q") {
			return 0;
		}
		std::getline(std::cin, s);
	}

	return 0;
}
