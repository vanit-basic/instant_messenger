#include <base/basic_controller.hpp>
#include <cpprest/http_client.h>

#include <cpprest/filestream.h>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/instance.hpp>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <bsoncxx/types.hpp>

#include <notification/notification.hpp>
#include <notification/mongoDB.hpp>

bool NotDB::createPool(std::string path) {
        std::ifstream configFile(path);
        json::value config;
        if (configFile.is_open()) {
                configFile >> config;
                configFile.close();
                this->poolDB = new mongocxx::pool (mongocxx::uri{config.at("mongodbserver").as_string()});
                return true;
        } else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

NotDB::NotDB(std::string path) {
        static int count = 0;
        if (count < 1) {
                ++count;
                mongocxx::instance instance{};
        }
        createPool(path);

	
}

NotDB::~NotDB() {
        delete[] this->poolDB;
}

json::value NotDB::userJoinGroup(json::value) {}

json::value NotDB::userAcceptInvitation(json::value) {}

json::value NotDB::groupInviteUser(json::value) {}

json::value NotDB::groupAccepyUser(json::value) {}

json::value NotDB::newMessage(json::value) {}

json::value NotDB::messageFromService(json::value) {}

json::value NotDB::groupRemoveUser(json::value) {}

json::value NotDB::userLeaveGroup(json::value) {}

