#include "connectionUser.h"

#include <iostream>
#include <unistd.h>
#include <mutex>
#include <string>
#include <map>
#include <string>
#include <regex>
#include <thread>

std::mutex m;
static std::string id = "0";
static std::string name1 = "";
static std::string name2 = "";
static std::string str = "";

std::string mapToString(std::map<std::string, std::string> infoMap) {
    std::string newString = ":";
    for (auto it = infoMap.begin(); it != infoMap.end(); ++it) {
        newString += it->first + ":" + it->second + ":";
    }

    return newString;
}

void recv_message_server(connection* c, std::string message) {
    if (message != "") {
        m.lock();
        str = message;
        m.unlock();
    }
}

void recv_message(connection* c, std::string message) {
    std::cout << "from server: " << message << std::endl;
    std::string login = "";
    std::string pass = "";
    std::string mail = "";
    std::string s = "";

    usleep(100);
    if (message == "Enter s (for signin), r (for registration) or q (for quit): ") {
        while (!(s == "s" || s == "r" || s == "q")) {
            std::cout << "Enter s (for signin), r (for registration) or q (for quit): " << std::endl;
            std::cin >> s;
        }

        if (s == "s") {
            std::cout << "Enter login: ";
            std::cin >> login;
            std::cout << "Enter password: ";
            std::cin >> pass;
            s = ":action:signin:login:" + login + ":password:" + pass + ":";
            c->send(s);
        } else if (s == "r") {
            std::cout << "Enter your e-mail adress: ";
            std::cin >> mail;

            while (! isValidMail(mail) ) {
                std::cout << "Your e-mail adress is not Valid. Please, enter again: ";
                std::cin >> mail;
            }

            std::cout << "Enter login: ";
            std::cin >> login;

            while (! isValidLogin(login) ) {
                std::cout << "Your login is not valid. Please, enter again: ";
                std::cin >> mail;
            }

            std::string temp = ":check:login:" + login + ":mail:" + mail + ":";
            c->send(temp);

            while (message == "Your e-mail is busy!") {
                std::cout << "Your e-mail adress is busy!" << std::endl;
                std::cout << "Please, enter new e-mail adress: ";
                std::cin >> mail;
                c->send(mail);
            }

            while (message == "Your login is busy!") {
                std::cout << "Your login is busy!" << std::endl;
                std::cout << "Please, enter new login: ";
                std::cin >> login;
                c->send(login);
            }
            s = regist(login, mail);

            c->send(s);
        }
    }

    if (message.find("You are already registered! Your ID is") != std::string::npos) {
        std::cout << message << std::endl;
    }

    if (message.find(":yourid:") != std::string::npos) {
        id = message.substr(0, 8);
        id = id.substr(id.length() - 1, 1);
        std::cout << "Your id is " << id << std::endl;
    }

    if (message == "You entered wrong login or password!") {
        std::cout << "You entered wrong login or password!";
    }

}

std::string regist(std::string login, std::string mail) {
    std::string id = "";
    std::string name = "";
    std::string surname = "";
    std::string birthdate = "";
    std::string gender = "";
    std::string pass1 = "";
    std::string pass2 = "";
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
    s += ":mail:" + mail;

    do {
        while (! isValidPass(pass1)) {
            std::cout << "Enter your password: ";
            std::cin >> pass1;
        }

        while (! isValidPass(pass2)) {
            std::cout << "Enter your password again for accepting: ";
            std::cin >> pass2;
        }
    } while (pass1 != pass2);

    if (login == "") {
        login = mail;
    }

    s += ":login:" + login;
    s += ":password:" + pass1 + ":";

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
        while (name2 == "") {
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

    return 0;
}
