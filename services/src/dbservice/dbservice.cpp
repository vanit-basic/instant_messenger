#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <thread>

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

#include <dbservice/database.hpp>
#include <dbservice/mongoDb.hpp>
#include <dbservice/dbservice.hpp>


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;
using namespace cfx;
using namespace utility;                   
using namespace web;                       
using namespace web::http;                 
using namespace web::http::client;         
using namespace concurrency::streams; 

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
	auto path = requestPath(message);

	message.extract_json()
		.then([message, path, this](json::value request) {
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
						if (path[1] == "userRegistration") {
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
