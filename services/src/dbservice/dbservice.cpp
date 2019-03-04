#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <thread>

#include <dbservice/database.hpp>
#include <dbservice/mongoDb.hpp>
#include <dbservice/dbservice.hpp>



void DbService::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&DbService::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&DbService::handlePost, this, std::placeholders::_1));
}

bool DbService::getUri(std::string path) {
        std::ifstream configFile(path);
        json::value config;
        if (configFile.is_open()) {
                configFile >> config;
                configFile.close();
                this->dbserviceUri = config.at("dbservice").as_string();
                return true;
        } else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

DbService::DbService(std::string path, database* m) : BasicController() {
/*	static int count = 0;
	if (count < 1) {
		++count;
		mongocxx::instance instance{};
	}*/
	if(getUri(path)) {
		this->setEndpoint(dbserviceUri);
	}
	this->m_db = m;
}

DbService::~DbService() {
}

void DbService::handleGet(http_request message) {
	/*	auto threadfunc = [](mongocxx::client& client, std::string dbname) {
		auto coll = client[dbname]["account"].insert_one({});
		};
		std::thread t([&]() {
		auto c = poolMydb->acquire();
		threadfunc(*c, "infoDB");
	//	});

	auto c = poolMydb->acquire();
	std::cout<< message.to_string()<<std::endl;
	auto path = requestPath(message);

	});*/
std::cout<< message.to_string()<<std::endl;
auto path = requestPath(message);
if (!(path.empty())) {
	if (path[0] == "ServiceTest"){
		message.reply(status_codes::OK, "DbService_Start");
	}
}else{
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
}
}

void DbService::handlePost(http_request message) {
	std::cout<<"message  "<<message.to_string()<<std::endl;


	message.extract_json()
		.then([message, this](json::value request) {
				std::cout<<request.at("firstname").as_string();
			auto path = requestPath(message);
			if (!path.empty()) {
				if (path[0] == "check") {
					if (path[1] == "mail&login") {
						json::value response = m_db->mail_login(request);
						message.reply(status_codes::OK, response);
					} else if (path[1] == "userLogin") {
							json::value response = m_db->loginUser(request);
							message.reply(status_codes::OK, response);
						}
						else{
							message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
						}
				} else if (path[0] == "insert") {
						if (path[1] == "registration") {
							std::cout<<"path registration"<<std::endl;
							json::value response = m_db->registerUser(request);
							message.reply(status_codes::OK, response);
						}else {
							message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
						}
					}
			}else {
				message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
			}
		});
}
