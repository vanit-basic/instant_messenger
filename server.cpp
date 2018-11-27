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
static std::string id = "0";
static std::string name1 = "";
static std::string name2 = "";
static std::map<std::string, std::string> infoMap;
static std::map<std::string, std::string> mailMap;
static std::map<std::string, std::pair <std::string, std::string>> loginPassID;
static std::map<std::string, User> idUser;
static std::map<std::string, connection*>  myMap;

std::string mapToString(std::map<std::string, std::string> infoMap) {
    std::string newString = ":";
    for (auto it = infoMap.begin(); it != infoMap.end(); ++it) {
        newString += it->first + ":" + it->second + ":";
    }

    return newString;
}


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
        id = std::to_string(stoi(id) + 1);
        name2 = std::to_string(num) + "2";
        ++num;
        std::cout<<name1<<"  "<<name2<<"\n";
        c->send(name1);
        c->send(name2);
        c->send("q");
        m.unlock();
    }
}

void recv_message(connection* client, std::string message) {
    std::cout << "From client: " << client->getID() << message << std::endl;
    std::string login = "";
    std::string temp = message;
    if (message.find(":check:login:") != std::string::npos) {
        temp.erase(0, 13);
        std::string login = temp.substr(0, temp.find(":"));
        temp.erase(0, login.length() + 6);
        std::string mail = temp.erase(temp.length() - 1); 
        for (auto iter = loginPassID.begin(); iter != loginPassID.end(); ++iter) {
            if (iter->first == login) {
                client->send("Your login is busy!");
            }
        } 
        for  (auto iter = mailMap.begin(); iter != mailMap.end(); ++iter) {
            if (iter->first == mail) {
                client->send("Your e-mail is busy!");
            }
            std::string str = ":yourid:" + id;
            client->send(str);
        }
    } else if (temp == ":action:signin:") {
        temp.erase(0, 15);
        login = temp.substr(0, temp.find(":"));
        temp.erase(0, 10);
        std::string password = temp.substr(temp.length()- 1, 1);
        if (loginPassID[login].first == password) {
            std::string s = ":login:" + login + ":password:" + password + ":";
            client->send(s);
        } else {
            client->send("You enteredYou entered wrong login or password! wrong login or password!");
            client->send("Enter s (for signin), r (for registration) or q (for quit): ");
        }
    } else if (temp == ":action:registration:") {
        temp.erase(0, 21);
        infoMap = stringToMap(temp);
        infoMap.emplace(std::string("ID"), std::string(id));
        auto iter = loginPassID.begin();
        mailMap.emplace(std::string(infoMap["mail"]), std::string(""));
        loginPassID.emplace(std::string(infoMap["login"]), std::make_pair(std::string(infoMap["password"]), std::string(infoMap["ID"])));
        User var(infoMap);
        idUser.emplace(std::string(infoMap["ID"]), User(var));
        id = std::to_string(stoi(id) + 1);
        std::string s = "You are already registered! Your ID is" + infoMap["ID"];
        client->send(s);
    }
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
            new_con->send("Enter s (for signin), r (for registration) or q (for quit): ");
            l.push_back(new_con);
            name1 = "";
            name2 = "";
            m.unlock();
        }
        usleep(100000);
    }

    for (iter = l.begin(); iter != l.end(); ++iter) {
        delete [](*iter);
    }

    return 0;
}
